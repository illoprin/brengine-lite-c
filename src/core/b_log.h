#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <util/defs.h>

// Colorful output
#define RESET       "\033[0m"
#define BLACK       "\033[30m"             /* Black */
#define RED         "\033[31m"             /* Red */
#define GREEN       "\033[32m"             /* Green */
#define YELLOW      "\033[33m"             /* Yellow */
#define BLUE        "\033[34m"             /* Blue */
#define MAGENTA     "\033[35m"             /* Magenta */
#define CYAN        "\033[36m"             /* Cyan */
#define WHITE       "\033[37m"             /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

enum LogType
{
	LOG_INFO = 0,
	LOG_ERROR,
	LOG_WARNING
};

// Universal function for log message
void u_log_message(int type, const char* file, unsigned line, const char* format, ...);

#define LOG_MSG(...) u_log_message(LOG_INFO, __BASE_FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERR(...) u_log_message(LOG_ERROR, __BASE_FILE__, __LINE__, __VA_ARGS__)
#define LOG_WAR(...) u_log_message(LOG_WARNING, __BASE_FILE__, __LINE__, __VA_ARGS__)