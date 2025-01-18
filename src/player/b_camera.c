#include "b_camera.h"

camera_t* camera_create(vec3 p, vec2 r)
{
	camera_t* cam = (camera_t*)calloc(1, sizeof(camera_t));

	cam->pitch = r[0];
	cam->yaw = r[1];
	glm_vec3_copy(p, cam->position);

	cam->fov = CAM_FOV;

	camera_update_vectors(cam);

	return cam;
};

void camera_update_vectors(camera_t* cam)
{
	float ryaw = glm_rad(cam->yaw);
	float rpitch = glm_rad(cam->pitch);
	
	cam->forward[0] = cosf(ryaw) * cosf(rpitch);
	cam->forward[1] = sinf(rpitch);
	cam->forward[2] = sinf(ryaw) * cosf(rpitch);

	glm_vec3_norm(cam->forward);

	glm_vec3_cross(DIR_UP, cam->forward, cam->right);
	glm_vec3_norm(cam->right);

	glm_vec3_cross(cam->forward, cam->right, cam->up);
	glm_vec3_norm(cam->up);
};

void camera_set_position(camera_t* c, vec3 p)
{
	c->position[0] = p[0];
	c->position[1] = p[1];
	c->position[2] = p[2];
};

void camera_set_rotation(camera_t* c, float p, float y)
{
	c->pitch = p;
	c->pitch = glm_clamp(c->pitch, -89.99f, 89.99f);
	
	c->yaw = y;
};

void camera_move(camera_t* c, vec3 d)
{
	glm_vec3_add(c->position, d, c->position);
};

void camera_rotate(camera_t* c, float p, float y)
{
	c->pitch = glm_clamp(c->pitch + p, -89.99f, 89.99f);
	c->yaw += y;
};

void camera_release(camera_t* c)
{
	if (c) free(c);
}

void camera_projection(camera_t* c, mat4 proj)
{
	glm_perspective(glm_rad(c->fov), waspect, CAM_NEAR, CAM_FAR, proj);
};

void camera_view(camera_t* c, mat4 view)
{
	vec3 center;
	glm_vec3_add(c->position, c->forward, center);
	glm_lookat(c->position, center, c->up, view);
};