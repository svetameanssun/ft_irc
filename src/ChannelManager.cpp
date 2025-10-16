#include "ChannelManager.hpp"
#include "Client.hpp"
#include "utils.hpp"
#include <iostream>

ChannelManager::ChannelManager() {}
//ChannelManager::ChannelManager(Server &server) : _server(server) {}

ChannelManager::~ChannelManager()
{
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
        delete it->second;
    log_msg("All channels have been deleted by the Channel Manager");
}

Channel *ChannelManager::addChannel(const std::string &name)
{
    // prevent duplicates
    std::map<std::string, Channel*>::iterator it = _channels.find(name);
    if (it != _channels.end())
        return it->second;

    Channel *chan = new Channel(name);
    _channels[name] = chan;
    log_msg("ChannelManager created channel %s", name.c_str());
    return chan;
}

Channel *ChannelManager::findChannel(const std::string &name)
{
    for (std::map<std::string, Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
    {
        if (it->first == name)
            return it->second;
    }
    return NULL;
}

void ChannelManager::removeChannel(const std::string &name)
{
    std::map<std::string, Channel*>::iterator it = _channels.find(name);
    if (it != _channels.end())
    {
        delete it->second;
        _channels.erase(it);
        log_msg("ChannelManager removed channel %s", name.c_str());
    }
}

void ChannelManager::broadcastToChannel(const std::string &name, const std::string &msg)
{
    Channel *chan = findChannel(name);
    if (chan) 
        chan->broadcast(msg);
    log_debug("ChannelManager is looking for a channel to broadcast");
}

void ChannelManager::broadcastToJoinedChannels(int fd, const std::string &msg)
{
    for(std::map<std::string, Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
    {
        if (it->second->isMember(fd))
            it->second->broadcast(msg);
    }
    log_debug("ChannelManager is looking for all channels where user belongs to broadcast");

}

void ChannelManager::removeClientFromChannels(Client *client)
{
    for (std::map<std::string, Channel*>::iterator it = _channels.begin();
         it != _channels.end(); )
    {
        Channel *chan = it->second;
        if (chan->isMember(client->getFd()))
        {
            chan->removeMember(client);
            if (chan->isEmpty())
            {
                removeChannel(it->first);
                it = _channels.begin(); // restart iterator, since map changed
                continue;
            }
        }
        ++it;
    }
    log_debug("ChannelManager is removing the user from all the channels");

}

void ChannelManager::printChannels() const
{
    std::cout << "Active channels:" << std::endl;
    for (std::map<std::string, Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
        std::cout << " - " << it->first << " (" << it->second->getUserCount() << " users)" << std::endl;
}


void ChannelManager::freeResources()
{
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
        delete it->second;
    _channels.clear();
    log_debug("ChannelManager has ended its duty, goodbye!");
}