#include "b_program.h"

static_shader* create_shader()
{
	static_shader* sh = (static_shader*)malloc(sizeof(static_shader));

	sh->program_id = glCreateProgram();
	LOG_MSG("Program with id = %u created", sh->program_id);

	return sh;
};

static_shader* create_shader_from_source (const char* vs, const char* fs)
{
	static_shader* sh = create_shader();

	// Get full path to vs source file path
	char vs_filepath[MAX_FILEPATH] = DIR_SHADERS;
	sprintf(vs_filepath, "assets/shaders/%s", vs);
	// Get full path to fs source file path
	char fs_filepath[MAX_FILEPATH] = DIR_SHADERS;
	sprintf(fs_filepath, "assets/shaders/%s", fs);

	// Read lines from vs source
	char* vs_source = read_file_lines(vs_filepath);
	// Read lines from fs source
	char* fs_source = read_file_lines(fs_filepath);

	// Compile vertex shader
	sh->shaders[0] = compile_shader(vs_source, GL_VERTEX_SHADER);
	// Compile fragment shader
	sh->shaders[1] = compile_shader(fs_source, GL_FRAGMENT_SHADER);

	link_program(sh->program_id, 2, sh->shaders[0], sh->shaders[1]);

	free(vs_source); free(fs_source);

	return sh;
};

void program_release(static_shader* s)
{
	if (s)
	{
		GLuint progid = s->program_id;
		glDetachShader(progid, s->shaders[0]);
		glDetachShader(progid, s->shaders[1]);

		glDeleteShader(s->shaders[0]);
		LOG_MSG("Shader id = %u released", s->shaders[0]);

		glDeleteShader(s->shaders[1]);
		LOG_MSG("Shader id = %u released", s->shaders[1]);

		glDeleteProgram(progid);
		LOG_MSG("Program id = %u released", progid);

		free(s);
	}
}

GLuint compile_shader(const char* source, GLenum type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		char error_log[512];
		glGetShaderInfoLog(shader, 512, NULL, error_log);
		LOG_ERR("Shader compilation error:\n%s", error_log);
	}
	else
	{
		LOG_MSG("Shader id = %u compiled!", shader);
	};
	return shader;
};

void use_program(static_shader* sh)
{
	glUseProgram(sh->program_id);
}; 

void link_program(GLuint prog, uch count, ...)
{
	va_list args;

	va_start(args, count);

	for (uch i = 0; i < count; ++i)
		glAttachShader(prog, va_arg(args, GLuint));

	va_end(args);

	glLinkProgram(prog);

	int status;
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (!status)
	{
		char error_log[MAX_BUFFER];
		glGetProgramInfoLog(prog, MAX_BUFFER, NULL, error_log);
		LOG_ERR("Program link error:\n%s", error_log);
	}
	else
	{
		LOG_MSG("Program id = %u linked!", prog);
	}
};

static inline GLint get_uniform_id(GLuint prog, const char* name)
{
	GLint id = glGetUniformLocation(prog, name);
	if (id < 0)
		LOG_WAR("Program id = %u undefined uniform with name %s", 
			prog, name);
	
	return id;
}

/* Setters for uniforms */
void program_set1f(GLuint id, const char* uniform_name, float v)
{
	GLuint loc = get_uniform_id(id, uniform_name);
	if (loc >= 0) glUniform1f(loc, v);
};
void program_set1i(GLuint id, const char* uniform_name, int v)
{
	GLuint loc = get_uniform_id(id, uniform_name);
	if (loc >= 0) glUniform1i(loc, v);
};
void program_set2f(GLuint id, const char* uniform_name, vec2 v)
{
	GLuint loc = get_uniform_id(id, uniform_name);
	if (loc >= 0) glUniform2f(loc, v[0], v[1]);
};
void program_set3f(GLuint id, const char* uniform_name, vec3 v)
{
	GLuint loc = get_uniform_id(id, uniform_name);
	if (loc >= 0) glUniform3f(loc, v[0], v[1], v[2]);
};
void program_set4f(GLuint id, const char* uniform_name, vec4 v)
{
	GLuint loc = get_uniform_id(id, uniform_name);
	if (loc >= 0) glUniform4f(loc, v[0], v[1], v[2], v[3]);
};

void program_setmat4(GLuint id, const char* uniform_name, mat4 v)
{
	GLuint loc = get_uniform_id(id, uniform_name);
	if (loc >= 0) glUniformMatrix4fv(loc, 1, GL_FALSE, &v[0][0]);
};
void program_setmat3(GLuint id, const char* uniform_name, mat3 v)
{
	GLuint loc = get_uniform_id(id, uniform_name);
	if (loc >= 0) glUniformMatrix3fv(loc, 1, GL_FALSE, &v[0][0]);
};
void program_setmat2(GLuint id, const char* uniform_name, mat2 v)
{
	GLuint loc = get_uniform_id(id, uniform_name);
	if (loc >= 0) glUniformMatrix2fv(loc, 1, GL_FALSE, &v[0][0]);
};