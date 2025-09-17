#include "Server.hpp"
#include "utils.hpp"

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

void Server::init(char *argv[])
{
    //Check for input - password and port number
    //And remove the password
    setPassword(argv[2]);
    log_msg("Password: %s", getPassword().c_str());

    setPort(atoi(argv[1]));
    log_msg("Server listening in port number: %d", getPort());
}


void Server::setPort(int port) { _port = port; }
void Server::setPassword(const std::string password) { _password = password; }


int Server::getPort() const { return _port; }
const std::string &Server::getPassword() const { return _password; }