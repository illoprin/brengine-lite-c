#include "b_context.h"

int ctx_init()
{
	if (glewInit() != GLEW_OK)
	{
		LOG_ERR("Could not create OpenGL context");
		return 0;
	};

	glewExperimental = 1;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	LOG_MSG("OpenGL context created with vidmode X: %u Y: %u", wwidth, wheight);
	LOG_MSG("GL Vendor - %s", glGetString(GL_VERSION));
	LOG_MSG("Hardware - %s", glGetString(GL_RENDERER));

	return 1;
};

void ctx_bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0u);
};

void ctx_enable_depth_test()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
};

void ctx_disable_depth_test()
{
	glDisable(GL_DEPTH_TEST);
};

void ctx_enable_face_culling()
{
	// Enable backface culling
	glEnable(GL_CULL_FACE);
	// Set backface culling model - vertices order is counter clockwise
	glCullFace(GL_BACK);
	// Face culling - front face is in clockwise order
	glFrontFace(GL_CCW);
};

void ctx_disable_face_culling()
{
	glDisable(GL_CULL_FACE);
};

void ctx_clear()
{
	ctx_bind();
	glClearColor(0.266f, 0.266f, 0.266f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

GLenum ctx_check_error(const char* file, int line)
{
	GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        switch (errorCode)
        {
            case GL_INVALID_ENUM:
				LOG_ERR("INVALID_ENUM at %s:%d",      file, line);             break;
            case GL_INVALID_VALUE:
				LOG_ERR("INVALID_VALUE at %s:%d",     file, line);             break;
            case GL_INVALID_OPERATION:
				LOG_ERR("INVALID_OPERATION at %s:%d", file, line);             break;
            case GL_STACK_OVERFLOW:
				LOG_ERR("STACK_OVERFLOW at %s:%d",    file, line);             break;
            case GL_STACK_UNDERFLOW:
				LOG_ERR("STACK_UNDERFLOW at %s:%d",   file, line);             break;
            case GL_OUT_OF_MEMORY:
				LOG_ERR("OUT_OF_MEMORY at %s:%d",     file, line);             break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
				LOG_ERR("INVALID_FRAMEBUFFER_OPERATION at %s:%d", file, line); break;
        }
		
    }
    return errorCode;
};

void ctx_release()
{
	LOG_MSG("Context released");
};