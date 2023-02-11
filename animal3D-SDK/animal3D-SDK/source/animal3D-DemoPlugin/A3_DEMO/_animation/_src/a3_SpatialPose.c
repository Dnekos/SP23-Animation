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
	
	a3_SpatialPose.c
	Implementation of spatial pose.
*/

#include "../a3_SpatialPose.h"


//-----------------------------------------------------------------------------

a3i32 a3spatialPoseInit(a3_SpatialPose* spatialPose_out, a3mat4 spatial_transform, a3vec3 spatial_orientation, a3vec3 spatial_scale, a3vec3 spatial_translation)
{
	if(!spatialPose_out)
		return -1;
	spatialPose_out->transform = spatial_transform;
	spatialPose_out->orientation = spatial_orientation;
	spatialPose_out->scale = spatial_scale;
	spatialPose_out->translation = spatial_translation;

	return 1;
}

//-----------------------------------------------------------------------------
