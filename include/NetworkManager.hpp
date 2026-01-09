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
    void pollOnce();

    int acceptClient();
    //ssize_t receiveFrom(int fd, std::string &out);
    void sendTo(int fd, const std::string &msg);
    void closeFd(int fd);

    std::vector<struct pollfd> &getPollFds();
};
