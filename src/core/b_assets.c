#include "b_assets.h"

mesh_t* b_quad_2f = NULL;
mesh_t* b_quad_3f = NULL;
mesh_t* b_cube = NULL;
GLuint b_tex_null = 0;
GLuint b_tex_alpha = 0;

model_triangle b_cube_tris[12] = {
	/* Front */
	{.vertices = {
		{ {0.5f, 0.5f, -.5f}, {1.f, 1.f}, {0.f, 0.f, -1.f} },
		{ {0.5f, -0.5f, -.5f}, {1.f, 0.f}, {0.f, 0.f, -1.f} },
		{ {-0.5f, -0.5f, -.5f}, {0.f, 0.f}, {0.f, 0.f, -1.f} }
	}},
	{.vertices = {
		{ {-0.5f, -0.5f, -.5f}, {0.f, 0.f}, {0.f, 0.f, -1.f} },
		{ {-0.5f, 0.5f, -.5f}, {0.f, 1.f}, {0.f, 0.f, -1.f}},
		{ {0.5f, 0.5f, -.5f}, {1.f, 1.f}, {0.f, 0.f, -1.f}}
	}},

	/* Back */
	{.vertices = {
		{ {-0.5f, 0.5f, 0.5f}, {1.f, 1.f}, {0.f, 0.f, 1.f} },
		{ {-0.5f, -0.5f, 0.5f}, {1.f, 0.f}, {0.f, 0.f, 1.f} },
		{ {0.5f, -0.5f, 0.5f}, {0.f, 0.f}, {0.f, 0.f, 1.f} }
	}},
	{.vertices = {
		{{0.5f, -0.5f, 0.5f}, {0.f, 0.f}, {0.f, 0.f, 1.f}},
		{{0.5f, 0.5f, 0.5f}, {0.f, 1.f}, {0.f, 0.f, 1.f}},
		{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f}, {0.f, 0.f, 1.f}}
	}},

	/* Left */
	{.vertices = {
		{{0.5f, -0.5f, -.5f}, {1.f, 1.f}, {1.f, 0.f, 0.f}},
		{{0.5f, 0.5f, -.5f}, {1.f, 0.f}, {1.f, 0.f, 0.f}},
		{{0.5f, 0.5f, .5f}, {0.f, 0.f}, {1.f, 0.f, -0.f}}
	}},
	{.vertices = {
		{{0.5f, 0.5f, .5f}, {0.f, 0.f}, {1.f, 0.f, 0.f}},
		{{0.5f, -0.5f, .5f}, {0.f, 1.f}, {1.f, 0.f, 0.f}},
		{{0.5f, -0.5f, -.5f}, {1.f, 1.f}, {1.f, 0.f, 0.f}}
	}},

	/* Right */
	{.vertices = {
		{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f}, {-1.f, 0.f, 0.f}},
		{{-0.5f, -0.5f, 0.5f}, {1.f, 0.f}, {-1.f, 0.f, 0.f}},
		{{-0.5f, 0.5f, 0.5f}, {0.f, 0.f}, {-1.f, 0.f, 0.f}}
	}},
	{.vertices = {
		{{-0.5f, 0.5f, 0.5f}, {0.f, 0.f}, {-1.f, 0.f, 0.f}},
		{{-0.5f, 0.5f, -0.5f}, {0.f, 1.f}, {-1.f, 0.f, 0.f}},
		{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f}, {-1.f, 0.f, 0.f}}
	}},

	/* Top */
	{.vertices = {
		{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f}, {0.f, 1.f, 0.f}},
		{{0.5f, 0.5f, 0.5f}, {1.f, 0.f}, {0.f, 1.f, 0.f}},
		{{0.5f, 0.5f, -0.5f}, {0.f, 0.f}, {0.f, 1.f, 0.f}}
	}},
	{.vertices = {
		{{0.5f, 0.5f, -0.5f}, {0.f, 0.f}, {0.f, 1.f, 0.f}},
		{{-0.5f, 0.5f, -0.5f}, {0.f, 1.f}, {0.f, 1.f, 0.f}},
		{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f}, {0.f, 1.f, 0.f}}
	}},

	/* Bottom */
	{.vertices = {
		{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f}, {0.f, -1.f, 0.f}},
		{{0.5f, -0.5f, -0.5f}, {1.f, 0.f}, {0.f, -1.f, 0.f}},
		{{0.5f, -0.5f, 0.5f}, {0.f, 0.f}, {0.f, -1.f, 0.f}}
	}},
	{.vertices = {
		{{0.5f, -0.5f, 0.5f}, {0.f, 0.f}, {0.f, -1.f, 0.f}},
		{{-0.5f, -0.5f, 0.5f}, {0.f, 1.f}, {0.f, -1.f, 0.f}},
		{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f}, {0.f, -1.f, 0.f}}
	}}
};

model_triangle b_quad_tris[2] = {
	{.vertices = {
		{{0.5f, 0.5f, 0.f}, {1.f, 1.f}, {0.f, 0.f, -1.f}},
		{{0.5f, -0.5f, 0.f}, {1.f, 0.f}, {0.f, 0.f, -1.f}},
		{{-0.5f, -0.5f, 0.f}, {0.f, 0.f}, {0.f, 0.f, -1.f}}
	}},
	{.vertices = {
		{{-0.5f, -0.5f, 0.f}, {0.f, 0.f}, {0.f, 0.f, -1.f}},
		{{-0.5f, 0.5f, 0.f}, {0.f, 1.f}, {0.f, 0.f, -1.f}},
		{{0.5f, 0.5f, 0.f}, {1.f, 1.f}, {0.f, 0.f, -1.f}}
	}}
};

void assets_init()
{
	static float quad_v[] = {
	    1.f,  -1.f, 1.f, 0.f, // Left bottom
	    -1.f, -1.f, 0.f, 0.f, // Right bottom
	    1.f,  1.f,  1.f, 1.f, // Left top
	    -1.f, -1.f, 0.f, 0.f, // Right bottom
	    -1.f, 1.f,  0.f, 1.f, // Right top
	    1.f,  1.f,  1.f, 1.f, // Left top
	};

	b_quad_2f = create_mesh();
	mesh_add_buffer(b_quad_2f, quad_v, 4 * 6 * sizeof(float));
	mesh_add_attribute(b_quad_2f, 0, 2, sizeof(float) * 4, 0);
	mesh_add_attribute(b_quad_2f, 0, 2, sizeof(float) * 4, sizeof(float) * 2);
	b_quad_2f->vertices_count = 6u;

	b_quad_3f = create_mesh();
	mesh_add_buffer(b_quad_3f, b_quad_tris, sizeof(float) * 24 * 2);
	mesh_add_attribute(b_quad_3f, 0, 3, sizeof(float) * 8, 0);
	mesh_add_attribute(b_quad_3f, 0, 2, sizeof(float) * 8, offsetof(model_vertex, texcoord));
	mesh_add_attribute(b_quad_3f, 0, 3, sizeof(float) * 8, offsetof(model_vertex, normal));
	b_quad_3f->vertices_count = 6u;

	b_cube = create_mesh();
	mesh_add_buffer(b_cube, b_cube_tris, sizeof(float) * 24 * 12);
	mesh_add_attribute(b_cube, 0, 3, sizeof(float) * 8, 0);
	mesh_add_attribute(b_cube, 0, 2, sizeof(float) * 8, offsetof(model_vertex, texcoord));
	mesh_add_attribute(b_cube, 0, 3, sizeof(float) * 8, offsetof(model_vertex, normal));
	b_cube->vertices_count = 12 * 3;

	int iwidth, iheight, icomps;
	uch* image = stbi_load(DIR_TEXTURES "/null.bmp", &iwidth, &iheight, &icomps, 0); 
	b_tex_null = tex2d_create(image, iwidth, iheight, GL_NEAREST, GL_REPEAT);
	stbi_image_free(image);
};

void assets_release()
{
	mesh_release(b_quad_2f);
	mesh_release(b_quad_3f);
	mesh_release(b_cube);
	tex2d_release(b_tex_null);
};