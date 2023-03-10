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

	a3_DemoMode0_Starter_idle-input.c
	Demo mode implementations: starter scene.

	********************************************
	*** INPUT FOR STARTER SCENE MODE         ***
	********************************************
*/

//-----------------------------------------------------------------------------

#include "../a3_DemoMode0_Starter.h"

//typedef struct a3_DemoState a3_DemoState;
#include "../a3_DemoState.h"

#include "../_a3_demo_utilities/a3_DemoMacros.h"


//-----------------------------------------------------------------------------
// CALLBACKS

// main demo mode callback
void a3starter_input_keyCharPress(a3_DemoState const* demoState, a3_DemoMode0_Starter* demoMode, a3i32 const asciiKey, a3i32 const state)
{
	switch (asciiKey)
	{
		// toggle render program
		a3demoCtrlCasesLoop(demoMode->render, starter_render_max, 'k', 'j');

		// toggle display program
		a3demoCtrlCasesLoop(demoMode->display, starter_display_max, 'K', 'J');

		// toggle active camera
		a3demoCtrlCasesLoop(demoMode->activeCamera, starter_camera_max, 'v', 'c');

		// toggle pipeline mode
		a3demoCtrlCasesLoop(demoMode->pipeline, starter_pipeline_max, ']', '[');

		// toggle target
		a3demoCtrlCasesLoop(demoMode->targetIndex[demoMode->pass], demoMode->targetCount[demoMode->pass], '}', '{');

		// toggle pass to display
		a3demoCtrlCasesLoop(demoMode->pass, starter_pass_max, ')', '(');
	}
}

void a3starter_input_keyCharHold(a3_DemoState const* demoState, a3_DemoMode0_Starter* demoMode, a3i32 const asciiKey, a3i32 const state)
{
//	switch (asciiKey)
//	{
//
//	}
}


//-----------------------------------------------------------------------------

void a3demo_input_controlProjector(
	a3_DemoState* demoState, a3_DemoProjector* projector,
	a3f64 const dt, a3real ctrlMoveSpeed, a3real ctrlRotateSpeed, a3real ctrlZoomSpeed);

void a3starter_input(a3_DemoState* demoState, a3_DemoMode0_Starter* demoMode, a3f64 const dt)
{
	a3_DemoProjector* projector = demoMode->projector + demoMode->activeCamera;

	//active clip controller
	//a3_ClipController const* activeClipController = demoMode->clipController;

	// right click to ray pick
	if (a3mouseGetState(demoState->mouse, a3mouse_right) == a3input_down)
	{
		// get window coordinates
		a3i32 const x = a3mouseGetX(demoState->mouse) + demoState->frameBorder;
		a3i32 const y = a3mouseGetY(demoState->mouse) + demoState->frameBorder;

		// transform to NDC
		a3vec4 coord = a3vec4_one;
		coord.x = +((a3real)x * demoState->frameWidthInv * a3real_two - a3real_one);
		coord.y = -((a3real)y * demoState->frameHeightInv * a3real_two - a3real_one);
		coord.z = -a3real_one;

		// transform to view space
		a3real4Real4x4Mul(projector->projectionMatInv.m, coord.v);
		a3real4DivS(coord.v, coord.w);

		// transform to world space
		a3real4Real4x4Mul(projector->sceneObject->modelMat.m, coord.v);
	}
	
	// move camera
	a3demo_input_controlProjector(demoState, projector,
		dt, projector->ctrlMoveSpeed, projector->ctrlRotateSpeed, projector->ctrlZoomSpeed);

	//Select Clip Controller to Edit
	//Cycle through the three clip controllers by index
	//On 'k' or 'l' press, increment or decrement clip controller index value by one
	//When we reach the first or last index, jump back to end or start?

	//Play/Pause controller playback
	//On 'SPACEBAR' press get playback_direction = activeClipController.playback_direction
	//If (playback_direction == 1 || -1) store this value then set it to 0
	//else (playback_direction == 0) set this to stored value

	//Set to first/last frame in current clip
	//On 'u' or 'U' press get current_keyframe = activeClipController.clip_pool->clip[activeClipController.clip].keyframe_pool->keyframe[activeClipController.keyframe]
	//if('u') current_keyframe = activeClipController.clip_pool->clip[activeClipController.clip].first_keyframe
	//else if('U') current_keyframe = activeClipController.clip_pool->clip[activeClipController.clip].last_keyframe

	//Change clip to control
	//Get name of clip we want to control
	//Use get clip index function using clip name
	//Use set clip to play function using clip index

	//Flip Playback Direction
	//On 'y' press get playback_direction = activeClipController.playback_direction
	//if(playback_direction == 0) do nothing
	//else if(playback_direction == 1) playback_direction = -1
	//else if(playback_direction == -1) playback_direction = 1

	//Slow-motion (multiply the time step by a factor of less than one)
	//Multiply playback_direction by 0.5?
}


//-----------------------------------------------------------------------------
