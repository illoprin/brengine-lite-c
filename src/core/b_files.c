#include "b_files.h"

void dir_create(const char* p)
{
	#ifdef _WIN32

	#else
		mkdir(p, 0700);
	#endif
};

int dir_check(const char* p)
{
	#ifdef _WIN32
		
	#else
		struct stat st = {0};
		if (stat(p, &st) == -1)
			return 0;
		return 1;
	#endif
};

void init_filesystem()
{
	if (!dir_check(DIR_TEMP))
		dir_create(DIR_TEMP);
	
	if (!dir_check(DIR_ASSETS))
	{
		LOG_ERR("Assets folder undefined. Cannot init game without resources");
		exit(EXIT_FAILURE);
	}
};