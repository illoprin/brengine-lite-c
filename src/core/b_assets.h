#pragma once

#include <core/b_mesh.h>
#include <texture/b_texture_2d.h>
#include <model/b_model.h>
#include <core/b_files.h>

extern mesh_t* b_quad_2f;
extern mesh_t* b_quad_3f;
extern mesh_t* b_cube;

extern GLuint b_tex_null;

extern model_triangle b_quad_tris[2];
extern model_triangle b_cube_tris[12];

void assets_init();

void assets_release();