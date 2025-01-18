#pragma once

#include <stdio.h>
#include <util/defs.h>
#include <core/b_log.h>
#include <stdlib.h>

#ifndef _WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#define DIR_ASSETS "assets"
#define DIR_TEXTURES DIR_ASSETS "/textures"
#define DIR_SHADERS DIR_ASSETS "/shaders"
#define DIR_TEMP "tmp"

void dir_create(const char*);
int dir_check(const char*);

void init_filesystem();