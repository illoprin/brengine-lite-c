#pragma once

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <core/b_log.h>
#include <core/b_context.h>
#include <util/defs.h>

/*
	Creates simple 2D texture object
	Format: RGB; Internal Format: R8 G8 B8 (24 bits)
*/
GLuint tex2d_create(
	unsigned char* data,
	uint16_t width,
	uint16_t height,
	GLint filter,
	GLint wrapping
);

void tex2d_bind_to_slot(GLint slot, GLuint texid);

void tex2d_release(GLuint id);