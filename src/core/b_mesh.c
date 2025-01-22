#include "b_mesh.h"

unsigned b_draw_calls = 0u;
unsigned long b_vertices = 0LU;

mesh_t* create_mesh()
{
	mesh_t* m = (mesh_t*)malloc(sizeof(mesh_t));

	m->buffers = NULL;
	m->__buffers_length = 0;
	m->__attributes = 0;
	m->vertices_count = 0;

	glGenVertexArrays(1, &m->vao_id);
	LOG_MSG("Created mesh with id = %u", m->vao_id);

	return m;
};

GLuint mesh_add_buffer(mesh_t* mesh, void* d, size_t b)
{
	GLuint vbo;

	glBindVertexArray(mesh->vao_id);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, b, d, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	ctxCheckError();

	if (mesh->__buffers_length < 1)
		mesh->buffers = (GLuint*)malloc(sizeof(GLuint));
	else
		mesh->buffers = (GLuint*)realloc(mesh->buffers, sizeof(GLuint) * (mesh->__buffers_length + 1));
	
	mesh->buffers[mesh->__buffers_length] = vbo;

	mesh->__buffers_length++;
	
	LOG_MSG("Mesh id = %u added buffer object with index %u", mesh->vao_id, vbo);


	return vbo;
};

GLuint mesh_add_dynamic_buffer(mesh_t* mesh, size_t reserve)
{
	GLuint vbo;

	glBindVertexArray(mesh->vao_id);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, reserve, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	ctxCheckError();

	if (mesh->__buffers_length == 0)
		mesh->buffers = (GLuint*)malloc(sizeof(GLuint));
	else
		mesh->buffers = (GLuint*)realloc(mesh->buffers, sizeof(GLuint) * (mesh->__buffers_length + 1));
	
	mesh->buffers[mesh->__buffers_length] = vbo;

	mesh->__buffers_length++;

	LOG_MSG("Mesh id = %u added buffer object with index %u", mesh->vao_id, vbo);

	return vbo;
};

void mesh_update_buffer(
	mesh_t* mesh, uch index, size_t offset, void* data, size_t size_bytes)
{
	glBindVertexArray(mesh->vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffers[index]);

	glBufferSubData(GL_ARRAY_BUFFER, offset, size_bytes, data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
};

void mesh_add_attribute(
	mesh_t* mesh, uch buffer_index, uch comps, size_t stride, size_t offset)
{
	glBindVertexArray(mesh->vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffers[buffer_index]);
	
	glEnableVertexAttribArray(mesh->__attributes);
	glVertexAttribPointer(mesh->__attributes, comps, GL_FLOAT, GL_FALSE, stride, (void*)offset);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	ctxCheckError();

	mesh->__attributes++;
};

void mesh_add_integer_attribute(
	mesh_t* mesh, uch buffer_index, uch comps, size_t stride, size_t offset)
{
	glBindVertexArray(mesh->vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffers[buffer_index]);
	
	glEnableVertexAttribArray(mesh->__attributes);
	glVertexAttribIPointer(mesh->__attributes, comps, GL_INT, stride, (void*)offset);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	ctxCheckError();

	mesh->__attributes++;
};

static void mesh_enable_attrs(uch attrs)
{
	uch i = 0;
	for ( ; i < attrs; i++)
		glEnableVertexAttribArray(i);
};

static void mesh_disable_attrs(uch attrs)
{
	uch i = 0;
	for ( ; i < attrs; i++)
		glDisableVertexAttribArray(i);
};

void mesh_draw(mesh_t* mesh, GLint mode)
{
	if (mesh->vertices_count > 0)
	{
		mesh_enable_attrs(mesh->__attributes);
		glBindVertexArray(mesh->vao_id);
		glDrawArrays(mode, 0, mesh->vertices_count);
		b_draw_calls++;
		b_vertices += mesh->vertices_count;
		glBindVertexArray(0);
		mesh_disable_attrs(mesh->__attributes);
	}
};

void mesh_draw_count(mesh_t* mesh, GLuint f, GLuint last)
{
	if (mesh->vertices_count > 0)
	{
		mesh_enable_attrs(mesh->__attributes);
		glBindVertexArray(mesh->vao_id);
		last = last <= mesh->vertices_count ? last : mesh->vertices_count;
		glDrawArrays(GL_TRIANGLES, 0, last);
		b_draw_calls++;
		b_vertices += mesh->vertices_count;
		glBindVertexArray(0);
		mesh_disable_attrs(mesh->__attributes);
	}
}

void mesh_release(mesh_t* mesh)
{
	if (mesh)
	{
		if (mesh->buffers)
		{
			glDeleteBuffers(mesh->__buffers_length, mesh->buffers);
			LOG_MSG("Mesh id = %u released buffers count %lu", mesh->vao_id, mesh->__buffers_length);
			free(mesh->buffers);
		}
		glDeleteVertexArrays(1, &mesh->vao_id);

		LOG_MSG("Mesh id = %u released", mesh->vao_id);

		free(mesh);
	}
};