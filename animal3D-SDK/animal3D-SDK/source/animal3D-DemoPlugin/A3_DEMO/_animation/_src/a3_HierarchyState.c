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
		size_t spatial_size = poseCount * sizeof(a3_SpatialPose) * hierarchy->numNodes + sizeof(a3_HierarchyPose) * poseCount;

		// allocate everything (one malloc)
		poseGroup_out->spatialPose_pool = (a3_SpatialPose*)malloc(spatial_size);

		// set pointers
		poseGroup_out->hierarchy = hierarchy;
		poseGroup_out->hierarchyPoses = (a3_HierarchyPose*)((a3_SpatialPose*)(poseGroup_out->spatialPose_pool) + poseCount * hierarchy->numNodes);
		// This is probably not correct
		poseGroup_out->hierarchyPoses->spatialPose = poseGroup_out->spatialPose_pool;

		for (a3ui32 j = 0, i = 0; i < poseCount && j < poseCount * hierarchy->numNodes; ++i, j += hierarchy->numNodes)
		{
			poseGroup_out->hierarchyPoses[i].spatialPose = &poseGroup_out->spatialPose_pool[j];
		}

		// reset all data
		poseGroup_out->channels = a3poseChannel_none;
		poseGroup_out->euler_order = a3poseEulerOrder_xyz;
		poseGroup_out->spatial_pose_count = 0;

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
		size_t pose_size = sizeof(a3_HierarchyPoseGroup) * hierarchy->numNodes;

		// allocate everything (one malloc)
		state_out->poseGroup = (a3_HierarchyPoseGroup*)malloc(pose_size);

		// set pointers
		state_out->hierarchy = hierarchy;

		// reset all data
		state_out->sample_pose = 0;
		state_out->local_space_pose = 0;
		state_out->object_space_pose = 0;

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
