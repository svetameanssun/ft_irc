#include "Server.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    if (checkParams(argc, argv) < 0)
        return 1;
    
    Server srv(atoi(argv[1]), argv[2]);

    srv.init();
}
