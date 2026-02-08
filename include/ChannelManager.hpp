#pragma once

#include <map>
#include <string>
#include <iostream>
#include "utils.hpp"
#include "Channel.hpp"
#include "Client.hpp"


class Server;


class ChannelManager
{
private:
    std::map<std::string, Channel*> _channels;
    // private; just for compliance
    ChannelManager(const ChannelManager &other);
    ChannelManager &operator=(const ChannelManager &other);

public:
    ChannelManager();
    ~ChannelManager();

    Channel *addChannel(const std::string &name);
    Channel *findChannel(const std::string &name);
    void removeChannel(const std::string &name);

    void broadcastToChannel(const std::string &name, const std::string &msg);
    void broadcastToJoinedChannels(int fd, const std::string &msg);

    void removeClientFromChannels(Client *client);

    void printChannels() const;

    void freeResources();
};
