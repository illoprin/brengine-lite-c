#pragma once

#include <model/b_model.h>
#include <player/b_camera.h>
#include <core/b_program.h>
#include <texture/b_texture_2d.h>
#include <lsh/lp_list.h>

void entity_renderer_init();
void entity_render(entity_t*, camera_t*);
void entity_render_list(llist* entity_list, camera_t*);
void entity_renderer_release();