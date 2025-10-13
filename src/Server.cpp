#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "CommandHandler.hpp"
#include "utils.hpp"
#include <sstream>

// Default constructor
Server::Server()
: _serverName("irc_server"), _listenFd(-1), _port(0), _password(""),
    _running(false), _cmdHandler(*this), _clientManager(), _channelManager() {}

// Parametrized constructor
Server::Server(int port, const std::string &password)
: _serverName("irc_server"), _listenFd(-1), _port(port), _password(password),
    _running(false), _cmdHandler(*this), _clientManager(), _channelManager() {}

// Destructor
Server::~Server()
{
    if (_listenFd != -1)
        ::close(_listenFd);

    //free all clients & channels
    _clientManager.freeResources();
    _channelManager.freeResources();
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

//setters
void Server::setPort(int port) { _port = port; }
void Server::setPassword(const std::string password) { _password = password; }

//getters
const std::string &Server::getServerName() const { return _serverName; }
int Server::getPort() const { return _port; }
const std::string &Server::getPassword() const { return _password; }


void Server::dispatchCommand(Client *client, const std::string &cmd,
                             const std::vector<std::string> &args)
{
    _cmdHandler.execute(client, cmd, args);
}
