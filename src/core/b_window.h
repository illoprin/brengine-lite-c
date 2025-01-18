#pragma once

#include "util/deps.h"

#include <core/b_clock.h>
#include <core/b_log.h>

/* Externs */
extern GLFWwindow* b_window;
extern uint16_t wwidth;
extern uint16_t wheight;
extern float waspect;
extern double b_mouse_delta_x;
extern double b_mouse_delta_y;
extern bool is_game_mode;

extern int init_window();
extern int is_window_closed();
extern void switch_game_mode();
extern void open_game_loop();
extern void close_game_loop();
extern void release_window();