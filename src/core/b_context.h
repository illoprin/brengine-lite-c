#pragma once

#include <util/deps.h>

#include <core/b_log.h>
#include <core/b_window.h>

#define ctxCheckError() ctx_check_error(__FILE__, __LINE__)

extern int ctx_init();
extern void ctx_enable_depth_test();
extern void ctx_clear();
extern void ctx_disable_depth_test();
extern void ctx_enable_face_culling();
extern void ctx_disable_face_culling();
GLenum ctx_check_error(const char* file, int line);
extern void ctx_release();
