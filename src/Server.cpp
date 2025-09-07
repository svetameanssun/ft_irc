#include "Server.hpp"

// Default constructor
Server::Server()
: _listenFd(-1), _port(0), _password(""), _running(false) {}

// Parametrized constructor
Server::Server(int port, const std::string &password)
: _listenFd(-1), _port(port), _password(password), _running(false) {}

// Destructor
Server::~Server() {
    if (_listenFd != -1)
        ::close(_listenFd);
    // más adelante: liberar Clients y Channels
}

int Server::getPort() const { return _port; }

void Server::setPort(int port) { this->_port = port; }

void Server::setPassword(std::string password) { this->_password = password; }