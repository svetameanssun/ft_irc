#pragma once

#include <map>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include "utils.hpp"
#include <string>
#include "Client.hpp"

class Server;


class ClientManager
{
private:
    std::map<int, Client*> _clients;     
    ClientManager(const ClientManager &other);
    ClientManager &operator=(const ClientManager &other);

public:
    ClientManager();
    ~ClientManager();

    // Management
    void addClient(Client *client);
    void removeClient(int fd);
    bool clientExists(int fd);
    Client *findByFd(int fd);
    Client *findByNick(const std::string &nick);

    // Utility
    void broadcast(const std::string &msg, int excludeFd = -1);

    // For debugging
    void printClients() const;

    void freeResources();
};
