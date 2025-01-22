#include "b_master_renderer.h"

void renderer_init()
{
	// TODO: Create scene and gui framebuffers	
};

void renderer_start()
{
	ctx_clear();
};

void renderer_flush()
{
	glfwSwapBuffers(b_window);
};
