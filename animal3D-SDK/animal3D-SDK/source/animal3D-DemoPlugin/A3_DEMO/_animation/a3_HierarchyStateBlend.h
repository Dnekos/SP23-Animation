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
	
	a3_HierarchyStateBlend.h
	Hierarchy blend operations.
*/

#ifndef __ANIMAL3D_HIERARCHYSTATEBLEND_H
#define __ANIMAL3D_HIERARCHYSTATEBLEND_H


#include "a3_HierarchyState.h"

#include "a3_Kinematics.h"


#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus

#endif	// __cplusplus
	

//-----------------------------------------------------------------------------

// pointer-based reset/identity operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpIdentity(a3_SpatialPose* pose_out);

// pointer-based constructor operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpConstruct(a3_SpatialPose* pose_out, a3vec3 rotation, a3vec3 scale, a3vec3 translation);

// pointer-based copy operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpCopy(a3_SpatialPose* pose_out, a3_SpatialPose const* pose_in);

// pointer-based inversion / negation operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpInvert(a3_SpatialPose* pose_out);

// pointer-based addition operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpConcat(a3_SpatialPose* pose_out, a3_SpatialPose const* lhs, a3_SpatialPose const* rhs);

// pointer-based Nearest operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpNEAR(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, 
	a3real const u);

// pointer-based LERP operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpLERP(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, 
	a3real const u);

a3_SpatialPose* a3spatialPoseOpSmoothStep(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1,
	a3real const u);

// pointer-based cubic operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpCUBIC(a3_SpatialPose* pose_out, a3_SpatialPose const* posen1, a3_SpatialPose const* pose0, 
	a3_SpatialPose const* pose1, a3_SpatialPose const* pose2, a3real const u);

// DERIVATIVE OPERATIONS

// pointer-based subtraction / difference operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpDeconcat(a3_SpatialPose* pose_out, a3_SpatialPose const* lhs, a3_SpatialPose const* rhs);

// pointer-based multiplication / scale operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpScale(a3_SpatialPose* pose_out, a3real const u);

a3_SpatialPose* a3spatialPoseOpDescale(a3_SpatialPose* pose_out, a3real const u);

// pointer-based triangular operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpTriangular(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0,
	a3_SpatialPose const* pose1, a3_SpatialPose const* pose2, a3real const u1, a3real const u2);

// pointer-based bilinear operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpBiNearest(a3_SpatialPose* pose_out, a3_SpatialPose const* pose00, a3_SpatialPose const* pose01,
	a3_SpatialPose const* pose10, a3_SpatialPose const* pose11, a3real const u0, a3real const u1, a3real const u);

// pointer-based bilinear operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpBiLinear(a3_SpatialPose* pose_out, a3_SpatialPose const* pose00, a3_SpatialPose const* pose01,
	a3_SpatialPose const* pose10, a3_SpatialPose const* pose11, a3real const u0, a3real const u1, a3real const u);

// pointer-based bicubic operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpBiCubic(a3_SpatialPose* pose_out, 
	a3_SpatialPose const* posen1n1, a3_SpatialPose const* posen10,a3_SpatialPose const* posen11, a3_SpatialPose const* posen12,
	a3_SpatialPose const* pose0n1, a3_SpatialPose const* pose00, a3_SpatialPose const* pose01, a3_SpatialPose const* pose02,
	a3_SpatialPose const* pose1n1, a3_SpatialPose const* pose10, a3_SpatialPose const* pose11, a3_SpatialPose const* pose12,
	a3_SpatialPose const* pose2n1, a3_SpatialPose const* pose20, a3_SpatialPose const* pose21, a3_SpatialPose const* pose22,
	a3real const un1, a3real const u0, a3real const u1, a3real const u2, a3real const u);

//-----------------------------------------------------------------------------

// data-based reset/identity
a3_SpatialPose a3spatialPoseDOpIdentity();

// data-based constructor operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpConstruct(a3vec3 rotation, a3vec3 scale, a3vec3 translation);

// data-based copy operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpCopy(a3_SpatialPose pose_in);

// data-based inversion / negation operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpInvert(a3_SpatialPose pose_in);

// data-based addition operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpConcat(a3_SpatialPose const lhs, a3_SpatialPose const rhs);

// data-based Nearest operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpNEAR(a3_SpatialPose const pose0, a3_SpatialPose const pose1,
	a3real const u);

// data-based LERP
a3_SpatialPose a3spatialPoseDOpLERP(a3_SpatialPose const pose0, a3_SpatialPose const pose1, 
	a3real const u);

// data-based cubic operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpCUBIC(a3_SpatialPose const posen1, a3_SpatialPose const pose0,
	a3_SpatialPose const pose1, a3_SpatialPose const pose2, a3real const u);

// DERIVATIVE OPERATIONS

// data-based subtraction / difference operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpDeconcat(a3_SpatialPose const lhs, a3_SpatialPose const rhs);

// data-based multiplication / scale operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpScale(a3_SpatialPose lhs, a3real const u);

// data-based triangular operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpTriangular(a3_SpatialPose const pose0,
	a3_SpatialPose const pose1, a3_SpatialPose const pose2, a3real const u1, a3real const u2);

// data-based bilinear operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpBiNearest(a3_SpatialPose const pose00, a3_SpatialPose const pose01,
	a3_SpatialPose const pose10, a3_SpatialPose const pose11, a3real const u0, a3real const u1, a3real const u);

// data-based bilinear operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpBiLinear(a3_SpatialPose const pose00, a3_SpatialPose const pose01,
	a3_SpatialPose const pose10, a3_SpatialPose const pose11, a3real const u0, a3real const u1, a3real const u);

// data-based bicubic operation for single spatial pose
a3_SpatialPose a3spatialPoseDOpBiCubic(
	a3_SpatialPose const posen1n1, a3_SpatialPose const posen10, a3_SpatialPose const posen11, a3_SpatialPose const posen12,
	a3_SpatialPose const pose0n1, a3_SpatialPose const pose00, a3_SpatialPose const pose01, a3_SpatialPose const pose02,
	a3_SpatialPose const pose1n1, a3_SpatialPose const pose10, a3_SpatialPose const pose11, a3_SpatialPose const pose12,
	a3_SpatialPose const pose2n1, a3_SpatialPose const pose20, a3_SpatialPose const pose21, a3_SpatialPose const pose22,
	a3real const un1, a3real const u0, a3real const u1, a3real const u2, a3real const u);


//-----------------------------------------------------------------------------

// pointer-based reset/identity operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpIdentity(a3_HierarchyPose* pose_out, 
	const a3ui32 nodeCount);

// pointer-based constructor operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpConstruct(a3_HierarchyPose* pose_out, a3vec3 rotation, a3vec3 scale, a3vec3 translation, 
	const a3ui32 nodeCount);

// pointer-based copy operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpCopy(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose_in, 
	const a3ui32 nodeCount);

// pointer-based inversion / negation operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpInvert(a3_HierarchyPose* pose_out, 
	const a3ui32 nodeCount);

// pointer-based addition operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpConcat(a3_HierarchyPose* pose_out, a3_HierarchyPose const* lhs, a3_HierarchyPose const* rhs, 
	const a3ui32 nodeCount);

// pointer-based Nearest operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpNEAR(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1,
	a3real const u, const a3ui32 nodeCount);

// pointer-based LERP operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpLERP(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, 
	a3real const u, const a3ui32 nodeCount);

a3_HierarchyPose* a3hierarchyPoseOpSmoothStep(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1,
	a3real const u, const a3ui32 nodeCount);

// pointer-based cubic operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpCUBIC(a3_HierarchyPose* pose_out, a3_HierarchyPose const* posen1, a3_HierarchyPose const* pose0,
	a3_HierarchyPose const* pose1, a3_HierarchyPose const* pose2, a3real const u, const a3ui32 nodeCount);

// DERIVATIVE OPERATIONS

// pointer-based subtraction / difference operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpDeconcat(a3_HierarchyPose* pose_out, a3_HierarchyPose const* lhs, a3_HierarchyPose const* rhs, const a3ui32 nodeCount);

// pointer-based multiplication / scale operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpScale(a3_HierarchyPose* pose_out, a3real const u, const a3ui32 nodeCount);

a3_HierarchyPose* a3hierarchyPoseOpDescale(a3_HierarchyPose* pose_out, a3real const u, const a3ui32 nodeCount);

// pointer-based triangular operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpTriangular(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0,
	a3_HierarchyPose const* pose1, a3_HierarchyPose const* pose2, a3real const u1, a3real const u2, const a3ui32 nodeCount);

// pointer-based bilinear operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpBiNearest(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose00, a3_HierarchyPose const* pose01,
	a3_HierarchyPose const* pose10, a3_HierarchyPose const* pose11, a3real const u0, a3real const u1, a3real const u, const a3ui32 nodeCount);

// pointer-based bilinear operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpBiLinear(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose00, a3_HierarchyPose const* pose01,
	a3_HierarchyPose const* pose10, a3_HierarchyPose const* pose11, a3real const u0, a3real const u1, a3real const u, const a3ui32 nodeCount);

// pointer-based bicubic operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpBiCubic(a3_HierarchyPose* pose_out,
	a3_HierarchyPose const* posen1n1, a3_HierarchyPose const* posen10, a3_HierarchyPose const* posen11, a3_HierarchyPose const* posen12,
	a3_HierarchyPose const* pose0n1, a3_HierarchyPose const* pose00, a3_HierarchyPose const* pose01, a3_HierarchyPose const* pose02,
	a3_HierarchyPose const* pose1n1, a3_HierarchyPose const* pose10, a3_HierarchyPose const* pose11, a3_HierarchyPose const* pose12,
	a3_HierarchyPose const* pose2n1, a3_HierarchyPose const* pose20, a3_HierarchyPose const* pose21, a3_HierarchyPose const* pose22,
	a3real const un1, a3real const u0, a3real const u1, a3real const u2, a3real const u, const a3ui32 nodeCount);

//-----------------------------------------------------------------------------

// concat full hierarchy pose - already made in HierarchyState
a3i32 a3hierarchyPoseConcat(const a3_HierarchyPose* pose_out, const a3_HierarchyPose* pose_lhs, const a3_HierarchyPose* pose_rhs, const a3ui32 nodeCount);



#ifdef __cplusplus
}
#endif	// __cplusplus


#include "_inl/a3_HierarchyStateBlend.inl"


#endif	// !__ANIMAL3D_HIERARCHYSTATEBLEND_H