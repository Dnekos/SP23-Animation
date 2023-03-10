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
	
	a3_KeyframeAnimation.c
	Implementation of keyframe animation interfaces.
*/

#include "../a3_KeyframeAnimation.h"

#include <stdlib.h>
#include <string.h>


// macros to help with names
#define A3_CLIP_DEFAULTNAME		("unnamed clip")
#define A3_CLIP_SEARCHNAME		((clipName && *clipName) ? clipName : A3_CLIP_DEFAULTNAME)


//-----------------------------------------------------------------------------
//VALIDATE

// allocate keyframe pool
a3i32 a3keyframePoolCreate(a3_KeyframePool* keyframePool_out, const a3ui32 count)
{
	if (count < 0) return -1;

	// set count
	keyframePool_out->count = count;

	// allocate memory for keyframes
	keyframePool_out->keyframe = (a3_Keyframe*) malloc(count * sizeof(a3_Keyframe));

	return 1;
}

// release keyframe pool
a3i32 a3keyframePoolRelease(a3_KeyframePool* keyframePool)
{
	if (!keyframePool) return -1;
	free(keyframePool->keyframe);

	return -1;
}

// initialize keyframe
a3i32 a3keyframeInit(a3_Keyframe* keyframe_out, const a3real duration, const a3ui32 value_x)
{
	if (!keyframe_out || duration <= 0) return -1;
	// set keyframe values
	keyframe_out->duration = duration;
	keyframe_out->duration_inverse = duration / 1.0f;
	keyframe_out->data = value_x;

	return 1;
}


// allocate clip pool
a3i32 a3clipPoolCreate(a3_ClipPool* clipPool_out, const a3ui32 count)
{
	if (count < 0) return -1;

	// set count
	clipPool_out->count = count;

	// allocate memory for keyframes
	clipPool_out->clip = (a3_Clip*)malloc(count * sizeof(a3_Clip));

	return 1;
}

// release clip pool
a3i32 a3clipPoolRelease(a3_ClipPool* clipPool)
{
	if (!clipPool) return -1;

	free(clipPool->clip);

	return 1;
}

// initialize clip with first and last indices
a3i32 a3clipInit(a3_Clip* clip_out, const a3byte clipName[a3keyframeAnimation_nameLenMax], const a3_KeyframePool* keyframePool, const a3ui32 firstKeyframeIndex, const a3ui32 finalKeyframeIndex)
{
	if (!clip_out || !keyframePool || firstKeyframeIndex < 0 || finalKeyframeIndex < 0 || firstKeyframeIndex > finalKeyframeIndex) return -1;
	// set variables
	strncpy(clip_out->name, clipName, a3keyframeAnimation_nameLenMax);
	clip_out->keyframe_pool = keyframePool;
	clip_out->first_keyframe = firstKeyframeIndex;
	clip_out->last_keyframe = finalKeyframeIndex;

	return 1;
}

// get clip index from pool
a3i32 a3clipGetIndexInPool(const a3_ClipPool* clipPool, const a3byte clipName[a3keyframeAnimation_nameLenMax])
{
	if (!clipPool) return -1;
	// loop through clips and check for correct name
	for (a3ui32 i = 0; i < clipPool->count; i++)
		if (clipPool->clip[i].name == clipName)
			return i;

	// return -1 if didn't find correct clip
	return -1;
}


//-----------------------------------------------------------------------------
