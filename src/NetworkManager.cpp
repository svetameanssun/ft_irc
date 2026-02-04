#include "NetworkManager.hpp"
#include "Server.hpp"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>

NetworkManager::NetworkManager(int port)
    : _listenFd(-1), _port(port) {}

NetworkManager::~NetworkManager()
{
    if (_listenFd != -1)
        this->closeFd(_listenFd);
}

void NetworkManager::init() { setupSocket(); }

void NetworkManager::run(Server &server)
{
    init();

    while (true)
    {
        if (gSignalStatus == SIGINT){
		    log_msg("SIGINT received, shutting down...");
		    //server.stop();
            break;
	    }
        log_debug("[Network manager] Inside the loop..");
        if (poll(_pollFds.data(), _pollFds.size(), -1) < 0)
        {
            log_err("Poll error, returning...");
            break;
        }

        for (size_t i = 0; i < _pollFds.size(); i++)
        {
            if (!(_pollFds[i].revents & POLLIN))
                continue;

            // Look at these functions
            if (_pollFds[i].fd == _listenFd)
                server.onClientConnected(acceptClient());
            else
                server.onClientData(_pollFds[i].fd);
        }
    }
}

void NetworkManager::setupSocket()
{
    _listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_listenFd < 0)
    {
        log_err("socket failed");
        return; 
    }

    int opt = 1;
    if (setsockopt(_listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        log_err("Socket not initialized correctly");
        return ;
    }

    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(_port);

    if (bind(_listenFd, (sockaddr*)&addr, sizeof(addr)) < 0)
    { 
        log_err("bind failed");
        return; 
    }

    if (listen(_listenFd, SOMAXCONN) < 0)
    {
        log_err("listen failed");
        return; 
    }

    struct pollfd pfd;
    pfd.fd = _listenFd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);
}

int NetworkManager::acceptClient()
{
    sockaddr_in clientAddr;
    socklen_t len = sizeof(clientAddr);

    int fd = accept(_listenFd, (sockaddr*)&clientAddr, &len);
    if (fd < 0)
        return -1;
    
    fcntl(fd, F_SETFL, O_NONBLOCK);

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);

    return fd;
}

void NetworkManager::closeFd(int fd)
{
    close(fd);
    for (size_t i = 0; i < _pollFds.size(); ++i)
    {
        if (_pollFds[i].fd == fd)
        {
            _pollFds.erase(_pollFds.begin() + i);
            break;
        }
    }
}

std::vector<struct pollfd> &NetworkManager::getPollFds() { return _pollFds; }


