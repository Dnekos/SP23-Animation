/*
	Copyright 2011-2020 Daniel S. Buckstein

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	animal3D SDK: Minimal 3D Animation Framework
	By Daniel S. Buckstein
	
	a3_HierarchyState.c
	Implementation of transform hierarchy state.
*/

#include "../a3_HierarchyState.h"

#include <stdlib.h>
#include <string.h>

const a3ui32 NUM_POSES = 3;
#define MAX_CHARACTERS_PER_LINE 255 // idk random value that we shouldnt hit anyway

//-----------------------------------------------------------------------------

// initialize pose set given an initialized hierarchy and key pose count
a3i32 a3hierarchyPoseGroupCreate(a3_HierarchyPoseGroup *poseGroup_out, const a3_Hierarchy *hierarchy, const a3ui32 poseCount)
{
	// validate params and initialization states
	//	(output is not yet initialized, hierarchy is initialized)
	if (poseGroup_out && hierarchy && !poseGroup_out->hierarchy && hierarchy->nodes && poseCount >= 0)
	{
		// determine memory requirements
		poseGroup_out->hierarchical_pose_count = poseCount;
		poseGroup_out->spatial_pose_count = poseCount * hierarchy->numNodes;
		size_t spatial_size = sizeof(a3_SpatialPose) * poseGroup_out->spatial_pose_count + sizeof(a3_HierarchyPose) * poseCount;
		size_t spatialch_size = sizeof(a3_SpatialPoseChannel) * poseGroup_out->spatial_pose_count + sizeof(a3_HierarchyPose) * poseCount;
		size_t spatialeo_size = sizeof(a3_SpatialPoseEulerOrder) * poseGroup_out->spatial_pose_count + sizeof(a3_HierarchyPose) * poseCount;

		// allocate everything (one malloc)
		poseGroup_out->spatialPose_pool = (a3_SpatialPose*)malloc(spatial_size);

		// set pointers
		poseGroup_out->hierarchy = hierarchy;
		poseGroup_out->hierarchyPoses = (a3_HierarchyPose*)((a3_SpatialPose*)(poseGroup_out->spatialPose_pool) + poseGroup_out->spatial_pose_count);
		poseGroup_out->hierarchyPoses->spatialPose = (a3_SpatialPose*)(poseGroup_out->spatialPose_pool) + poseGroup_out->spatial_pose_count;
		// This is probably not correct
		for (a3ui32 i = 0; i < poseGroup_out->spatial_pose_count; ++i)
		{
			a3spatialPoseInit(&poseGroup_out->spatialPose_pool[i], a3mat4_identity, a3vec3_zero, a3vec3_one, a3vec3_zero);
		}

		for (a3ui32 j = 0, i = 0; i < poseCount && j < poseGroup_out->spatial_pose_count; ++i, j += hierarchy->numNodes)
		{
			poseGroup_out->hierarchyPoses[i].spatialPose = &poseGroup_out->spatialPose_pool[j];
		}

		// reset all data
		poseGroup_out->channels = (a3_SpatialPoseChannel*)malloc(spatialch_size);
		poseGroup_out->euler_order = (a3_SpatialPoseEulerOrder*)malloc(spatialeo_size);
		

		// done
		return 1;
	}
	return -1;
}

// release pose set
a3i32 a3hierarchyPoseGroupRelease(a3_HierarchyPoseGroup *poseGroup)
{
	// validate param exists and is initialized
	if (poseGroup && poseGroup->hierarchy)
	{
		// release everything (one free)
		free(poseGroup->spatialPose_pool);

		// reset pointers
		poseGroup->hierarchy = 0;

		// done
		return 1;
	}
	return -1;
}


//-----------------------------------------------------------------------------

// initialize hierarchy state given an initialized hierarchy
a3i32 a3hierarchyStateCreate(a3_HierarchyState *state_out, const a3_Hierarchy *hierarchy)
{
	// validate params and initialization states
	//	(output is not yet initialized, hierarchy is initialized)
	if (state_out && hierarchy && !state_out->hierarchy && hierarchy->nodes)
	{
		// determine memory requirements
		size_t pose_size = sizeof(a3_HierarchyPose) * NUM_POSES + sizeof(a3_SpatialPose) * hierarchy->numNodes * NUM_POSES;

		// allocate everything (one malloc)
		a3_HierarchyPose* hpbase = (a3_HierarchyPose*)malloc(pose_size);
		if (!hpbase)
		{
			// bail
		}

		a3_SpatialPose* spbase = (a3_SpatialPose*)((a3_HierarchyPose*)hpbase + NUM_POSES);

		state_out->sample_pose = hpbase + 0;
		state_out->sample_pose->spatialPose = spbase + hierarchy->numNodes * 0;
		
		// set pointers
		state_out->hierarchy = hierarchy;

		// (target type pointer) ((source type pointer) pointer name + how many source type)
		state_out->local_space_pose = hpbase + 1;
		state_out->local_space_pose->spatialPose = spbase + hierarchy->numNodes * 1;

		state_out->object_space_pose = hpbase + 2;
		state_out->object_space_pose->spatialPose = spbase + hierarchy->numNodes * 2;

		a3hierarchyPoseInit(state_out->sample_pose, hierarchy->numNodes);
		a3hierarchyPoseInit(state_out->local_space_pose, hierarchy->numNodes);
		a3hierarchyPoseInit(state_out->object_space_pose, hierarchy->numNodes);

		// reset all data
		a3hierarchyPoseReset(state_out->sample_pose, hierarchy->numNodes);
		a3hierarchyPoseReset(state_out->local_space_pose, hierarchy->numNodes);
		a3hierarchyPoseReset(state_out->object_space_pose, hierarchy->numNodes);

		// done
		return 1;
	}
	return -1;
}

// release hierarchy state
a3i32 a3hierarchyStateRelease(a3_HierarchyState *state)
{
	// validate param exists and is initialized
	if (state && state->hierarchy)
	{
		// reset pointers
		state->hierarchy = 0;
		state->sample_pose = 0;
		state->local_space_pose = 0;
		state->object_space_pose = 0;

		// release everything (one free)
		free(state->poseGroup);


		// done
		return 1;
	}
	return -1;
}


//-----------------------------------------------------------------------------

// load HTR file, read and store complete pose group and hierarchy
a3i32 a3hierarchyPoseGroupLoadHTR(a3_HierarchyPoseGroup* poseGroup_out, a3_Hierarchy* hierarchy_out, const a3byte* resourceFilePath)
{
	if (poseGroup_out && !poseGroup_out->spatial_pose_count && hierarchy_out && !hierarchy_out->numNodes && resourceFilePath && *resourceFilePath)
	{
		a3ui32 segments = 0, frames = 0;
		char namebuffer[MAX_CHARACTERS_PER_LINE];

		a3f32 tx, ty, tz, rx, ry, rz, scale;
		a3_SpatialPoseEulerOrder order = a3poseEulerOrder_xyz;		

		// Create file pointer
		FILE* fPtr;

		// Open file for reading
		fPtr = fopen(resourceFilePath, "r");

		char buffer[MAX_CHARACTERS_PER_LINE];
		a3ui32 numbytes = MAX_CHARACTERS_PER_LINE;

		// Assume everything we check here is related to the header - failed
		while (strncmp(buffer, "[SegmentNames&Hierarchy]", numbytes) != 0 )
		{
			a3readWordFromFile(fPtr, buffer);
			if (strncmp(buffer, "NumSegments", numbytes) == 0)
			{
				a3readWordFromFile(fPtr, buffer);
				sscanf(buffer, "%u", &segments);
			}
			else if (strncmp(buffer, "NumFrames", numbytes) == 0)
			{
				a3readWordFromFile(fPtr, buffer);
				sscanf(buffer, "%u", &frames);
			}
		}

		// setting up hierarchy
		a3hierarchyCreate(hierarchy_out, segments, 0);
		a3ui32 jointIndex = 0;
		a3i32 jointParentIndex = -1;

		// setting up hierarchy pose group (frames+1 is to include base pose)
		a3hierarchyPoseGroupCreate(poseGroup_out, hierarchy_out, frames+1); // euler order will be a var giv

		// ------------------------------------------------------------------------------------------------------------
		
		while (strncmp(buffer, "[BasePosition]", numbytes) != 0)
		{
			// grab both names, save one as the actual name
			a3readWordFromFile(fPtr, namebuffer);

			// we found the end of the bone creation
			if (strncmp(namebuffer, "[BasePosition]", numbytes) == 0)
				break;

			a3readWordFromFile(fPtr, buffer);

			// GLOBAL fails GetNodeIndex, giving us the root index
			jointParentIndex = a3hierarchyGetNodeIndex(hierarchy_out, buffer);
			/*if (strncmp(buffer, "GLOBAL", numbytes) != 0)
				jointParentIndex = a3hierarchyGetNodeIndex(hierarchy_out, buffer);
			else
				jointParentIndex = -1;*/

			// set joint
			a3hierarchySetNode(hierarchy_out, jointIndex++, jointParentIndex, namebuffer);
		}

		// ------------------------------------------------------------------------------------------------------------
		// 
		// base pose 
		a3_SpatialPose* spatialPose = 0;
		for (a3ui32 i = 0; i < segments; ++i)
		{
			// bone name
			char namebuf[MAX_CHARACTERS_PER_LINE];

			a3readWordFromFile(fPtr, namebuf);
			
			// read the translation, rotation, and scale values
			fscanf(fPtr, "%f %f %f %f %f %f %f", &tx, &ty, &tz, &rx, &ry, &rz, &scale);
			/*
			a3readWordFromFile(fPtr, buffer);
			sscanf(buffer, "%f", &tx);
			a3readWordFromFile(fPtr, buffer);
			sscanf(buffer, "%f", &ty);
			a3readWordFromFile(fPtr, buffer);
			sscanf(buffer, "%f", &tz);
			a3readWordFromFile(fPtr, buffer);
			sscanf(buffer, "%f", &rx);
			a3readWordFromFile(fPtr, buffer);
			sscanf(buffer, "%f", &ry);
			a3readWordFromFile(fPtr, buffer);
			sscanf(buffer, "%f", &rz);
			a3readWordFromFile(fPtr, buffer);
			sscanf(buffer, "%f", &scale);
			*/

			// Get our joint index from name
			jointIndex = a3hierarchyGetNodeIndex(hierarchy_out, namebuf);

			// Set the values to the spatial pose
			spatialPose = poseGroup_out->hierarchyPoses[0].spatialPose + jointIndex;
			a3spatialPoseSetTranslation(spatialPose, tx, ty, tz);
			a3spatialPoseSetRotation(spatialPose, rx, ry, rz);
			a3spatialPoseSetScale(spatialPose, scale, scale, scale);

			/*printf("%s\n", namebuffer);
			printf("%f\n", tx);
			printf("%f\n", ty);
			printf("%f\n", tz);
			printf("%f\n", rx);
			printf("%f\n", ry);
			printf("%f\n", rz);
			printf("%f\n", scale);*/

			// Handle Euler Channels
			if (tx != 0)
				poseGroup_out->channels[jointIndex] |= a3poseChannel_translate_x;
			if (ty != 0)
				poseGroup_out->channels[jointIndex] |= a3poseChannel_translate_y;
			if (tz != 0)
				poseGroup_out->channels[jointIndex] |= a3poseChannel_translate_z;
			if (rx != 0)
				poseGroup_out->channels[jointIndex] |= a3poseChannel_orient_x;
			if (ry != 0)
				poseGroup_out->channels[jointIndex] |= a3poseChannel_orient_y;
			if (rz != 0)
				poseGroup_out->channels[jointIndex] |= a3poseChannel_orient_z;
			if (scale != 1)
				poseGroup_out->channels[jointIndex] |= a3poseChannel_scale_xyz;
		}

		// ------------------------------------------------------------------------------------------------------------
		
		// individual poses
		for (a3ui32 j = 0; j < segments; ++j)
		{
			a3readWordFromFile(fPtr, buffer);

			// get joint index from the name
			jointIndex = a3hierarchyGetNodeIndex(hierarchy_out, namebuffer);

			a3i32 index;
			for (a3ui32 p = 0; p < frames; ++p)
			{
				// bone index
				a3readWordFromFile(fPtr, buffer);
				sscanf(buffer, "%i", &index);

				// read the translation, rotation, and scale values
				fscanf(fPtr, "%f %f %f %f %f %f %f", &tx, &ty, &tz, &rx, &ry, &rz, &scale);

				// Set the values to the spatial pose
				spatialPose = poseGroup_out->hierarchyPoses[index].spatialPose + j; // WHEN USING STEVE's, REMOVE +1
				a3spatialPoseSetTranslation(spatialPose, tx, ty, tz);
				a3spatialPoseSetRotation(spatialPose, rx, ry, rz);
				a3spatialPoseSetScale(spatialPose, scale, scale, scale);

			}
		}

		// ------------------------------------------------------------------------------------------------------------
		
		// Close file 
		fclose(fPtr);
		return 1;
	}
	return -1;
}

// load BVH file, read and store complete pose group and hierarchy
a3i32 a3hierarchyPoseGroupLoadBVH(a3_HierarchyPoseGroup* poseGroup_out, a3_Hierarchy* hierarchy_out, const a3byte* resourceFilePath)
{
	if (poseGroup_out && !poseGroup_out->spatial_pose_count && hierarchy_out && !hierarchy_out->numNodes && resourceFilePath && *resourceFilePath)
	{

	}
	return -1;
}

// Read up to whitespace, while skipping comments
a3i32 a3readWordFromFile(FILE* ptr, char* output) 
{
	if (ptr && output) 
	{
		// reading word
		int byts = fscanf(ptr, "%s", output);
		if (byts <= 0)
			return -1;

		// if word is start of comment
		if (output[0] == '#')
		{
			// read through line
			fgets(output, MAX_CHARACTERS_PER_LINE, ptr);

			// grab new word
			byts = fscanf(ptr, "%s", output);
			if (byts <= 0)
				return -1;
		}

		printf("%s\n", output);

		return byts;
	}

	return -1;
}


// Potential Functions to make code cleaner.
a3i32 a3initBasePoseFromFile(FILE* ptr, char* output)
{
	return -1;
}

// Header is already in HierarchyState.h
a3i32 a3createIndividualPoses(FILE* ptr, char* output)
{
	return -1;
}


//-----------------------------------------------------------------------------
