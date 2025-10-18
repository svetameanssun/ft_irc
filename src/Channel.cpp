#include "Channel.hpp"

//Constructor 
Channel::Channel(const std::string &name)
: _name(name), _iMode(false), _userLimit(-1) {}

Channel::~Channel()
{
    log_warning("Resources from the channel not freed");
}

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
        log_msg("Channel is full, cannot add the member");
        return false;
    }
    int fd = client->getFd();
    if (_members.find(fd) != _members.end())
    {
        log_msg("Channel: the user is already a member");
        return false; // already member
    }
    _members[fd] = client;
    if (isOp)
    {
        log_msg("Channel: the user is a operator, added to op list");
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
    log_msg("Channel: The member has been deleted from the channel");
}

bool Channel::isMember(int fd) const { return _members.find(fd) != _members.end(); }

bool Channel::isOperator(int fd) const { return _operators.find(fd) != _operators.end(); }

void Channel::promoteToOp(int fd)
{
    if (isMember(fd))
        _operators.insert(fd);
    log_msg("Channel: The member has been added to operators");
}

void Channel::demoteFromOp(int fd) { _operators.erase(fd); }

// Invite handling
void Channel::invite(int fd) { _invited.insert(fd); }

bool Channel::isInvited(int fd) const { return _invited.find(fd) != _invited.end(); }

void Channel::broadcast(const std::string &message) const
{
    int excludeFd = -1;
    log_msg("Channel: broadcasting to all users: ");
    for (std::map<int, Client *>::const_iterator it = _members.begin(); it != _members.end(); ++it)
    {
        int fd = it->first;
        Client *c = it->second;
        if (!c) continue;
        if (fd == excludeFd) continue; // skip excluded fd
        // send raw message to each member
        MessageSender::sendToClient(c, message);
    }
}

bool Channel::isEmpty() { return _members.empty(); }
