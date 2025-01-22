#pragma once

#include <util/deps.h>
#include <core/b_context.h>
#include <core/b_mesh.h>
#include <core/b_window.h>

typedef enum {
	RENDER_TEXTURED = 0,
	RENDER_WIRE,
	RENDER_DEPTH,
	RENDER_NORMAL,
} RenderMode;

extern RenderMode b_render_mode;

void renderer_init();
void renderer_start();
void renderer_flush();

