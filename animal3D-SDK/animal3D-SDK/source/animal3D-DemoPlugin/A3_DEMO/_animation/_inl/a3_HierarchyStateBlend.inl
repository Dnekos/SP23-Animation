#include "a3_HierarchyStateBlend.h"
#include <math.h>
#include <stdlib.h>
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

inline a3_SpatialPose* a3clipOpLERP(a3_HierarchyPoseGroup* const poseGroup, a3_Clip* const clip0, a3_Clip* const clip1, a3real const u)
{
	if(poseGroup && clip0 && clip1)
	{
		//Perform Key-Pose interpolation on each clip???
		a3_SpatialPose* pose;
		a3_SpatialPose* pose0 = poseGroup->hpose->pose + clip0->index;
		a3_SpatialPose* pose1 = poseGroup->hpose->pose + clip1->index;
		a3spatialPoseOpLERP(pose, pose0, pose1, u);
		return pose;
	}
	return 0;
}

inline a3_SpatialPose* a3clipOpADD(a3_HierarchyPoseGroup* const poseGroup, a3_Clip* const clip0, a3_Clip* const clip1)
{
	if (poseGroup && clip0 && clip1)
	{
		a3_SpatialPose* pose;
		a3_SpatialPose* pose0 = poseGroup->hpose->pose + clip0->index;
		a3_SpatialPose* pose1 = poseGroup->hpose->pose + clip1->index;
		a3spatialPoseOpConcat(pose, pose0, pose1);
		return pose;
	}
	return 0;
}

inline a3_SpatialPose* a3clipOpSCALE(a3_HierarchyPoseGroup* const poseGroup, a3_Clip* const clip0, a3real const u)
{
	if (poseGroup && clip0)
	{
		a3_SpatialPose* pose = poseGroup->hpose->pose + clip0->index;
		a3spatialPoseOpScale(pose, u);
		return pose;
	}
	return 0;
}

// pointer-based reset/identity operation for single spatial pose
inline a3_SpatialPose* a3spatialPoseOpIdentity(a3_SpatialPose* pose_out)
{
	if (pose_out) 
	{
		pose_out->transformMat = a3mat4_identity;
		pose_out->rotate = a3vec4_zero;
		pose_out->translate = a3vec4_zero;
		pose_out->scale = a3vec4_one;

		// done
		return pose_out;
	}
	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpConstruct(a3_SpatialPose* pose_out, a3vec3 rotation, a3vec3 scale, a3vec3 translation)
{
	// TODO: How do we validate the controls? Also, why are spatial poses vec4s??
	if (pose_out)
	{
		a3spatialPoseSetRotation(pose_out, rotation.x, rotation.y, rotation.z);
		a3spatialPoseSetScale(pose_out, scale.x, scale.y, scale.z);
		a3spatialPoseSetTranslation(pose_out, translation.x, translation.y, translation.z);
	}

	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpCopy(a3_SpatialPose* pose_out, a3_SpatialPose const* pose_in)
{
	if (pose_out && pose_in)
	{
		pose_out->translate = pose_in->translate;
		pose_out->transformMat = pose_in->transformMat;
		//pose_out->orientation = pose_in->orientation;
		pose_out->scale = pose_in->scale;
		return pose_out;
	}
	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpInvert(a3_SpatialPose* pose_in)
{
	if (pose_in)
	{
		pose_in->rotate.x = -pose_in->rotate.x;
		pose_in->rotate.y = -pose_in->rotate.y;
		pose_in->rotate.z = -pose_in->rotate.z;
		if (pose_in->scale.x != 0)
			pose_in->scale.x = 1 / pose_in->scale.x;
		if (pose_in->scale.y != 0)
			pose_in->scale.y = 1 / pose_in->scale.y;
		if (pose_in->scale.z != 0)
			pose_in->scale.z = 1 / pose_in->scale.z;
		pose_in->translate.x = -pose_in->translate.x;
		pose_in->translate.y = -pose_in->translate.y;
		pose_in->translate.z = -pose_in->translate.z;
		return pose_in;
	}
	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpConcat(a3_SpatialPose* pose_out, a3_SpatialPose const* lhs, a3_SpatialPose const* rhs)
{
	if (pose_out && lhs && rhs)
	{
		pose_out->rotate.x = lhs->rotate.x + rhs->rotate.x;
		pose_out->rotate.y = lhs->rotate.y + rhs->rotate.y;
		pose_out->rotate.z = lhs->rotate.z + rhs->rotate.z;
		pose_out->scale.x = lhs->scale.x * rhs->scale.x;
		pose_out->scale.y = lhs->scale.y * rhs->scale.y;
		pose_out->scale.z = lhs->scale.z * rhs->scale.z;
		pose_out->translate.x = lhs->translate.x + rhs->translate.x;
		pose_out->translate.y = lhs->translate.y + rhs->translate.y;
		pose_out->translate.z = lhs->translate.z + rhs->translate.z;
		return pose_out;
	}

	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpNEAR(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3real const u)
{
	if (pose_out && pose0 && pose1)
	{
		if (u < 0.5f)
		{
			a3spatialPoseOpCopy(pose_out, pose0);
			return pose_out;
		}
		else
		{
			a3spatialPoseOpCopy(pose_out, pose1);
			return pose_out;
		}
	}
	return 0;
}

// pointer-based LERP operation for single spatial pose
inline a3_SpatialPose* a3spatialPoseOpLERP(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3real const u)
{
	if (pose_out && pose0 && pose1)
	{
		pose_out->rotate.x =		a3lerp(pose0->rotate.x, pose1->rotate.x, u);
		pose_out->rotate.y =		a3lerp(pose0->rotate.y, pose1->rotate.y, u);
		pose_out->rotate.z =		a3lerp(pose0->rotate.z, pose1->rotate.z, u);
		// validate denominators
		if (pose0->scale.x != 0)
			pose_out->scale.x =			(a3real)pow(pose1->scale.x / pose0->scale.x, u) * pose0->scale.x;
		if (pose0->scale.y != 0)
			pose_out->scale.y =			(a3real)pow(pose1->scale.y / pose0->scale.y, u) * pose0->scale.y;
		if (pose0->scale.z != 0)
			pose_out->scale.z =			(a3real)pow(pose1->scale.z / pose0->scale.z, u) * pose0->scale.z;
		pose_out->translate.x =	a3lerp(pose0->translate.x, pose1->translate.x, u);
		pose_out->translate.y =	a3lerp(pose0->translate.y, pose1->translate.y, u);
		pose_out->translate.z =	a3lerp(pose0->translate.z, pose1->translate.z, u);
		return pose_out;
	}
	return 0;
}

a3_SpatialPose* a3spatialPoseOpSmoothStep(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3real const u)
{
	if (pose_out && pose0 && pose1)
	{
		if (u <= 0)
			return a3spatialPoseOpCopy(pose_out, pose0);
		if (u >= 1)
			return a3spatialPoseOpCopy(pose_out, pose1);

		return a3spatialPoseOpLERP(pose_out, pose0, pose1, u * u * (3 - 2 * u));
	}
	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpCUBIC(a3_SpatialPose* pose_out, a3_SpatialPose const* posen1, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3_SpatialPose const* pose2, a3real const u)
{
	if(pose_out && posen1 && pose0 && pose1 && pose2)
	{
		// Check Slide 90 for Catmull
		// Check Slide 108 for Hermite
		a3_SpatialPose* t_posen1, *t_pose0, *t_pose1, *t_pose2;
		t_posen1 = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));
		t_pose0 = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));
		t_pose1 = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));
		t_pose2 = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));
		t_posen1 = a3spatialPoseOpCopy(t_posen1, posen1);
		t_pose0 = a3spatialPoseOpCopy(t_pose0, pose0);
		t_pose1 = a3spatialPoseOpCopy(t_pose1, pose1);
		t_pose2 = a3spatialPoseOpCopy(t_pose2, pose2);


		pose_out = a3spatialPoseOpScale(
			a3spatialPoseOpConcat(pose_out, 
				a3spatialPoseOpConcat(pose_out, 
					a3spatialPoseOpScale(t_posen1, -u + 2 * u * u - u * u * u),
					a3spatialPoseOpScale(t_pose0, 2 - 5 * u * u + 3 * u * u * u)),
				a3spatialPoseOpConcat(t_pose1, 
					a3spatialPoseOpScale(t_pose1, u + 4 * u * u - 3u * u * u),
					a3spatialPoseOpScale(t_pose2, -u * u + u * u * u))), 0.5f);

		free(t_posen1);
		free(t_pose0);
		free(t_pose1);
		free(t_pose2);

		return pose_out;
	}
	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpDeconcat(a3_SpatialPose* pose_out, a3_SpatialPose const* lhs, a3_SpatialPose const* rhs)
{
	if (pose_out && lhs && rhs)
	{
		pose_out->rotate.x = lhs->rotate.x - rhs->rotate.x;
		pose_out->rotate.y = lhs->rotate.y - rhs->rotate.y;
		pose_out->rotate.z = lhs->rotate.z - rhs->rotate.z;
		if (rhs->scale.x != 0)
			pose_out->scale.x = lhs->scale.x / rhs->scale.x;
		if (rhs->scale.y != 0)
			pose_out->scale.y = lhs->scale.y / rhs->scale.y;
		if (rhs->scale.z != 0)
			pose_out->scale.z = lhs->scale.z / rhs->scale.z;
		pose_out->translate.x = lhs->translate.x - rhs->translate.x;
		pose_out->translate.y = lhs->translate.y - rhs->translate.y;
		pose_out->translate.z = lhs->translate.z - rhs->translate.z;

		return pose_out;
	}

	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpScale(a3_SpatialPose* pose_out, a3real const u)
{
	if (pose_out) 
	{

		pose_out->rotate.x *= u;
		pose_out->rotate.y *= u;
		pose_out->rotate.z *= u;
		pose_out->scale.x = (a3real)powf(pose_out->scale.x, u);
		pose_out->scale.y = (a3real)powf(pose_out->scale.y, u);
		pose_out->scale.z = (a3real)powf(pose_out->scale.z, u);
		pose_out->translate.x *= u;
		pose_out->translate.y *= u;
		pose_out->translate.z *= u;

		return pose_out;

	}
	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpDescale(a3_SpatialPose* pose_out, a3real const u)
{
	if (pose_out)
	{		
		if (u == 0)
			return a3spatialPoseOpIdentity(pose_out);

		pose_out->rotate.x *= -u;
		pose_out->rotate.y *= -u;
		pose_out->rotate.z *= -u;
		pose_out->scale.x = (a3real)powf(pose_out->scale.x, 1 / u);
		pose_out->scale.y = (a3real)powf(pose_out->scale.y, 1 / u);
		pose_out->scale.z = (a3real)powf(pose_out->scale.z, 1 / u);
		pose_out->translate.x *=  -u;
		pose_out->translate.y *=  -u;
		pose_out->translate.z *=  -u;


		return pose_out;
	}
	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpTriangular(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3_SpatialPose const* pose2, a3real const u1, a3real const u2)
{
	if (pose_out && pose0 && pose1 && pose2)
	{
		a3real u3 = 1 - u2 - u1;

		pose_out->rotate.x = pose0->rotate.x * u1 + pose1->rotate.x * u2 + pose2->rotate.x * u3;
		pose_out->rotate.y = pose0->rotate.y * u1 + pose1->rotate.y * u2 + pose2->rotate.y * u3;
		pose_out->rotate.z = pose0->rotate.z * u1 + pose1->rotate.z * u2 + pose2->rotate.z * u3;

		pose_out->scale.x = (a3real)powf(pose0->scale.x, u1) * (a3real)powf(pose1->scale.x, u2) * (a3real)powf(pose2->scale.x, u3);
		pose_out->scale.y = (a3real)powf(pose0->scale.y, u1) * (a3real)powf(pose1->scale.y, u2) * (a3real)powf(pose2->scale.y, u3);
		pose_out->scale.z = (a3real)powf(pose0->scale.z, u1) * (a3real)powf(pose1->scale.z, u2) * (a3real)powf(pose2->scale.z, u3);

		pose_out->translate.x = pose0->translate.x * u1 + pose1->translate.x * u2 + pose2->translate.x * u3;
		pose_out->translate.y = pose0->translate.y * u1 + pose1->translate.y * u2 + pose2->translate.y * u3;
		pose_out->translate.z = pose0->translate.z * u1 + pose1->translate.z * u2 + pose2->translate.z * u3;

		return pose_out;
	}
	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpBiNearest(a3_SpatialPose* pose_out, a3_SpatialPose const* pose00, a3_SpatialPose const* pose01, a3_SpatialPose const* pose10, a3_SpatialPose const* pose11, a3real const u0, a3real const u1, a3real const u)
{
	if(pose_out && pose00 && pose01 && pose10 && pose11)
	{
		a3_SpatialPose* lhs, * rhs;
		lhs = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));
		rhs = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));

		pose_out = a3spatialPoseOpNEAR(pose_out, a3spatialPoseOpNEAR(lhs, pose00, pose01, u0), a3spatialPoseOpNEAR(rhs, pose10, pose11, u1), u);
		free(lhs);
		free(rhs);

		return pose_out;
	}
	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpBiLinear(a3_SpatialPose* pose_out, a3_SpatialPose const* pose00, a3_SpatialPose const* pose01, a3_SpatialPose const* pose10, a3_SpatialPose const* pose11, a3real const u0, a3real const u1, a3real const u)
{
	if (pose_out && pose00 && pose01 && pose10 && pose11) 
	{
		a3_SpatialPose* lhs, * rhs;
		lhs = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));
		rhs = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));

		pose_out = a3spatialPoseOpLERP(pose_out, a3spatialPoseOpLERP(lhs, pose00, pose01, u0), a3spatialPoseOpLERP(rhs, pose10, pose11, u0), u1);
		
		free(lhs);
		free(rhs);

		// Check Slide 34 of interpolation slides
		return pose_out;
	}
	return 0;
}

inline a3_SpatialPose* a3spatialPoseOpBiCubic(a3_SpatialPose* pose_out, a3_SpatialPose const* posen1n1, a3_SpatialPose const* posen10, a3_SpatialPose const* posen11, a3_SpatialPose const* posen12, a3_SpatialPose const* pose0n1, a3_SpatialPose const* pose00, a3_SpatialPose const* pose01, a3_SpatialPose const* pose02, a3_SpatialPose const* pose1n1, a3_SpatialPose const* pose10, a3_SpatialPose const* pose11, a3_SpatialPose const* pose12, a3_SpatialPose const* pose2n1, a3_SpatialPose const* pose20, a3_SpatialPose const* pose21, a3_SpatialPose const* pose22, a3real const un1, a3real const u0, a3real const u1, a3real const u2, a3real const u)
{
	if(pose_out 
		&& posen1n1 && posen10 && posen11 && posen12
		&& pose0n1 && pose00 && pose01 && pose02
		&& pose1n1 && pose10 && pose11 && pose12
		&& pose2n1 && pose20 && pose21 && pose22)
	{
		a3_SpatialPose* out0, * out1, * out2, * out3;
		out0 = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));
		out1 = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));
		out2 = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));
		out3 = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose));

		pose_out = a3spatialPoseOpCUBIC(pose_out,
			a3spatialPoseOpCUBIC(out0, posen1n1, posen10, posen11, posen12, un1),
			a3spatialPoseOpCUBIC(out1, pose0n1, pose00, pose01, pose02, u0),
			a3spatialPoseOpCUBIC(out2, pose1n1, pose10, pose11, pose12, u1),
			a3spatialPoseOpCUBIC(out3, pose2n1, pose20, pose21, pose22, u2),
			u);

		free(out0);
		free(out1); 
		free(out2);
		free(out3);
		return pose_out;
	}
	return 0;
}

//-----------------------------------------------------------------------------

// data-based reset/identity
inline a3_SpatialPose a3spatialPoseDOpIdentity()
{
	a3_SpatialPose result = { a3mat4_identity /*, ...*/ };
	result.rotate.x =0;
	result.rotate.y =0;
	result.rotate.z =0;

	result.scale.x = 1;
	result.scale.y = 1;
	result.scale.z = 1;

	result.translate.x = 0;
	result.translate.y = 0;
	result.translate.z = 0;


	return result;
}

inline a3_SpatialPose a3spatialPoseDOpConstruct(a3vec3 rotation, a3vec3 scale, a3vec3 translation)
{
	a3_SpatialPose result = { 0 };
	result.rotate.x = a3trigValid_sind(rotation.x);
	result.rotate.y = a3trigValid_sind(rotation.y);
	result.rotate.z = a3trigValid_sind(rotation.z);

	result.scale.x = scale.x;
	result.scale.y = scale.y;
	result.scale.z = scale.z;

	result.translate.x = translation.x;
	result.translate.y = translation.y;
	result.translate.z = translation.z;


	return result;
}

inline a3_SpatialPose a3spatialPoseDOpCopy(a3_SpatialPose pose_in)
{
	a3_SpatialPose result = { 0 };
	result.translate = pose_in.translate;
	result.transformMat = pose_in.transformMat;
	//result.orientation = pose_in.orientation;
	result.scale = pose_in.scale;
	return result;
}

inline a3_SpatialPose a3spatialPoseDOpInvert(a3_SpatialPose pose_in)
{
	a3_SpatialPose out = { 0 };
	out.rotate.x = -pose_in.rotate.x;
	out.rotate.y = -pose_in.rotate.y;
	out.rotate.z = -pose_in.rotate.z;
	if (pose_in.scale.x != 0)
		out.scale.x = 1 / pose_in.scale.x;
	if (pose_in.scale.y != 0)
		out.scale.y = 1 / pose_in.scale.y;
	if (pose_in.scale.z != 0)
		out.scale.z = 1 / pose_in.scale.z;
	out.translate.x = -pose_in.translate.x;
	out.translate.y = -pose_in.translate.y;
	out.translate.z = -pose_in.translate.z;
	return out;
}

inline a3_SpatialPose a3spatialPoseDOpConcat(a3_SpatialPose const lhs, a3_SpatialPose const rhs)
{
	a3_SpatialPose out;
	out.rotate.x = lhs.rotate.x + rhs.rotate.x;
	out.rotate.y = lhs.rotate.y + rhs.rotate.y;
	out.rotate.z = lhs.rotate.z + rhs.rotate.z;
	out.scale.x = lhs.scale.x * rhs.scale.x;
	out.scale.y = lhs.scale.y * rhs.scale.y;
	out.scale.z = lhs.scale.z * rhs.scale.z;
	out.translate.x = lhs.translate.x + rhs.translate.x;
	out.translate.y = lhs.translate.y + rhs.translate.y;
	out.translate.z = lhs.translate.z + rhs.translate.z;
	return out;
}

inline a3_SpatialPose a3spatialPoseDOpNEAR(a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3real const u)
{
	if (u < 0.5f)
		return pose0;
	else
		return pose1;
}

// data-based LERP
inline a3_SpatialPose a3spatialPoseDOpLERP(a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3real const u)
{
	a3_SpatialPose result = { 0 };

	result.rotate.x = a3lerp(pose0.rotate.x, pose1.rotate.x, u);
	result.rotate.y = a3lerp(pose0.rotate.y, pose1.rotate.y, u);
	result.rotate.z = a3lerp(pose0.rotate.z, pose1.rotate.z, u);

	if (pose0.scale.x != 0)
		result.scale.x = (a3real)pow(pose1.scale.x / pose0.scale.x, u) * pose0.scale.x;
	if (pose0.scale.y != 0)
		result.scale.y = (a3real)pow(pose1.scale.y / pose0.scale.y, u) * pose0.scale.y;
	if (pose0.scale.z != 0)
		result.scale.z = (a3real)pow(pose1.scale.z / pose0.scale.z, u) * pose0.scale.z;
	result.translate.x = a3lerp(pose0.translate.x, pose1.translate.x, u);
	result.translate.y = a3lerp(pose0.translate.y, pose1.translate.y, u);
	result.translate.z = a3lerp(pose0.translate.z, pose1.translate.z, u);

	// done
	return result;
}

inline a3_SpatialPose a3spatialPoseDOpCUBIC(a3_SpatialPose const posen1, a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3_SpatialPose const pose2, a3real const u)
{
	return a3spatialPoseDOpScale(
		a3spatialPoseDOpConcat(
			a3spatialPoseDOpConcat(
				a3spatialPoseDOpScale(posen1, -u + 2 * u * u - u * u * u),
				a3spatialPoseDOpScale(pose0, 2 - 5 * u * u + 3 * u * u * u)),
			a3spatialPoseDOpConcat(
				a3spatialPoseDOpScale(pose1, u + 4 * u * u - 3u * u * u),
				a3spatialPoseDOpScale(pose2, -u * u + u * u * u))), 0.5f);
}

inline a3_SpatialPose a3spatialPoseDOpDeconcat(a3_SpatialPose const lhs, a3_SpatialPose const rhs)
{
	a3_SpatialPose result = { 0 };
	result.rotate.x = lhs.rotate.x - rhs.rotate.x;
	result.rotate.y = lhs.rotate.y - rhs.rotate.y;
	result.rotate.z = lhs.rotate.z - rhs.rotate.z;
	if (rhs.scale.x != 0)
		result.scale.x = lhs.scale.x / rhs.scale.x;
	if (rhs.scale.y != 0)
		result.scale.y = lhs.scale.y / rhs.scale.y;
	if (rhs.scale.z != 0)
		result.scale.z = lhs.scale.z / rhs.scale.z;
	result.translate.x = lhs.translate.x - rhs.translate.x;
	result.translate.y = lhs.translate.y - rhs.translate.y;
	result.translate.z = lhs.translate.z - rhs.translate.z;

	return result;
}

inline a3_SpatialPose a3spatialPoseDOpScale(a3_SpatialPose lhs, a3real const u)
{
	a3_SpatialPose result = lhs;

	result.rotate.x *= u;
	result.rotate.y *= u;
	result.rotate.z *= u;
	result.scale.x = (a3real)powf(lhs.scale.x, u);
	result.scale.y = (a3real)powf(lhs.scale.y, u);
	result.scale.z = (a3real)powf(lhs.scale.z, u);
	result.translate.x *= u;
	result.translate.y *= u;
	result.translate.z *= u;


	return result;
}

inline a3_SpatialPose a3spatialPoseDOpTriangular(a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3_SpatialPose const pose2, a3real const u1, a3real const u2)
{
	a3real u3 = 1 - u2 - u1;

	return a3spatialPoseDOpConcat(a3spatialPoseDOpConcat(a3spatialPoseDOpScale(pose0, u1), a3spatialPoseDOpScale(pose1, u2)), a3spatialPoseDOpScale(pose2, u3));
}

inline a3_SpatialPose a3spatialPoseDOpBiNearest(a3_SpatialPose const pose00, a3_SpatialPose const pose01, a3_SpatialPose const pose10, a3_SpatialPose const pose11, a3real const u0, a3real const u1, a3real const u)
{
	return a3spatialPoseDOpNEAR(a3spatialPoseDOpNEAR(pose00, pose01, u0), a3spatialPoseDOpNEAR(pose10, pose11, u1), u);
}

inline a3_SpatialPose a3spatialPoseDOpBiLinear(a3_SpatialPose const pose00, a3_SpatialPose const pose01, a3_SpatialPose const pose10, a3_SpatialPose const pose11, a3real const u0, a3real const u1, a3real const u)
{
	return a3spatialPoseDOpLERP(a3spatialPoseDOpLERP(pose00, pose01, u0), a3spatialPoseDOpLERP(pose10, pose11, u0), u1);
}

inline a3_SpatialPose a3spatialPoseDOpBiCubic(a3_SpatialPose const posen1n1, a3_SpatialPose const posen10, a3_SpatialPose const posen11, a3_SpatialPose const posen12, a3_SpatialPose const pose0n1, a3_SpatialPose const pose00, a3_SpatialPose const pose01, a3_SpatialPose const pose02, a3_SpatialPose const pose1n1, a3_SpatialPose const pose10, a3_SpatialPose const pose11, a3_SpatialPose const pose12, a3_SpatialPose const pose2n1, a3_SpatialPose const pose20, a3_SpatialPose const pose21, a3_SpatialPose const pose22, a3real const un1, a3real const u0, a3real const u1, a3real const u2, a3real const u)
{
	return a3spatialPoseDOpCUBIC(
		a3spatialPoseDOpCUBIC(posen1n1, posen10, posen11, posen12, un1),
		a3spatialPoseDOpCUBIC(pose0n1, pose00, pose01, pose02, u0),
		a3spatialPoseDOpCUBIC(pose1n1, pose10, pose11, pose12, u1),
		a3spatialPoseDOpCUBIC(pose2n1, pose20, pose21, pose22, u2),
		u);
}

//-----------------------------------------------------------------------------

// pointer-based reset/identity operation for hierarchical pose
inline a3_HierarchyPose* a3hierarchyPoseOpIdentity(a3_HierarchyPose* pose_out, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpIdentity(pose_out->pose + i);
		return pose_out;
	}
	// done
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpConstruct(a3_HierarchyPose* pose_out, a3vec3 rotation, a3vec3 scale, a3vec3 translation, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpConstruct(pose_out->pose + i, rotation, scale, translation);
		return pose_out;
	}
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpCopy(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose_in, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpCopy(pose_out->pose + i, pose_in->pose + i);
		return pose_out;
	}
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpInvert(a3_HierarchyPose* pose_out, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpInvert(pose_out->pose + i);
		return pose_out;
	}
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpConcat(a3_HierarchyPose* pose_out, a3_HierarchyPose const* lhs, a3_HierarchyPose const* rhs, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpConcat(pose_out->pose + i, lhs->pose + i, rhs->pose + i);
		return pose_out;
	}
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpNEAR(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, a3real const u, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpNEAR(pose_out->pose + i, pose0->pose + i, pose1->pose + i, u);
		return pose_out;
	}
	return 0;
}

// pointer-based LERP operation for hierarchical pose
inline a3_HierarchyPose* a3hierarchyPoseOpLERP(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, a3real const u, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpLERP(pose_out->pose + i, pose0->pose + i, pose1->pose + i, u);
		return pose_out;
	}
	return 0;
}

a3_HierarchyPose* a3hierarchyPoseOpSmoothStep(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1,
	a3real const u, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpSmoothStep(pose_out->pose + i, pose0->pose + i, pose1->pose + i, u);
		return pose_out;
	}
	return 0;
}


inline a3_HierarchyPose* a3hierarchyPoseOpCUBIC(a3_HierarchyPose* pose_out, a3_HierarchyPose const* posen1, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, a3_HierarchyPose const* pose2, a3real const u, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpCUBIC(pose_out->pose + i, posen1->pose + i, pose0->pose + i, pose1->pose + i, pose2->pose + i, u);
		return pose_out;
	}
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpDeconcat(a3_HierarchyPose* pose_out, a3_HierarchyPose const* lhs, a3_HierarchyPose const* rhs, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpDeconcat(pose_out->pose + i, lhs->pose + i, rhs->pose + i);
		return pose_out;
	}
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpScale(a3_HierarchyPose* pose_out, a3real const u, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpScale(pose_out->pose + i, u);
		return pose_out;
	}
	return 0;
}

a3_HierarchyPose* a3hierarchyPoseOpDescale(a3_HierarchyPose* pose_out, a3real const u, const a3ui32 nodeCount);
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpDescale(pose_out->pose + i, u);
		return pose_out;
	}
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpTriangular(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, a3_HierarchyPose const* pose2, a3real const u1, a3real const u2, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpTriangular(pose_out->pose + i, pose0->pose + i, pose1->pose + i, pose2->pose + i, u1, u2);
		return pose_out;
	}
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpBiNearest(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose00, a3_HierarchyPose const* pose01, a3_HierarchyPose const* pose10, a3_HierarchyPose const* pose11, a3real const u0, a3real const u1, a3real const u, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpBiNearest(pose_out->pose + i, pose00->pose + i, pose01->pose + i, pose10->pose + i, pose11->pose + i, u0, u1, u);
		return pose_out;
	}
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpBiLinear(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose00, a3_HierarchyPose const* pose01, a3_HierarchyPose const* pose10, a3_HierarchyPose const* pose11, a3real const u0, a3real const u1, a3real const u, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpBiLinear(pose_out->pose + i, pose00->pose + i, pose01->pose + i, pose10->pose + i, pose11->pose + i, u0, u1, u);
		return pose_out;
	}
	return 0;
}

inline a3_HierarchyPose* a3hierarchyPoseOpBiCubic(a3_HierarchyPose* pose_out, a3_HierarchyPose const* posen1n1, a3_HierarchyPose const* posen10, a3_HierarchyPose const* posen11, a3_HierarchyPose const* posen12, a3_HierarchyPose const* pose0n1, a3_HierarchyPose const* pose00, a3_HierarchyPose const* pose01, a3_HierarchyPose const* pose02, a3_HierarchyPose const* pose1n1, a3_HierarchyPose const* pose10, a3_HierarchyPose const* pose11, a3_HierarchyPose const* pose12, a3_HierarchyPose const* pose2n1, a3_HierarchyPose const* pose20, a3_HierarchyPose const* pose21, a3_HierarchyPose const* pose22, a3real const un1, a3real const u0, a3real const u1, a3real const u2, a3real const u, const a3ui32 nodeCount)
{
	if (pose_out && nodeCount)
	{
		a3index i;
		for (i = 0; i < nodeCount; ++i)
			a3spatialPoseOpBiCubic(pose_out->pose + i, 
				posen1n1->pose + i, posen10->pose + i, posen11->pose + i, posen12->pose + i,
				pose0n1->pose + i, pose00->pose + i, pose01->pose + i, pose02->pose + i, 
				pose1n1->pose + i, pose10->pose + i, pose11->pose + i, pose12->pose + i, 
				pose2n1->pose + i, pose20->pose + i, pose21->pose + i, pose22->pose + i, 
				un1, u0, u1, u2, u);
		return pose_out;
	}
	return 0;
}

//-----------------------------------------------------------------------------


#endif	// !__ANIMAL3D_HIERARCHYSTATEBLEND_INL
#endif	// __ANIMAL3D_HIERARCHYSTATEBLEND_H