#include "utils.hpp"

void log_msg(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    std::cout << std::endl;
}

void log_err(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    std::cerr << std::endl;
}