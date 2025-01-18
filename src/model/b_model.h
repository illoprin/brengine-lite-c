#pragma once

#include <cglm/cglm.h>
#include <util/deps.h>

typedef struct {
	vec3 position;
	vec2 texcoord;
	vec3 normal;
} model_vertex;

typedef struct {
	model_vertex vertices[3];
} model_triangle;

model_triangle* mt_from_obj(const char* filename, unsigned* vertex_count);

void mt_print(model_triangle* mt, unsigned count);