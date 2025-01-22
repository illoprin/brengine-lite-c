#include "b_window.h"

GLFWwindow* b_window = NULL;

uint16_t wwidth = WIN_WIDTH;
uint16_t wheight = WIN_HEIGHT;
float waspect = 1.f;

double mouse_last_x = 0.0, mouse_last_y = 0.0;
double b_mouse_delta_x = 0.0, b_mouse_delta_y = 0.0;

int init_window()
{
	if (!glfwInit())
	{
		LOG_ERR("Could not init window manager");
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	b_window = glfwCreateWindow(wwidth, wheight, "Brengine Level Editor", NULL, NULL);

	int w, h; glfwGetFramebufferSize(b_window, &w, &h);
	wwidth = (uint16_t)w; wheight = (uint16_t)h;
	waspect = (float)wwidth / (float)wheight;

	if (!b_window)
	{
		LOG_ERR("Could not create window");
		return 0;
	};

	glfwFocusWindow(b_window);
	
	glfwMakeContextCurrent(b_window);

	LOG_MSG("Window created!");

	return 1;
};

int is_window_closed()
{
	return glfwWindowShouldClose(b_window);
}

void open_game_loop()
{
	start_clock();
	b_mouse_delta_x = b_mouse_delta_y = 0;
	double mouse_x, mouse_y;
	glfwGetCursorPos(b_window, &mouse_x, &mouse_y);
	b_mouse_delta_x = mouse_x - mouse_last_x;
	b_mouse_delta_y = mouse_y - mouse_last_y;
	mouse_last_x = mouse_x; mouse_last_y = mouse_y;

	glfwPollEvents();
};

void close_game_loop()
{
	end_clock();
};

void release_window()
{
	glfwDestroyWindow(b_window);
	glfwTerminate();
	LOG_MSG("Window released");
};