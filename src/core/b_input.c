#include <core/b_input.h>

bool is_game_mode = false;

// User callback functions
user_key_callback          b_input_key_callback_func          = NULL;
user_mouse_pos_callback    b_input_mouse_pos_callback_func    = NULL;
user_mouse_btn_callback    b_input_mouse_btn_callback_func    = NULL;
user_mouse_scroll_callback b_input_mouse_scroll_callback_func = NULL;
user_char_callback         b_input_char_callback_func         = NULL;

/* Input functions declarations */
static void window_key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
static void window_resize_callback(GLFWwindow* window, int width, int height);
static void window_mousepos_callback(GLFWwindow* window, double xpos, double ypos);
static void window_mousebtn_callback(GLFWwindow* window, int button, int action, int mods);
static void window_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void window_char_callback(GLFWwindow*  window, unsigned int codepoint);

void init_input()
{
	glfwSetKeyCallback        (b_window, window_key_callback);
	glfwSetWindowSizeCallback (b_window, window_resize_callback);
	glfwSetCursorPosCallback  (b_window, window_mousepos_callback);
	glfwSetMouseButtonCallback(b_window, window_mousebtn_callback);
	glfwSetScrollCallback     (b_window, window_scroll_callback);
	glfwSetCharCallback       (b_window, window_char_callback);
};

void input_switch_game_mode()
{
	is_game_mode = !is_game_mode;
	if (is_game_mode)
		/* Hide and lock cursor */
		glfwSetInputMode(
			b_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		/* Set cursor visible */
		glfwSetInputMode(
			b_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
};

static void window_key_callback(
	GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(win, 1);
		if (key == GLFW_KEY_TAB) input_switch_game_mode();
	}

	if (b_input_key_callback_func != NULL)
		b_input_key_callback_func(key, action, mods);
};

static void window_resize_callback (
	GLFWwindow* window, int width, int height
)
{
	wwidth = width;
	wheight = height;
	waspect = (float)wwidth / (float)wheight;
	glViewport(0, 0, width, height);
	LOG_MSG("Window resized X: %u Y: %u ASPECT: %.2f",
		wwidth, wheight, waspect);
};

static void window_mousepos_callback(
	GLFWwindow* window, double xpos, double ypos)
{
	if (b_input_mouse_pos_callback_func != NULL)
		b_input_mouse_pos_callback_func(xpos, ypos);
};

static void window_mousebtn_callback(
	GLFWwindow* window, int button, int action, int mods)
{
	if (b_input_mouse_btn_callback_func != NULL)
		b_input_mouse_btn_callback_func(button, action, mods);
};

static void window_scroll_callback(
	GLFWwindow* window, double xoffset, double yoffset)
{
	if (b_input_mouse_scroll_callback_func != NULL)
		b_input_mouse_scroll_callback_func(xoffset, yoffset);
};

static void window_char_callback(
	GLFWwindow* window, unsigned int codepoint)
{
	if (b_input_char_callback_func != NULL)
		b_input_char_callback_func(codepoint);
};