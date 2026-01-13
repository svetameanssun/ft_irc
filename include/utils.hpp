#pragma once

#include <iostream>
#include <cstdlib>
#include <cctype>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

#define TRUE 1
#define FALSE 0

#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define ORANGE  "\033[0;38;5;208m"
#define RED     "\033[0;31m"
#define RESET   "\033[0m"

// log helpers
void log_msg(const char *format, ...);
void log_debug(const char *format, ...);
void log_warning(const char *format, ...);
void log_err(const char *format, ...);

// I think this was for Reply codes :D
bool isAllowed(int ret);

// checking params at the beggining
int checkParams(int argc, char **argv);
