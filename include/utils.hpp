#pragma once

#include <iostream>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

#define TRUE 1
#define FALSE 0

void log_err(const std::string &message)
{
    std::cerr << message << std::endl;
}

void log_msg(const std::string &message)
{
    std::cout << message << std::endl;
}
