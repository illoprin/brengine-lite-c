#include "brengine.h"

bool show_debug_gui = false;

void key_callback(int key, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_F1) show_debug_gui = !show_debug_gui;
	}
}

int main(void)
{
	srand(time(NULL));

	init_filesystem();
	
	if (!init_window())
		return 1;
	
	init_input();
	b_input_key_callback_func = key_callback;

	if (!ctx_init())
		return 1;

	assets_init();

	GLuint t_brick =
		tex2d_from_bmp("brick_1.bmp", GL_NEAREST, GL_REPEAT);

	GLuint t_handgun =
		tex2d_from_bmp("handgun.bmp", GL_NEAREST, GL_CLAMP_TO_EDGE);

	size_t vertex_count = 0;

	model_triangle* tris_handgun = mt_from_obj("handgun.obj", &vertex_count);

	mesh_t* m_handgun = mesh_from_mt(tris_handgun, vertex_count);
	free(tris_handgun);

	entity_t e_handgun = entity_init(m_handgun, t_handgun);
	entity_t e_cube = entity_init(b_cube, t_brick);

	editor_controller* player = create_editor_controller(
		(vec3){0, 0, -2}, (vec2){0, 90}
	);

	e_cube.poistion[1] = -2.f;
	e_cube.scale[0] = 10;
	e_cube.scale[1] = .3f;
	e_cube.scale[2] = 10;

	gui_renderer_init();
	entity_renderer_init();
	while (!is_window_closed())
	{
		open_game_loop();

		// Update
		editor_controller_update(player);

		// Render
		renderer_start();
		
		entity_render(&e_handgun, player->camera);
		entity_render(&e_cube, player->camera);
		
		gui_renderer_update();

		if (show_debug_gui)
		{
			for (unsigned i = 0; i < 10; i++)
				gui_render_quad((vec2){(float)i / 10, (float)i / 10},
								(vec2){.1f, .1f},
								(vec4){1.f, 0.f, 0.f, 1.f / i},
								b_time * 50.f + i*20,
								b_tex_null);

			gui_render_line((vec2){0, .8}, (vec2){1, .8}, 3, (vec4){0.1, 0.2, 0.8, 1.0});
		}

		renderer_flush();

		close_game_loop();
	};

	tex2d_release(t_handgun);
	mesh_release(m_handgun);
	tex2d_release(t_brick);
	gui_renderer_release();
	entity_renderer_release();
	assets_release();
	ctx_release();
	release_window();

	return 0;
}