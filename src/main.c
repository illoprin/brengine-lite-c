#include "brengine.h"

int main(void)
{
	init_filesystem();
	
	if (!init_window())
		return 1;
	
	if (!ctx_init())
		return 1;

	ctx_enable_depth_test();
	ctx_enable_face_culling();
	assets_init();

	int twidth, theight, tcomps;
	unsigned char* image = stbi_load(DIR_TEXTURES "/brick_1.bmp",
		&twidth, &theight, &tcomps, 0);
	GLuint brick_tex = tex2d_create(image, twidth, theight, GL_NEAREST, GL_REPEAT);
	free(image);

	static_shader* default_shader = create_shader_from_source("standart.vert", "standart.frag");

	editor_controller* player = create_editor_controller((vec3){0, 0, -3.f}, (vec2){0, 90});

	mat4 projection;
	mat4 view;
	mat4 model = GLM_MAT4_IDENTITY_INIT;
	glm_scale(model, (vec3){0.5f, 0.5f, 0.5f});

	while (!is_window_closed())
	{
		open_game_loop();

		// Update

		// Camera projection
		editor_controller_update(player);
		camera_projection(player->camera, projection);
		camera_view(player->camera, view);

		glm_rotate(model, (float)b_delta_time, (vec3){0, 1, 0});

		// Render
		renderer_start();

		use_program(default_shader);
		tex2d_bind_to_slot(0, brick_tex);
		program_setmat4(default_shader->program_id, "u_projection", projection);
		program_setmat4(default_shader->program_id, "u_model", model);
		program_setmat4(default_shader->program_id, "u_view", view);
		program_set3f(default_shader->program_id, "u_cam_pos", player->camera->position);
		mesh_draw(b_cube, GL_TRIANGLES);

		renderer_flush();

		close_game_loop();
	};

	editor_controller_release(player);

	program_release(default_shader);
	tex2d_release(brick_tex);

	assets_release();	
	ctx_release();
	release_window();

	return 0;
}