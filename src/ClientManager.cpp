#include "ClientManager.hpp"
#include "Server.hpp"

ClientManager::ClientManager() {}

//Not needed for the moment
//ClientManager::ClientManager(Server &server) : _server(server) {}

ClientManager::~ClientManager() { freeResources(); }

void ClientManager::addClient(Client *client)
{
    _clients[client->getFd()] = client;
    log_msg("[ClientManager] Added client with fd=%d", client->getFd());
}

void ClientManager::removeClient(int fd)
{
    std::map<int, Client*>::iterator it = _clients.find(fd);
    if (it != _clients.end())
    {
        delete it->second;
        _clients.erase(it);
        std::cout << "[ClientManager] Removed client fd=" << fd << std::endl;
    }
    close(fd);
}

bool ClientManager::clientExists(int fd) { return _clients.find(fd) != _clients.end(); }


Client *ClientManager::findByFd(int fd)
{
    std::map<int, Client*>::iterator it = _clients.find(fd);
    return (it != _clients.end()) ? it->second : NULL;
}

Client *ClientManager::findByNick(const std::string &nick)
{
    log_msg("[Client Manager]: Finding by name: ");
    if (nick.empty())
    {
        log_warning("[Client Manager]: Nick is empty, returning...");
        return NULL;
    }
    for (std::map<int, Client*>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->second->getNick() == nick)
        {
            std::cout << nick << std::endl;
            return it->second;
        }
    }
    log_msg("[Client Manager]: User not found in the Client list");
    return NULL;
}

void ClientManager::broadcast(const std::string &msg, int excludeFd)
{
    log_msg("[Client Manager]: Broadcasting to all the clients: ");
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->first == excludeFd) continue;
        MessageSender::sendToClient(it->second, msg);
    }
}

void ClientManager::printClients() const
{
    std::cout << "Active clients:" << std::endl;
    for (std::map<int, Client*>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
        std::cout << " - FD: " << it->first << " Nick: " << it->second->getNick() << std::endl;
}

void ClientManager::freeResources()
{
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
        delete it->second;
    _clients.clear();
    log_msg("All clients have been deleted by the Client Manager");
}