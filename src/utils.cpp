#include "utils.hpp"

void log_msg(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    std::cout << GREEN << "[LOG]: ";
    vprintf(format, args);
    va_end(args);
    std::cout << std::endl << RESET;
}

void log_debug(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    std::cout << YELLOW << "[DEBUG]: ";
    vprintf(format, args);
    va_end(args);
    std::cout << std::endl << RESET;
}

void log_warning(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    std::cout << ORANGE << "[WARNING]: ";
    vprintf(format, args);
    va_end(args);
    std::cout << std::endl << RESET;  
}


void log_err(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    std::cerr << RED << "[ERROR]: ";
    vprintf(format, args);
    va_end(args);
    std::cerr << std::endl << RESET;
}