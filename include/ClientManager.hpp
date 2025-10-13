#pragma once

#include <map>
#include <string>
#include "Client.hpp"

class Server;


class ClientManager
{
private:
    std::map<int, Client*> _clients; // fd -> Client*       
    //Server &_server;                                      //TODO: Check if reference to server is needed

public:
    ClientManager();
    //ClientManager(Server &server);
    ~ClientManager();

    // Management
    void addClient(int fd, const std::string &hostname);
    void removeClient(int fd);
    Client *findByFd(int fd);
    Client *findByNick(const std::string &nick);

    // Utility
    void broadcast(const std::string &msg, int excludeFd = -1);

    // For debugging
    void printClients() const;

    void freeResources();
};
