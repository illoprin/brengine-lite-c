#include "b_clock.h"

double b_time = 0.0, b_delta_time = 0.0, b_fps = 0.0;

double last_time = 0.0;

void start_clock()
{
	b_time = glfwGetTime();
};

void end_clock()
{
	b_delta_time = (b_time - last_time);
	b_fps = 1.0 / b_delta_time;
	last_time = b_time;
};