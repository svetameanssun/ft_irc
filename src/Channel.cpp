#include "Channel.hpp"
#include <algorithm>
#include <iostream>

//Constructor 
Channel::Channel(const std::string &name)
: _name(name), _inviteOnly(false), _userLimit(-1) {}

Channel::~Channel() {}

//Getters
const std::string& Channel::getName() const { return _name; }
const std::string& Channel::getTopic() const { return _topic; }
int Channel::getUserCount() const { return _members.size(); }
bool Channel::isInviteOnly() const { return _inviteOnly; }
bool Channel::hasKey() const { return _kMode; }
bool Channel::hasLimit() const { return _lMode; }
const std::string& Channel::getKey() const { return _key; }
int Channel::getUserLimit() const { return _userLimit; }
const std::map<int, Client *> Channel::getChannelMembers() const { return _members; }


// Mutators
void Channel::setTopic(const std::string& topic) { _topic = topic; }
void Channel::setInviteOnly(bool value) { _inviteOnly = value; }
void Channel::setKMode(bool value) { _kMode = value; }
void Channel::setKey(const std::string& key) { _key = key; }
void Channel::removeKey() { _key.clear(); }
void Channel::setUserLimit(int limit) { _userLimit = limit; }

// Membership management
bool Channel::addMember(Client *client, bool isOp)
{
    if (_userLimit > 0 && (int)_members.size() >= _userLimit)
        return false;
    int fd = client->getFd();
    if (_members.find(fd) != _members.end())
        return false; // already member
    _members[fd] = client;
    if (isOp)
        _operators.insert(fd);
    return true;
}

void Channel::removeMember(Client *client)
{
    int fd = client->getFd();
    _members.erase(fd);
    _operators.erase(fd);
    _invited.erase(fd);
}

bool Channel::isMember(int fd) const { return _members.find(fd) != _members.end(); }

bool Channel::isOperator(int fd) const { return _operators.find(fd) != _operators.end(); }

void Channel::promoteToOp(int fd)
{
    if (isMember(fd))
        _operators.insert(fd);
}

void Channel::demoteFromOp(int fd) { _operators.erase(fd); }

// Invite handling
void Channel::invite(int fd) { _invited.insert(fd); }

bool Channel::isInvited(int fd) const { return _invited.find(fd) != _invited.end(); }

void Channel::broadcast(const std::string &message) const
{
    int excludeFd = -1;
    for (std::map<int, Client *>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
    if (it->first == excludeFd)
        continue;
    // TODO: integrate with Server::sendMessage() when we build it
    std::cout << "Sending to " << it->second->getNick()
              << ": " << message << std::endl;
    }
}
