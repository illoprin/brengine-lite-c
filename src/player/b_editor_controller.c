#include "b_editor_controller.h"


editor_controller* create_editor_controller(vec3 position, vec2 rotation)
{
	editor_controller* ec = (editor_controller*)calloc(1, sizeof(editor_controller));
	ec->camera = (camera_t*)camera_create(position, rotation);
	
	return ec;
}

void editor_controller_update(editor_controller* ec)
{
	if (is_game_mode)
	{
		ec_handle_keyboard(ec);
		ec_handle_mouse_events(ec);
		ec_process_movement(ec);	
	}
	camera_update_vectors(ec->camera);
};

void ec_handle_keyboard(editor_controller* ec)
{
	ec->states[PL_M_FORWARD] = glfwGetKey(b_window, GLFW_KEY_W);
	ec->states[PL_M_BACKWARD] = glfwGetKey(b_window, GLFW_KEY_S);
	ec->states[PL_M_LEFT] = glfwGetKey(b_window, GLFW_KEY_A);
	ec->states[PL_M_RIGHT] = glfwGetKey(b_window, GLFW_KEY_D);
	ec->states[PL_A_MODIFY] = glfwGetKey(b_window, GLFW_KEY_LEFT_SHIFT);
};

void ec_handle_mouse_events(editor_controller* ec)
{
	float factor = 0.05f;
	camera_rotate(ec->camera, -(float)b_mouse_delta_y * factor, (float)b_mouse_delta_x * factor);
};

void ec_process_movement(editor_controller* ec)
{
	int* states = ec->states;
	camera_t* cam = ec->camera;

	vec3 f_vel = {cam->forward[0] * PLAYER_SPEED * b_delta_time,
				  cam->forward[1] * PLAYER_SPEED * b_delta_time,
				  cam->forward[2] * PLAYER_SPEED * b_delta_time};

	vec3 r_vel = {cam->right[0] * PLAYER_SPEED * b_delta_time,
				  cam->right[1] * PLAYER_SPEED * b_delta_time,
				  cam->right[2] * PLAYER_SPEED * b_delta_time};


	if (states[PL_A_MODIFY] == GLFW_PRESS) 
	{
		glm_vec3_scale(r_vel, PLAYER_SPEED_MODIFER, r_vel);
		glm_vec3_scale(f_vel, PLAYER_SPEED_MODIFER, f_vel);
	};

	if (states[PL_M_FORWARD] == GLFW_PRESS)
		glm_vec3_add(cam->position, f_vel, cam->position);
	if (states[PL_M_BACKWARD] == GLFW_PRESS)
		glm_vec3_sub(cam->position, f_vel, cam->position);
	if (states[PL_M_LEFT] == GLFW_PRESS)
		glm_vec3_add(cam->position, r_vel, cam->position);
	if (states[PL_M_RIGHT] == GLFW_PRESS)
		glm_vec3_sub(cam->position, r_vel, cam->position);
};

void editor_controller_release(editor_controller* ec)
{
	if (ec)
	{
		camera_release(ec->camera);
		free(ec);
	}
}
