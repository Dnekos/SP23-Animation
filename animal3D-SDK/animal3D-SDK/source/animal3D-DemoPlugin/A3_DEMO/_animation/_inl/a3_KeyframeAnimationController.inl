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
	
	a3_KeyframeAnimationController.h
	inline definitions for keyframe animation controller.
*/

#ifdef __ANIMAL3D_KEYFRAMEANIMATIONCONTROLLER_H
#ifndef __ANIMAL3D_KEYFRAMEANIMATIONCONTROLLER_INL
#define __ANIMAL3D_KEYFRAMEANIMATIONCONTROLLER_INL


//-----------------------------------------------------------------------------

// update clip controller
inline a3i32 a3clipControllerUpdate(a3_ClipController* clipCtrl, const a3real dt)
{
	//Pre-resolution 
	//Validate Clip Controller

	//Ensure we are taking in a positive time step.
	if (dt < 0 || !clipCtrl) return -1;

	//Apply time step to increment keyframe time and clip time by the time step.
	clipCtrl->keyframe_time += dt * clipCtrl->playback_direction;
	clipCtrl->clip_time += dt * clipCtrl->playback_direction;

	//Stand-in variable for our current clip in the clip pool.
	a3_Clip* current_clip = &clipCtrl->clip_pool->clip[clipCtrl->clip];

	//Resolution

	//Use our playback direction (1 is forward, -1 is reverse, 0 is stopped)
	//to determine the new keyframe time and clip time
	//Handle all 7 cases for playback
	if (clipCtrl->playback_direction > 0) 
	{
		//Forward
		//Case: Forward && Forward Skip
		//Advance to next keyframe time and increment keyframe index
		while (clipCtrl->keyframe_time >= current_clip->keyframe_pool->keyframe[clipCtrl->keyframe].duration)
		{
			clipCtrl->keyframe_time -= current_clip->keyframe_pool->keyframe[clipCtrl->keyframe].duration;
			clipCtrl->keyframe++;
			//Case: Forward Terminus
			//If passed end of clip, set clip time to start of clip by subtracting clip duration from clip time
			//Set keyframe index to first keyframe in clip
			if (clipCtrl->clip_time >= current_clip->duration && clipCtrl->keyframe == current_clip->last_keyframe)
			{
				// set new clip, if there is one
				if (current_clip->forward_transition.clipIndex_pool)
					a3clipControllerSetClip(clipCtrl, current_clip->forward_transition.clip_pool, 
						current_clip->forward_transition.clipIndex_pool);


				clipCtrl->clip_time -= current_clip->duration;
				clipCtrl->keyframe = current_clip->first_keyframe;
				
			}
		}
	}
	else if (clipCtrl->playback_direction < 0)
	{
		//Reverse
		//Case: Reverse && Reverse Skip
		//Rewind to last keyframe time and decrement keyframe index
		while (clipCtrl->keyframe_time < current_clip->keyframe_pool->keyframe[clipCtrl->keyframe].duration)
		{
			clipCtrl->keyframe_time += current_clip->keyframe_pool->keyframe[clipCtrl->keyframe].duration;
			clipCtrl->keyframe--;
			//Case: Reverse Terminus
			//If reached start of clip, set clip time to end of clip by adding clip duration to clip time
			//Set keyframe index to last keyframe in clip
			if (clipCtrl->clip_time < current_clip->duration && clipCtrl->keyframe == current_clip->first_keyframe)
			{
				// set new clip, if there is one
				if (current_clip->reverse_transition.clipIndex_pool)
					a3clipControllerSetClip(clipCtrl, current_clip->reverse_transition.clip_pool,
						current_clip->reverse_transition.clipIndex_pool);

				clipCtrl->clip_time += current_clip->duration;
				clipCtrl->keyframe = current_clip->last_keyframe;

			}
		}
	}
	//Stopped
	//Case: Paused
	else 
	{
		
	}

	//Post-Resolution
	
	//Normalize keyframe and clip time/parameters
	clipCtrl->keyframe_param = clipCtrl->keyframe_time * current_clip->duration_inverse;
	clipCtrl->clip_param = clipCtrl->clip_time * current_clip->duration_inverse;

	return 1;
}

// set clip to play
inline a3i32 a3clipControllerSetClip(a3_ClipController* clipCtrl, const a3_ClipPool* clipPool, const a3ui32 clipIndex_pool)
{
	//Validate input
	if (!clipCtrl || !clipPool || clipIndex_pool < 0) return -1;

	clipCtrl->clip_pool = clipPool;
	clipCtrl->clip = clipIndex_pool;
	clipCtrl->clip_time = 0;
	clipCtrl->keyframe_time = 0;
	clipCtrl->keyframe = clipPool->clip[clipIndex_pool].first_keyframe;
	clipCtrl->clip_param = 0;
	clipCtrl->keyframe_param = 0;

	return 1;
}


//-----------------------------------------------------------------------------


#endif	// !__ANIMAL3D_KEYFRAMEANIMATIONCONTROLLER_INL
#endif	// __ANIMAL3D_KEYFRAMEANIMATIONCONTROLLER_H