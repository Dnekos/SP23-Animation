#include "a3_HierarchyStateBlend.h"
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
	
	a3_HierarchyStateBlend.inl
	Implementation of inline hierarchical blend operations.
*/


#ifdef __ANIMAL3D_HIERARCHYSTATEBLEND_H
#ifndef __ANIMAL3D_HIERARCHYSTATEBLEND_INL
#define __ANIMAL3D_HIERARCHYSTATEBLEND_INL


//-----------------------------------------------------------------------------

// pointer-based reset/identity operation for single spatial pose
inline a3_SpatialPose* a3spatialPoseOpIdentity(a3_SpatialPose* pose_out)
{
	pose_out->transform = a3mat4_identity;
	// ...

	// done
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpConstruct(a3_SpatialPose* pose_out, a3vec3 rotation, a3vec3 scale, a3vec3 translation)
{
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpCopy(a3_SpatialPose* pose_out, a3_SpatialPose* pose_in)
{
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpInvert(a3_SpatialPose* pose_out)
{
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpConcat(a3_SpatialPose* pose_out, const a3_SpatialPose* lhs, const a3_SpatialPose* rhs)
{

	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpNEAR(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3real const u)
{
	return pose_out;
}

// pointer-based LERP operation for single spatial pose
inline a3_SpatialPose* a3spatialPoseOpLERP(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3real const u)
{

	// done
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpCUBIC(a3_SpatialPose* pose_out, a3_SpatialPose const* posen1, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3_SpatialPose const* pose2, a3real const u)
{
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpDeconcat(a3_SpatialPose* pose_out, const a3_SpatialPose* lhs, const a3_SpatialPose* rhs)
{
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpScale(a3_SpatialPose* pose_out, a3real const u)
{
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpTriangular(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3_SpatialPose const* pose2, a3real const u1, a3real const u2)
{
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpBiNearest(a3_SpatialPose* pose_out, a3_SpatialPose const* pose00, a3_SpatialPose const* pose01, a3_SpatialPose const* pose10, a3_SpatialPose const* pose11, a3real const u0, a3real const u1, a3real const u)
{
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpBiLinear(a3_SpatialPose* pose_out, a3_SpatialPose const* pose00, a3_SpatialPose const* pose01, a3_SpatialPose const* pose10, a3_SpatialPose const* pose11, a3real const u0, a3real const u1, a3real const u)
{
	return pose_out;
}

inline a3_SpatialPose* a3spatialPoseOpBiCubic(a3_SpatialPose* pose_out, a3_SpatialPose const* posen1n1, a3_SpatialPose const* posen10, a3_SpatialPose const* posen11, a3_SpatialPose const* posen12, a3_SpatialPose const* pose0n1, a3_SpatialPose const* pose00, a3_SpatialPose const* pose01, a3_SpatialPose const* pose02, a3_SpatialPose const* pose1n1, a3_SpatialPose const* pose10, a3_SpatialPose const* pose11, a3_SpatialPose const* pose12, a3_SpatialPose const* pose2n1, a3_SpatialPose const* pose20, a3_SpatialPose const* pose21, a3_SpatialPose const* pose22, a3real const un1, a3real const u0, a3real const u1, a3real const u2, a3real const u)
{
	return pose_out;
}

//-----------------------------------------------------------------------------

// data-based reset/identity
inline a3_SpatialPose a3spatialPoseDOpIdentity()
{
	a3_SpatialPose const result = { a3mat4_identity /*, ...*/ };
	return result;
}

inline a3_SpatialPose a3spatialPoseDOpConstruct(a3vec3 rotation, a3vec3 scale, a3vec3 translation)
{
	a3_SpatialPose result = { 0 };

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpCopy(a3_SpatialPose pose_in)
{
	a3_SpatialPose result = { 0 };

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpInvert()
{
	a3_SpatialPose result = { 0 };

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpConcat(const a3_SpatialPose lhs, const a3_SpatialPose rhs)
{
	a3_SpatialPose result = { 0 };

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpNEAR(a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3real const u)
{
	a3_SpatialPose result = { 0 };

	return result;
}

// data-based LERP
inline a3_SpatialPose a3spatialPoseDOpLERP(a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3real const u)
{
	a3_SpatialPose result = { 0 };
	// ...

	// done
	return result;
}

inline a3_SpatialPose a3spatialPoseDOpCUBIC(a3_SpatialPose const posen1, a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3_SpatialPose const pose2, a3real const u)
{
	a3_SpatialPose result = { 0 };

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpDeconcat(const a3_SpatialPose lhs, const a3_SpatialPose rhs)
{
	a3_SpatialPose result = { 0 };

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpScale(a3real const u)
{
	a3_SpatialPose result = { 0 };

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpTriangular(a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3_SpatialPose const pose2, a3real const u1, a3real const u2)
{
	a3_SpatialPose result = { 0 };

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpBiNearest(a3_SpatialPose const pose00, a3_SpatialPose const pose01, a3_SpatialPose const pose10, a3_SpatialPose const pose11, a3real const u0, a3real const u1, a3real const u)
{
	a3_SpatialPose result = { 0 };

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpBiLinear(a3_SpatialPose const pose00, a3_SpatialPose const pose01, a3_SpatialPose const pose10, a3_SpatialPose const pose11, a3real const u0, a3real const u1, a3real const u)
{
	a3_SpatialPose result = { 0 };

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpBiCubic(a3_SpatialPose const posen1n1, a3_SpatialPose const posen10, a3_SpatialPose const posen11, a3_SpatialPose const posen12, a3_SpatialPose const pose0n1, a3_SpatialPose const pose00, a3_SpatialPose const pose01, a3_SpatialPose const pose02, a3_SpatialPose const pose1n1, a3_SpatialPose const pose10, a3_SpatialPose const pose11, a3_SpatialPose const pose12, a3_SpatialPose const pose2n1, a3_SpatialPose const pose20, a3_SpatialPose const pose21, a3_SpatialPose const pose22, a3real const un1, a3real const u0, a3real const u1, a3real const u2, a3real const u)
{
	a3_SpatialPose result = { 0 };

	return result;
}

//-----------------------------------------------------------------------------

// pointer-based reset/identity operation for hierarchical pose
inline a3_HierarchyPose* a3hierarchyPoseOpIdentity(a3_HierarchyPose* pose_out, const a3ui32 nodeCount)
{

	// done
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpConstruct(a3_HierarchyPose* pose_out, a3vec3 rotation, a3vec3 scale, a3vec3 translation, const a3ui32 nodeCount)
{
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpCopy(a3_HierarchyPose* pose_out, a3_HierarchyPose* pose_in, const a3ui32 nodeCount)
{
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpInvert(a3_HierarchyPose* pose_out, const a3ui32 nodeCount)
{
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpConcat(a3_HierarchyPose* pose_out, const a3_HierarchyPose* lhs, const a3_HierarchyPose* rhs, const a3ui32 nodeCount)
{
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpNEAR(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, a3real const u, const a3ui32 nodeCount)
{
	return pose_out;
}

// pointer-based LERP operation for hierarchical pose
inline a3_HierarchyPose* a3hierarchyPoseOpLERP(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, a3real const u, const a3ui32 nodeCount)
{

	// done
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpCUBIC(a3_HierarchyPose* pose_out, a3_HierarchyPose const* posen1, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, a3_HierarchyPose const* pose2, a3real const u, const a3ui32 nodeCount)
{
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpDeconcat(a3_HierarchyPose* pose_out, const a3_HierarchyPose* lhs, const a3_HierarchyPose* rhs)
{
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpScale(a3_HierarchyPose* pose_out, a3real const u)
{
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpTriangular(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, a3_HierarchyPose const* pose2, a3real const u1, a3real const u2)
{
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpBiNearest(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose00, a3_HierarchyPose const* pose01, a3_HierarchyPose const* pose10, a3_HierarchyPose const* pose11, a3real const u0, a3real const u1, a3real const u)
{
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpBiLinear(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose00, a3_HierarchyPose const* pose01, a3_HierarchyPose const* pose10, a3_HierarchyPose const* pose11, a3real const u0, a3real const u1, a3real const u)
{
	return pose_out;
}

inline a3_HierarchyPose* a3hierarchyPoseOpBiCubic(a3_HierarchyPose* pose_out, a3_HierarchyPose const* posen1n1, a3_HierarchyPose const* posen10, a3_HierarchyPose const* posen11, a3_HierarchyPose const* posen12, a3_HierarchyPose const* pose0n1, a3_HierarchyPose const* pose00, a3_HierarchyPose const* pose01, a3_HierarchyPose const* pose02, a3_HierarchyPose const* pose1n1, a3_HierarchyPose const* pose10, a3_HierarchyPose const* pose11, a3_HierarchyPose const* pose12, a3_HierarchyPose const* pose2n1, a3_HierarchyPose const* pose20, a3_HierarchyPose const* pose21, a3_HierarchyPose const* pose22, a3real const un1, a3real const u0, a3real const u1, a3real const u2, a3real const u)
{
	return pose_out;
}

//-----------------------------------------------------------------------------


#endif	// !__ANIMAL3D_HIERARCHYSTATEBLEND_INL
#endif	// __ANIMAL3D_HIERARCHYSTATEBLEND_H