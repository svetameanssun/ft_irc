#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "MessageSender.hpp"
#include "CommandHandler.hpp"
#include "utils.hpp"
#include <sstream>

// Default constructor
Server::Server()
: _serverName("irc_server"), _listenFd(-1), _port(0), _password(""), _running(false) {}

// Parametrized constructor
Server::Server(int port, const std::string &password)
: _serverName("irc_server"), _listenFd(-1), _port(port), _password(password), _running(false) {}

// Destructor
Server::~Server()
{
    if (_listenFd != -1)
        ::close(_listenFd);

    // Free all clients
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
        delete it->second;
    _clients.clear();

    // Free all channels
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
        delete it->second;
    _channels.clear();
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


Channel *Server::findChannel(const std::string& name) const
{
    for (std::map<std::string, Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
    {
        if (it->first == name)
            return it->second;
    }
    return NULL;
}

// Create a new channel and return pointer
Channel *Server::addChannel(const std::string& name) {
    // prevent duplicates
    std::map<std::string, Channel*>::iterator it = _channels.find(name);
    if (it != _channels.end())
        return it->second;

    Channel* chan = new Channel(name);
    _channels[name] = chan;
    return chan;
}

// Remove channel (free memory)
void Server::removeChannel(const std::string& name) {
    std::map<std::string, Channel*>::iterator it = _channels.find(name);
    if (it != _channels.end()) {
        delete it->second;
        _channels.erase(it);
    }
}

//command handling 
//void Server::handleJoin(Client *client, const std::string &chanName, const std::string &key)
//{
//    Channel *chan = findChannel(chanName);  //<<<<<<------ Implement this
//    
//    if(!chan)
//    {
//        chan = new Channel(chanName);
//        _channels[chanName] = chan; 
//        chan->addMember(client, true); // true because it is going to be operator
//    }
//    else 
//    {
//        //Check if +i
//        if (chan->isInviteOnly() && !chan->isInvited(client->getFd()))
//        {
//            MessageSender::sendNumeric(getServerName(), client, 473, chanName + " :Cannot join channel (+i)");
//            return;
//        }
//        //Check if +k
//        if (chan->hasKey() && chan->getKey() != key)
//        {
//            MessageSender::sendNumeric(getServerName(), client, 475, chanName + " :Cannot join channel (+k)");
//            return;
//        }
//        //Check limit
//        if (chan->hasLimit() && chan->getUserLimit() > 0 && chan->getUserCount() > chan->getUserLimit())
//        {
//            MessageSender::sendNumeric(getServerName(), client, 471, chanName + " :Cannot join channel (+l)");
//            return; 
//        }
//        chan->addMember(client, false);
//    }
//
//    //JOIN reply
//    std::string joinMsg = ":" + client->getNick() + "!" + client->getUser() + "@" + client->getHost()
//                        + "JOIN :" + chanName + "\r\n";
//    chan->broadcast(joinMsg);
//
//    //Topic
//    if (!chan->getTopic().empty())
//        MessageSender::sendNumeric(getServerName(), client, 332, chanName + " :" + chan->getTopic());
//    else 
//        MessageSender::sendNumeric(getServerName(), client, 331, chanName + " :No topic is set");
//    
//    // NAMES list                       <<<<<------Take a look at this
//    std::ostringstream oss;
//    oss << "= " << chanName << " :";
//    const std::map<int, Client*> &members = chan->getChannelMembers();
//    for (std::map<int, Client*>::const_iterator it = members.begin(); it != members.end(); ++it) {
//        if (chan->isOperator(it->first))
//            oss << "@" << it->second->getNick() << " ";
//        else
//            oss << it->second->getNick() << " ";
//    }
//    MessageSender::sendNumeric(getServerName(), client, 353, oss.str()); // RPL_NAMREPLY
//    MessageSender::sendNumeric(getServerName(), client, 366, chanName + " :End of /NAMES list");
//}

// --- sending helpers ---              <-----Check if the function "send" is defined
//void Server::sendToClient(Client *client, const std::string &msg)
//{
//    std::cout << msg.c_str() << std::endl;
//    //for debugging purposes, we should start using a simple cout 
//    (void) client;
//    //send(client->getFd(), msg.c_str(), msg.size(), 0);
//}
//
//void Server::sendNumeric(Client *client, int code, const std::string &msg)
//{
//    std::ostringstream oss;
//    oss << ":" << _serverName << " " << code << " " << client->getNick() << " " << msg << "\r\n";
//    sendToClient(client, oss.str());
//}

