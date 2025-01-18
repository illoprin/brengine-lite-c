#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <util/defs.h>
#include <core/b_log.h>


/*
	Allocates memory for file data
	Release memory after use
*/
char* read_file_lines(char* file_path);

#ifdef BRENGINE_UTILS_IMPL

char* read_file_lines(char* file_path)
{
	FILE* src = fopen(file_path, "r");

	if (!src)
	{
		LOG_ERR("Could not open file %s", file_path);
		return NULL;
	}

	size_t byte_size = 0;

	fseek(src, 0, SEEK_END);
	byte_size = ftell(src);
	fseek(src, 0, SEEK_SET);
	
	char* data = (char*)calloc(byte_size + 1, sizeof(char));
	if (!data)
	{
		LOG_ERR("Could not allocate memory for file data");
		return NULL;
	}

	char line[MAX_BUFFER];

	unsigned lines = 0u;
	while (fgets(line, MAX_BUFFER, src))
	{
		strcat(data, line);
		lines++;
	}
	LOG_MSG("From file with path %s readed %u lines", file_path, lines);

	fclose(src);

	return data;
};

#endif