#include "Server.hpp"
#include "utils.hpp"

#include <iostream>

int main (int argc, char *argv[])
{
    Server server;

    if (argc != 3)
    {
        log_err("Error: Could not initiate server");
        return EXIT_ERROR;
    }

    //Probably we need to set the signals at the beggining of the program
    server.init(argv);

    while (TRUE);

    return (EXIT_SUCCESS);
}