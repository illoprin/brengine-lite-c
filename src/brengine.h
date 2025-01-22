#pragma once

#define BRENGINE_UTILS_IMPL
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#define LP_DYNARR_IMPLEMENTATION
#define LP_LISR_IMPLEMENTATION
#define LP_MATH_IMPLEMENTATION
#define DYNARR_DEBUG

#include <util/deps.h>
#include <util/b_utils.h>

#include <lsh/lp_common.h>
#include <lsh/lp_dynarr.h>
#include <lsh/lp_list.h>

// Core
#include <core/b_files.h>
#include <core/b_assets.h>
#include <util/b_math.h>
#include <core/b_window.h>
#include <core/b_input.h>
#include <core/b_context.h>
#include <core/b_mesh.h>
#include <core/b_program.h>

// Render
#include <render/b_master_renderer.h>
#include <render/b_entity_renderer.h>
#include <render/b_gui_renderer.h>

// Texture
#include <texture/b_texture_2d.h>

// Gameplay
#include <player/b_editor_controller.h>
// Game entites
#include <model/b_model.h>
