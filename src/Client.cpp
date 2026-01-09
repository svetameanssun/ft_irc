#include "Client.hpp"
#include "utils.hpp"
#include <algorithm>

Client::Client() : _fd(-1), _registered(false), _isOperator(false) {}
Client::Client(int fd) : _fd(fd), _registered(false), _isOperator(false) {}
Client::Client(int fd, const std::string &hostname)
    : _fd(fd), _hostname(hostname), _registered(false), _isOperator(false) {}
Client::~Client() {}

//getters
int Client::getFd() const { return _fd; }
const std::string &Client::getNick() const { return _nickname; }
const std::string &Client::getUser() const { return _username; }
const std::string &Client::getRealName() const { return _realname; }
const std::string &Client::getHost() const { return _hostname; }
std::string Client::getPrefix() const { return getNick() + "!" + getUser() + "@" + getHost(); }
bool Client::isRegistered() const { return _registered; }
bool Client::isOperator() const { return _isOperator; }
bool Client::getPassAccepted() const { return _passAccepted; }
bool Client::isChanLimitReached() const { return _nbrChannelJoined; }


//setters
void Client::setNick(const std::string &nick) { _nickname = nick; }
void Client::setUser(const std::string &user) { _username = user; }
void Client::setRealName(const std::string &realname) { _realname = realname; }
void Client::setRegistered(bool value) { _registered = value; }
void Client::setOperator(bool value) { _isOperator = value; }
void Client::setPassAccepted(bool value) { _passAccepted = value; }
void Client::setLimitReached(bool value) { _nbrChannelJoined = value; }
// Buffer handling
//TODO: [NETWORKING] We need to work on this
void Client::appendToBuffer(const std::string &data) { _buffer += data; }
const std::string &Client::getBuffer() { return _buffer; }  

std::vector<std::string> Client::extractMessages()
{
    std::vector<std::string> messages;
    std::string::size_type pos;

    while ((pos = _buffer.find("\r\n")) != std::string::npos)
    {
        std::string msg = _buffer.substr(0, pos);
        messages.push_back(msg);
        _buffer.erase(0, pos + 2); // remove processed message
    }

    return messages;
}

// Channel handling; of course we will need to call the proper procedures to 
// ask the server->ChannelManager to do it 
void Client::joinChannel(const std::string &name)
{
    log_debug("[Client] I want to join a channel :D");
    if (std::find(_channels.begin(), _channels.end(), name) == _channels.end())
    {
        _channels.push_back(name);
        _nbrChannelJoined++;
    }
}

void Client::leaveChannel(const std::string &name)
{
    log_debug("[Client] I want to leave a channel :(");
    std::vector<std::string>::iterator it =
        std::find(_channels.begin(), _channels.end(), name);
    if (it != _channels.end())
    {
        _channels.erase(it);
        _nbrChannelJoined--;
    }
}

const std::vector<std::string> &Client::getChannels() const
{
    log_debug("Hi I am client %s and these are my channels: ", getNick().c_str());
    return _channels;
}