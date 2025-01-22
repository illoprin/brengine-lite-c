#pragma once

#include <GL/glew.h>
#include <cglm/cglm.h>
#include <core/b_assets.h>
#include <core/b_program.h>
#include <core/b_window.h>
#include <core/b_context.h>

void gui_renderer_init();

void gui_renderer_update();
void gui_render_quad(vec2   position,
                     vec2   scale,
                     vec4   color,
                     float  rotation,
                     GLuint texture);
void gui_render_line(vec2 p1, vec2 p2, int line_width, vec4 color);
void gui_render_text(const char* text);
void gui_renderer_release();