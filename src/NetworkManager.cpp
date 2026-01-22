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

NetworkManager::~NetworkManager() {  }

void NetworkManager::init() { setupSocket(); }

void NetworkManager::run(Server &server)
{
    init();

    while (true)
    {
        if (gSignalStatus == SIGINT){
		    log_msg("SIGINT received, shutting down...");
		    server.stop();
            break;
	    }
        log_debug("[Network manager] Inside the loop..");
        poll(_pollFds.data(), _pollFds.size(), -1);

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


//TODO: do not use throw clauses
void NetworkManager::setupSocket()
{
    _listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_listenFd < 0)
        throw std::runtime_error("socket failed");

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
        throw std::runtime_error("bind failed");

    if (listen(_listenFd, SOMAXCONN) < 0)
        throw std::runtime_error("listen failed");

    struct pollfd pfd;
    pfd.fd = _listenFd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);
}

void NetworkManager::pollOnce()
{
    int ret = poll(&_pollFds[0], _pollFds.size(), -1);
    if (ret < 0)
        throw std::runtime_error("poll failed");
}


int NetworkManager::acceptClient()
{
    sockaddr_in clientAddr;
    socklen_t len = sizeof(clientAddr);

    int clientFd = accept(_listenFd, (sockaddr*)&clientAddr, &len);
    if (clientFd < 0)
        return -1;
    
    fcntl(clientFd, F_SETFL, O_NONBLOCK);


    struct pollfd pfd;
    pfd.fd = clientFd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);

    return clientFd;
}

//TODO: Right now the data is handled on the server side
//ssize_t NetworkManager::receiveFrom(int fd, std::string &out)
//{
//    char buffer[512];
//    ssize_t bytes = recv(fd, buffer, sizeof(buffer), 0);
//
//    if (bytes > 0)
//        out.assign(buffer, bytes);
//
//    return bytes;
//}


void NetworkManager::sendTo(int fd, const std::string &msg)
{
    send(fd, msg.c_str(), msg.size(), 0);
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


