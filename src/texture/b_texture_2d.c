#include "b_texture_2d.h"

GLuint tex2d_create(
	unsigned char* data,
	uint16_t width,
	uint16_t height,
	GLint filter,
	GLint wrapping
)
{
	GLuint texid;

	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (ctxCheckError() == GL_NO_ERROR)
		LOG_MSG("Texture2D id = %u created and inited", texid);

	return texid;
}

GLuint tex2d_from_bmp(const char* file_name, GLint filter, GLint wrapping)
{
	int  twidth, theight, tcomps;
	char file_path[MAX_FILEPATH];

	sprintf(file_path, DIR_TEXTURES "/%s", file_name);

	unsigned char* image =
		stbi_load(file_path, &twidth, &theight, &tcomps, 0);
	GLuint tex = tex2d_create(image, twidth, theight, filter, wrapping);
	free(image);
	return tex;
};

void tex2d_bind_to_slot(GLint slot, GLuint texid)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texid);
};

void tex2d_release(GLuint id)
{
	LOG_MSG("Texture2D id = %u released", id);
	glDeleteTextures(1, &id);
};