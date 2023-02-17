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

		// allocate everything (one malloc)
		poseGroup_out->spatialPose_pool = (a3_SpatialPose*)malloc(spatial_size);

		// set pointers
		poseGroup_out->hierarchy = hierarchy;
		poseGroup_out->hierarchyPoses = (a3_HierarchyPose*)((a3_SpatialPose*)(poseGroup_out->spatialPose_pool) + poseGroup_out->spatial_pose_count);
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
		poseGroup_out->channels = (a3_SpatialPoseChannel*)malloc(spatial_size);
		poseGroup_out->euler_order = a3poseEulerOrder_xyz;
		

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
		size_t pose_size = sizeof(a3_HierarchyPose) * hierarchy->numNodes * NUM_POSES;

		// allocate everything (one malloc)
		state_out->sample_pose = (a3_HierarchyPose*)malloc(pose_size);

		// Stage 1
		for (a3ui32 i = 0; i < NUM_POSES * hierarchy->numNodes; ++i) 
		{
			state_out->sample_pose->spatialPose = &state_out->poseGroup->spatialPose_pool[i * hierarchy->numNodes];
		}

		/*for (a3ui32 i = 0; i < state_out->poseGroup->spatial_pose_count; ++i)
		{
			a3spatialPoseInit(&state_out->sample_pose->spatialPose[i], a3mat4_identity, a3vec3_zero, a3vec3_one, a3vec3_zero);
		}*/

		// set pointers
		state_out->hierarchy = hierarchy;

		state_out->local_space_pose = (a3_HierarchyPose*)state_out->sample_pose + 1 * hierarchy->numNodes;
		
		for (a3ui32 i = 0; i < NUM_POSES * hierarchy->numNodes; ++i)
		{
			state_out->local_space_pose->spatialPose = &state_out->sample_pose->spatialPose[i];
		}
		/*
		for (a3ui32 i = 0; i < state_out->poseGroup->spatial_pose_count; ++i)
		{
			a3spatialPoseInit(&state_out->local_space_pose->spatialPose[i], a3mat4_identity, a3vec3_zero, a3vec3_one, a3vec3_zero);
		}*/

		state_out->object_space_pose = (a3_HierarchyPose*)state_out->sample_pose + 2 * hierarchy->numNodes;

		// reset all data
		//a3hierarchyPoseReset(state_out->sample_pose, hierarchy->numNodes);
		//a3hierarchyPoseReset(state_out->local_space_pose, hierarchy->numNodes);
		//a3hierarchyPoseReset(state_out->object_space_pose, hierarchy->numNodes);

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


//-----------------------------------------------------------------------------
