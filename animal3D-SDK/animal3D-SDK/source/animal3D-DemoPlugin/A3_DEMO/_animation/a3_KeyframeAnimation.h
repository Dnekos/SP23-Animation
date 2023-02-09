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
	
	a3_KeyframeAnimation.h
	Data structures for fundamental keyframe animation.
*/

#ifndef __ANIMAL3D_KEYFRAMEANIMATION_H
#define __ANIMAL3D_KEYFRAMEANIMATION_H


#include "animal3D-A3DM/a3math/a3vector.h"
#include "animal3D-A3DM/a3math/a3interpolation.h"


//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
typedef struct a3_Keyframe					a3_Keyframe;
typedef struct a3_KeyframePool				a3_KeyframePool;
typedef struct a3_Clip						a3_Clip;
typedef struct a3_ClipPool					a3_ClipPool;
typedef struct a3_ClipTransition			a3_ClipTransition;
#endif	// __cplusplus


//-----------------------------------------------------------------------------

// constant values
enum
{
	a3keyframeAnimation_nameLenMax = 32,
};


// description of single keyframe
// metaphor: moment
struct a3_Keyframe
{
	// index in keyframe pool
	a3ui32 index;

	// interval of time for which this keyframe is active; cannot be zero.
	a3real duration;

	// reciprocal of duration.
	a3real duration_inverse;

	// value of the sample described by a keyframe.
	a3ui32 data;
};

// pool of keyframe descriptors
struct a3_KeyframePool
{
	// array of keyframes
	a3_Keyframe *keyframe;

	// number of keyframes
	a3ui32 count;
};


// allocate keyframe pool
a3i32 a3keyframePoolCreate(a3_KeyframePool* keyframePool_out, const a3ui32 count);

// release keyframe pool
a3i32 a3keyframePoolRelease(a3_KeyframePool* keyframePool);

// initialize keyframe
a3i32 a3keyframeInit(a3_Keyframe* keyframe_out, const a3real duration, const a3ui32 value_x);


//-----------------------------------------------------------------------------

// data structure to describe a transition action
// Upon reaching or passing either terminus of a clip, 
// the controller should read the transition and follow its instructions
struct a3_ClipTransition
{
	// pointer to the pool of clips that contain the target clip
	const a3_ClipPool* clip_pool;

	// index of target clip in clip pool
	a3ui32 clipIndex_pool;

	// current time relative to start of clip
	a3real clip_time;

	// the active behavior of playback (forward, reverse, or stopped)
	a3i16 playback_direction;
};

// allocate clip pool
a3i32 a3clipTransitionInit(a3_ClipTransition* clipTransition_out, a3_ClipPool* clipPool, const a3ui32 clip_index);

//-----------------------------------------------------------------------------


// description of single clip
// metaphor: timeline
struct a3_Clip
{
	// clip name
	a3byte name[a3keyframeAnimation_nameLenMax];

	// index in clip pool
	a3ui32 index;

	// duration of clip; can be calculated as the sum of all of the referenced keyframes 
	// or set first and distributed uniformly across keyframes; cannot be zero
	a3real duration;

	// reciprocal of duration.
	a3real duration_inverse;

	// number of keyframes referenced by clip (including first and last).
	a3ui32 keyframe_count;

	// index of first keyframe in pool referenced by clip (see below)
	a3ui32 first_keyframe;
	// index of last keyframe in pool referenced by clip (see below)
	a3ui32 last_keyframe;

	// triggered when playing forward and the controller passes the end of a clip
	a3_ClipTransition forward_transition;

	// triggered when playing forward and the controller passes the end of a clip
	a3_ClipTransition reverse_transition;

	// pointer to the pool of keyframes containing those included in the set; 
	// within the array, the clip will be the sequence of keyframes from first to last.
	const a3_KeyframePool* keyframe_pool;
};

// group of clips
struct a3_ClipPool
{
	// array of clips
	a3_Clip* clip;

	// number of clips
	a3ui32 count;
};


// allocate clip pool
a3i32 a3clipPoolCreate(a3_ClipPool* clipPool_out, const a3ui32 count);

// release clip pool
a3i32 a3clipPoolRelease(a3_ClipPool* clipPool);

// initialize clip with first and last indices
a3i32 a3clipInit(a3_Clip* clip_out, const a3byte clipName[a3keyframeAnimation_nameLenMax], const a3_KeyframePool* keyframePool, const a3ui32 firstKeyframeIndex, const a3ui32 finalKeyframeIndex);

// get clip index from pool
a3i32 a3clipGetIndexInPool(const a3_ClipPool* clipPool, const a3byte clipName[a3keyframeAnimation_nameLenMax]);

// calculate clip duration as sum of keyframes' durations
a3i32 a3clipCalculateDuration(a3_Clip* clip);

// calculate keyframes' durations by distributing clip's duration
a3i32 a3clipDistributeDuration(a3_Clip* clip, const a3real newClipDuration);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#include "_inl/a3_KeyframeAnimation.inl"


#endif	// !__ANIMAL3D_KEYFRAMEANIMATION_H