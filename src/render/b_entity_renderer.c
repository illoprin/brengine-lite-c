#include "b_entity_renderer.h"

/* Camera view matrix */
static mat4 m_view;
/* Camera projection matrix */
static mat4 m_perspective;

/* Standart 3d shader */
static static_shader* p_standart = NULL;

void entity_renderer_init()
{
	p_standart = create_shader_from_source("entity.vert", "entity.frag");
}

void entity_render(entity_t* ety, camera_t* cam)
{
	use_program(p_standart);

	camera_projection(cam, m_perspective);
	camera_view(cam, m_view);

	// Form model matrix
	mat4 m_model = GLM_MAT4_IDENTITY_INIT;
	glm_translate(m_model, ety->poistion);
	glm_scale    (m_model, ety->scale);
	glm_rotate   (m_model, ety->rotation[0], (vec3){1, 0, 0});
	glm_rotate   (m_model, ety->rotation[1], (vec3){0, 1, 0});
	glm_rotate   (m_model, ety->rotation[2], (vec3){0, 0, 1});


	// -- Position
	program_setmat4(p_standart->id, "u_projection", m_perspective);
	program_setmat4(p_standart->id, "u_view", m_view);
	program_setmat4(p_standart->id, "u_model", m_model);

	// -- Color
	program_set1i(p_standart->id, "u_use_texture", 0);
	if (ety->texture != 0)
	{
		program_set1i(p_standart->id, "u_use_texture", 1);
		program_set1i(p_standart->id, "u_texture", 0);
		tex2d_bind_to_slot(0, ety->texture);
	}
	program_set4f(p_standart->id, "u_color", ety->color);

	ctx_enable_depth_test();
	ctx_enable_face_culling();

	mesh_draw(ety->mesh, GL_TRIANGLES);
}

void entity_render_list(llist* entity_list, camera_t* cam)
{
	
}

void entity_renderer_release()
{
	
}
