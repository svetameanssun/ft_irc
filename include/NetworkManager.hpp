#pragma once

#include <vector>
#include <string>
#include <poll.h>

class Server; 

class NetworkManager
{
private:
    int _listenFd;
    int _port;
    std::vector<struct pollfd> _pollFds;

    void setupSocket();

public:
    NetworkManager(int port);
    ~NetworkManager();

    void init();
    void run(Server &server);

    int acceptClient();
    void closeFd(int fd);

    std::vector<struct pollfd> &getPollFds();
};
