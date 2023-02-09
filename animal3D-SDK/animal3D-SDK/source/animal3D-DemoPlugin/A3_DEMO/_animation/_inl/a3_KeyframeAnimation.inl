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
	
	a3_KeyframeAnimation.inl
	Inline definitions for keyframe animation.
*/

#ifdef __ANIMAL3D_KEYFRAMEANIMATION_H
#ifndef __ANIMAL3D_KEYFRAMEANIMATION_INL
#define __ANIMAL3D_KEYFRAMEANIMATION_INL


//-----------------------------------------------------------------------------

// calculate clip duration as sum of keyframes' durations
inline a3i32 a3clipCalculateDuration(a3_Clip* clip)
{
	// error checking keyframes are valid
	if ((clip->first_keyframe >= clip->last_keyframe) || !clip)
		return -1;

	// loop through keyframes and sum up durations
	a3real tot_duration = 0;
	for (a3ui32 i = clip->first_keyframe; i <= clip->last_keyframe; i++)
		tot_duration += clip->keyframe_pool->keyframe[i].duration;

	// checking to prevent a /0
	if (tot_duration <= 0)
		return -1;

	// set and return duration
	clip->duration = tot_duration;
	clip->duration_inverse = 1 / tot_duration;

	// return duration
	return (a3i32)tot_duration;
}

// calculate keyframes' durations by distributing clip's duration
inline a3i32 a3clipDistributeDuration(a3_Clip* clip, const a3real newClipDuration)
{
	// checking that duration is valid
	if ((newClipDuration <= 0) || !clip)
		return -1;

	// assigning duration to clip
	clip->duration = newClipDuration;
	clip->duration_inverse = 1 / newClipDuration;

	// +1 to make it inclusive? maybe
	a3real keyframe_duration = (clip->last_keyframe - clip->first_keyframe + 1) * clip->duration_inverse;
	a3real inverse = 1 / keyframe_duration;

	// loop through keyframes and set durations
	for (a3ui32 i = clip->first_keyframe; i <= clip->last_keyframe; i++)
	{
		clip->keyframe_pool->keyframe[i].duration = keyframe_duration;
		clip->keyframe_pool->keyframe[i].duration_inverse = inverse;
	}

	// return duration
	return (a3i32)clip->duration;
}

a3i32 a3clipTransitionInit(a3_ClipTransition* clipTransition_out, const a3_ClipPool* clipPool, const a3ui32 clip_index)
{
	clipTransition_out->clipIndex_pool = clip_index;
	clipTransition_out->clip_pool = clipPool;
}
//-----------------------------------------------------------------------------


#endif	// !__ANIMAL3D_KEYFRAMEANIMATION_INL
#endif	// __ANIMAL3D_KEYFRAMEANIMATION_H