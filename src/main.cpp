#include "server.hpp"
#include "utils.hpp"

#include <iostream>

int main (int argc, char *argv[])
{
    Server server;

    if (argc != 2)
    {
        log_err("Could not initiate server");
        return EXIT_ERROR;
    }

    server.setPort(atoi(argv[1]));

    std::cout << "Server initiated in port number: " << server.getPort() << std::endl;
    while (TRUE);

    return (EXIT_SUCCESS);
}