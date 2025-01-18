#pragma once

#include <player/b_camera.h>
#include <core/b_window.h>

#define PLAYER_SPEED 3.f
#define PLAYER_SPEED_MODIFER 1.78f // Sprint ratio

enum PlayerActions {
	PL_M_FORWARD = 0,
	PL_M_BACKWARD,
	PL_M_LEFT,
	PL_M_RIGHT,
	PL_A_MODIFY,
	PL_A_JUMP,
	PL_NUM_ACTIONS
};

typedef struct {
	int states[PL_NUM_ACTIONS];
	camera_t* camera;
} editor_controller;

// ec - editor controller
editor_controller* create_editor_controller(vec3 position, vec2 rotation);
void editor_controller_update(editor_controller*);
void editor_controller_release(editor_controller*);