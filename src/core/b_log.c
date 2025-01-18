#include "b_log.h"

void u_log_message(
	int logType, const char* file, unsigned line, const char* format, ...)
{
	va_list arglist;
	printf("%s - ", file);
	switch (logType)
	{
		case LOG_INFO:
			printf(GREEN "INFO" RESET);
		break;

		case LOG_ERROR:
			printf(RED "ERROR" RESET);
		break;

		case LOG_WARNING:
			printf(YELLOW "WARNING" RESET);
		break;
	};

	printf(" - ");

	va_start(arglist, format);

	vprintf(format, arglist);

	va_end(arglist);

	printf("\n");
}