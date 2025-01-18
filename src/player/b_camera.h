#pragma once

#include <core/b_log.h>
#include <util/b_math.h>
#include <util/defs.h>
#include <cglm/cglm.h>
#include <stdlib.h>
#include <math.h>
#include <core/b_window.h>

#define CAM_NEAR (.001f)
#define CAM_FAR (150.f)
#define CAM_FOV (90.f)

#define DIR_UP (vec3){0.f, 1.f, 0.f}
#define DIR_FORWARD (vec3){0.f, 0.f, 1.f}
#define DIR_RIGHT (vec3){-1.f, 0.f, 0.f}

typedef struct {
	vec3 forward;
	vec3 right;
	vec3 up;

	vec3 position;
	float pitch;
	float yaw;

	float fov;
} camera_t;

camera_t* camera_create(vec3 position, vec2 rot);
void camera_update_vectors(camera_t*);
void camera_set_position(camera_t*, vec3);
void camera_set_rotation(camera_t*, float pitch, float yaw);
void camera_move(camera_t*, vec3 dir);
void camera_rotate(camera_t*, float pitch, float yaw);
void camera_release(camera_t*);

void camera_projection(camera_t*, mat4 proj);
void camera_view(camera_t*, mat4 view);