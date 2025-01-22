#pragma once

#include <stdlib.h>
#include <stdarg.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <util/defs.h>
#include <core/b_files.h>
#include <util/b_utils.h>
#include <cglm/cglm.h>
#include <core/b_log.h>

typedef struct {
	GLuint id;
	GLuint shaders[2];
} static_shader;

static_shader* create_shader();
static_shader* create_shader_from_source(const char* vs, const char* fs);
void           use_program(static_shader*);
void           program_release(static_shader*);

void program_set1f(GLuint id, const char* uniform_name, float);
void program_set1i(GLuint id, const char* uniform_name, int);
void program_set2f(GLuint id, const char* uniform_name, float*);
void program_set3f(GLuint id, const char* uniform_name, float*);
void program_set4f(GLuint id, const char* uniform_name, float*);
void program_setmat4(GLuint id, const char* uniform_name, float*);
void program_setmat3(GLuint id, const char* uniform_name, float*);
void program_setmat2(GLuint id, const char* uniform_name, float*);

extern GLuint compile_shader(const char* source, GLenum type);
extern void   link_program(GLuint prog, uch count, ...);