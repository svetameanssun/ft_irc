#include "ClientManager.hpp"
#include "Server.hpp"

ClientManager::ClientManager() {}

//ClientManager::ClientManager(Server &server) : _server(server) {}

ClientManager::~ClientManager()
{
    //TODO:[POINTERS] there are problems with doble free here. Check what happens
    //for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    //    delete it->second;
}

void ClientManager::addClient(Client *client)//Add hostname if needed; maybe override, const std::string &hostname)
{
    // TODO: resolve actual hostname with getpeername() maybe??
    _clients[client->getFd()] = client;
    log_warning("[Client Manager] addClient: Connection not established yet");

    log_msg("[ClientManager] Added client fd=%d", client->getFd());
}

void ClientManager::removeClient(int fd)
{
    std::map<int, Client*>::iterator it = _clients.find(fd);
    if (it != _clients.end()) {
        //TODO: [POINTERS]Right now clients are declared on stack, not valid deletion
        //delete it->second;
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
    this->printClients();
    for (std::map<int, Client*>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->second->getNick() == nick)
        {
            std::cout << nick << std::endl;
            log_msg("[Client Manager]: Found nickname: %s", it->second->getNick().c_str());
            return it->second;
        }
    }
    log_msg("[Client Manager]: User not found");
    return NULL;
}

void ClientManager::broadcast(const std::string &msg, int excludeFd)
{
    log_msg("[Client Mamanger]: Broadcasting to all the clients: ");
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->first == excludeFd) continue;
        MessageSender::sendToClient(it->second, msg);
        std::cout << "[Broadcast] " << msg << std::endl;
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
    //for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
    //    delete it->second;
    //_clients.clear();
    log_warning("[Client Manager]: resources not freed");
}