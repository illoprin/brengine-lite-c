#pragma once

#include <util/deps.h>
#include <core/b_window.h>

typedef void (*user_key_callback)(int key, int action, int mods);
typedef void (*user_mouse_pos_callback)(double x, double y);
typedef void (*user_mouse_btn_callback)(int button, int action, int mods);
typedef void (*user_mouse_scroll_callback)(double xoffset, double yoffset);
typedef void (*user_char_callback)(unsigned int codepoint);

extern user_key_callback b_input_key_callback_func;
extern user_mouse_pos_callback b_input_mouse_pos_callback_func;
extern user_mouse_btn_callback b_input_mouse_btn_callback_func;
extern user_mouse_scroll_callback b_input_mouse_scroll_callback_func;
extern user_char_callback b_input_char_callback_func;

extern bool is_game_mode;

void init_input();
void input_switch_game_mode();