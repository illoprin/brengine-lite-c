#pragma once

#include <cglm/cglm.h>
#include <util/deps.h>
#include <core/b_log.h>
#include <core/b_mesh.h>
#include <core/b_files.h>
#include <lsh/lp_dynarr.h>
#include <core/b_mesh.h>

typedef struct {
	vec3 position;
	vec2 texcoord;
	vec3 normal;
} model_vertex;

typedef struct {
	model_vertex vertices[3];
} model_triangle;

typedef struct {
	mesh_t* mesh;
	GLuint  texture;
	vec4    color;

	vec3    poistion;
	vec3    rotation;
	vec3    scale;
} entity_t;

model_triangle* mt_from_obj(const char* filename, size_t* vertex_count);

mesh_t* mesh_from_mt(model_triangle* tris, size_t vertex_count);

entity_t entity_init(mesh_t* m, GLuint texture);

void mt_print(model_triangle* mt, size_t count);