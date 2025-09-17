#pragma once

#include <iostream>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

#define TRUE 1
#define FALSE 0

void log_msg(const char* format, ...);

void log_err(const char* format, ...);