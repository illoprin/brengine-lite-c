#pragma once

#include <stdlib.h>
#include <GL/glew.h>
#include <core/b_context.h>

#include <util/defs.h>
#include <core/b_log.h>

extern unsigned b_draw_calls;
extern unsigned long b_vertices;

typedef struct {
	GLuint vao_id;
	GLuint* buffers;
	uch __attributes;
	size_t __buffers_length;
	unsigned vertices_count;
} mesh_t;

mesh_t* create_mesh();

GLuint mesh_add_buffer(mesh_t* mesh, void* data, size_t size_bytes);
GLuint mesh_add_dynamic_buffer(mesh_t*, size_t reserve);
void mesh_update_buffer(mesh_t*, uch index, size_t offset, void* data, size_t size_bytes);
void mesh_add_attribute(mesh_t*, uch buffer_index, uch comps, size_t stride, size_t offset);
void mesh_add_integer_attribute(mesh_t*, uch buffer_index, uch comps, size_t stride, size_t offset);
void mesh_draw(mesh_t*, GLint mode);
void mesh_release(mesh_t*);