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
	// Validate params
	if(!hierarchy || poseCount < 0)
		return -1;

	// set hierarchy
	poseGroup_out->hierarchy = hierarchy;
	// set count
	poseGroup_out->hierarchical_pose_count = poseCount;

	// allocate memory for hierarchy poses
	poseGroup_out->hierarchyPoses = (a3_HierarchyPose*)malloc(poseCount * sizeof(a3_HierarchyPose));

	return 1;
}

// release pose set
a3i32 a3hierarchyPoseGroupRelease(a3_HierarchyPoseGroup *poseGroup)
{
	// Validate pose group
	if(!poseGroup)
		return -1;

	free(poseGroup->hierarchyPoses);

	return 1;
}


//-----------------------------------------------------------------------------

// initialize hierarchy state given an initialized hierarchy
a3i32 a3hierarchyStateCreate(a3_HierarchyState *state_out, const a3_HierarchyPoseGroup *poseGroup)
{
	// Validate params
	if(!state_out || !poseGroup)
		return -1;

	// set pose group
	state_out->poseGroup = poseGroup;

	state_out->sample_pose = (a3_HierarchyPose*)malloc(sizeof(a3_HierarchyPose));
	state_out->local_space_pose = (a3_HierarchyPose*)malloc(sizeof(a3_HierarchyPose));
	state_out->object_space_pose = (a3_HierarchyPose*)malloc(sizeof(a3_HierarchyPose));

	return 1;
}

// release hierarchy state
a3i32 a3hierarchyStateRelease(a3_HierarchyState *state)
{
	if(!state)
		return -1;

	free(state->sample_pose);
	free(state->local_space_pose);
	free(state->object_space_pose);

	return 1;
}


//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
