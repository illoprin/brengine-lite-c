#include "b_gui_renderer.h"

/* Shader program for 2d shape rendering */
static static_shader* p_gui_shape = NULL;

/* Shader program for 2d text rendering */
static static_shader* p_gui_text = NULL;

/* Orthographic projection matrix */
static mat4 m_ortho;

void gui_renderer_init()
{
	p_gui_shape =
	    create_shader_from_source("gui_shape.vert", "gui_shape.frag");
}

void gui_renderer_update()
{
	glm_ortho(0.f, waspect, 1.f, 0.f, -1.f, 1.f, m_ortho);
}

void gui_render_quad(vec2   position,
                     vec2   scale,
                     vec4   color,
                     float  rotation,
                     GLuint texture)
{
	use_program(p_gui_shape);

	// -- Position
	mat4 model = GLM_MAT4_IDENTITY_INIT;
	vec2 shape_pos = {
		(position[0] + scale[0]) * waspect,
		position[1] + scale[1],
	};
	glm_translate(model, (vec3){shape_pos[0], shape_pos[1], 0.f});
	glm_scale(model, scale);
	glm_rotate(model, glm_rad(rotation), (vec3){0, 0, 1.f});
	
	program_setmat4(p_gui_shape->id, "u_model", &model[0][0]);
	program_setmat4(p_gui_shape->id, "u_projection", &m_ortho[0][0]);

	// -- Color
	if (texture != 0)
	{
		program_set1i(p_gui_shape->id, "u_use_texture", 1);
		tex2d_bind_to_slot(0, texture);
	}
	else
		program_set1i(p_gui_shape->id, "u_use_texture", 0);

	program_set4f(p_gui_shape->id, "u_color", &color[0]);

	ctx_disable_depth_test();
	ctx_disable_face_culling();

	mesh_draw(b_quad_2f, GL_TRIANGLES);
};

/*
	Renders line on screen from p1 to p2
	Line width in pixels
*/
void gui_render_line(vec2 p1, vec2 p2, int lw, vec4 color)
{
	use_program(p_gui_shape);

	// -- Position
	mat4 model = GLM_MAT4_IDENTITY_INIT;

	// Get relative to screen width points
	p1[0] *= waspect;
	p2[0] *= waspect;

	// Line renders as rotated quad
	
	float lx    = p2[0] - p1[0];            // Line relative x
	float ly    = p2[1] - p1[1];            // Line relative y
	float mag   = sqrtf(lx * lx + ly * ly); // Line length

	float angle = atan2f(ly, lx);           // Angle that quad to be rotated
	float qx    = (p1[0] + p2[0]) / 2;      // X coord of quad
	float qy    = (p1[1] + p2[1]) / 2;      // Y coord of quad

	glm_translate(model, (vec3){qx, qy, 0.f});
	glm_rotate   (model, angle, (vec3){0, 0, 1.f});
	glm_scale    (model, (vec3){mag, (float)lw / (float)wheight, 1.f});

	program_setmat4(p_gui_shape->id, "u_model", &model[0][0]);
	program_setmat4(p_gui_shape->id, "u_projection", &m_ortho[0][0]);

	program_set1i(p_gui_shape->id, "u_use_texture", 0);
	program_set4f(p_gui_shape->id, "u_color", color);

	mesh_draw(b_quad_2f, GL_TRIANGLES);
};

void gui_render_text(const char* text)
{
	
};

void gui_renderer_release()
{
	program_release(p_gui_shape);
};
