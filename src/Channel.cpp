#include "Channel.hpp"

//Constructor 
Channel::Channel(const std::string &name)
: _name(name), _iMode(false),_tMode(true), _kMode(false), _lMode(false), _userLimit(-1) {}

Channel::~Channel() {}

//Getters
const std::string &Channel::getName() const { return _name; }
const std::string &Channel::getTopic() const { return _topic; }
int Channel::getUserCount() const { return _members.size(); }
bool Channel::isInviteOnly() const { return _iMode; }
bool Channel::hasKey() const { return _kMode; }
bool Channel::hasLimit() const { return _lMode; }
bool Channel::isTopicLocked() const { return _tMode; }
const std::string& Channel::getKey() const { return _key; }
int Channel::getUserLimit() const { return _userLimit; }
bool Channel::userExists(int fd) const
{
    const std::map<int, Client*> &members = _members;
    return members.find(fd) != members.end();
}

const std::map<int, Client *> Channel::getChannelMembers() const { return _members; }

// Mutators
void Channel::setTopic(const std::string &topic) { _topic = topic; }
void Channel::setInviteOnly(bool value) { _iMode = value; }
void Channel::setKMode(bool value) { _kMode = value; }
void Channel::setTMode(bool value) { _tMode = value ;}
void Channel::setKey(const std::string &key) { _key = key; }
void Channel::removeKey() { _key.clear(); }
void Channel::setUserLimit(int limit) { _userLimit = limit; }

// Membership management
bool Channel::addMember(Client *client, bool isOp)
{
    if (_userLimit > 0 && (int)_members.size() >= _userLimit)
    {
        log_warning("[Channel] Channel is full, cannot add the member");
        return false;
    }
    int fd = client->getFd();
    if (_members.find(fd) != _members.end())
    {
        log_warning("[Channel] the user is already a member");
        return false;
    }
    _members[fd] = client;
    client->joinChannel(this->getName());
    if (isOp)
    {
        log_msg("[Channel]: the user is an operator, added to op list");
        _operators.insert(fd);
    }
    return true;
}

    void Channel::removeMember(Client *client)
    {
        int fd = client->getFd();
        _members.erase(fd);
        _operators.erase(fd);
        _invited.erase(fd);
        client->leaveChannel(this->getName());
        log_msg("[Channel]: The member has been deleted from the channel");
        if (this->getUserCount() == 1)
        {
            log_msg("[Channel]: Only one member on the channel %s", this->getName().c_str());
            std::map<int, Client *>::iterator it = _members.begin();
            int fd = it->first;
            promoteToOp(fd);
        }
    }

bool Channel::isMember(int fd) const { return _members.find(fd) != _members.end(); }

bool Channel::isOperator(int fd) const { return _operators.find(fd) != _operators.end(); }

void Channel::promoteToOp(int fd)
{
    if (isMember(fd))
        _operators.insert(fd);
    log_msg("[Channel]: The member has been added to operators");
}

void Channel::demoteFromOp(int fd) { _operators.erase(fd); }

void Channel::invite(int fd) { _invited.insert(fd); }

bool Channel::isInvited(int fd) const { return _invited.find(fd) != _invited.end(); }

void Channel::removeFromInviteList(int fd)
{
    if (_invited.find(fd) != _invited.end())
    {
        log_msg("[Channel] client deleted from invited list");
        _invited.erase(fd);
    }
    else
        log_msg("[Channel] removeFromInviteList: client was not in the invite list");
}


void Channel::broadcast(const std::string &message) const
{
    int excludeFd = -1;
    log_msg("[Channel] broadcasting to all users: ");
    printChannelMembers();
    for (std::map<int, Client *>::const_iterator it = _members.begin(); it != _members.end(); it++)
    {
        int fd = it->first;
        Client *c = it->second;
        if (!c) continue;
        if (fd == excludeFd) continue; // skip excluded fd
        // send raw message to each member
        MessageSender::sendToClient(c, message);
        log_msg("MessageSender: sending to client: %s", c->getNick().c_str());
    }
}

void Channel::broadcast(const std::string &message, int userFd) const
{
    int excludeFd = -1;
    log_msg("[Channel] broadcasting to all users: ");
    printChannelMembers();
    for (std::map<int, Client *>::const_iterator it = _members.begin(); it != _members.end(); it++)
    {
        int fd = it->first;
        Client *c = it->second;
        if (!c) continue;
        if (fd == excludeFd || fd == userFd) continue; // skip excluded fd
        // send raw message to each member
        MessageSender::sendToClient(c, message);
        log_msg("MessageSender: sending to client: %s", c->getNick().c_str());
    }
}


bool Channel::isEmpty() { return _members.empty(); }

void Channel::printChannelMembers() const
{
    log_debug("Channel Members of %s:", _name.c_str());
    for (std::map<int, Client *>::const_iterator it = _members.begin(); it != _members.end(); it++)
    {
        Client *c = it->second;
        if (c)
            log_debug(" - FD: %d - Nick: %s", it->first, c->getNick().c_str());
    }
}