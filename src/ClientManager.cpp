#include "ClientManager.hpp"

ClientManager::ClientManager() {}

//ClientManager::ClientManager(Server &server) : _server(server) {}

ClientManager::~ClientManager()
{
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
        delete it->second;
}

void ClientManager::addClient(int fd) //Add hostname if needed; maybe override, const std::string &hostname)
{
    Client *client = new Client(fd);  // TODO: resolve actual hostname with getpeername() maybe??
    _clients[fd] = client;
    log_err("addClient: Connection not established yet");

    //TODO: When connections will be implemented
    // Add to pollfd list
    //struct pollfd pfd;
    //pfd.fd = fd;
    //pfd.events = POLLIN;
    //pfd.revents = 0;
    //_pollFds.push_back(pfd);

    log_msg("[ClientManager] Added client fd=%d", fd);
}

void ClientManager::removeClient(int fd)
{
    std::map<int, Client*>::iterator it = _clients.find(fd);
    if (it != _clients.end()) {
        delete it->second;
        _clients.erase(it);
        std::cout << "[ClientManager] Removed client fd=" << fd << std::endl;
    }

    //TODO: when we will implement the network part
    log_err("removeClient: connection not established yet");
    // Erase from pollfd list
    //_pollFds.erase(
    //    std::remove_if(_pollFds.begin(), _pollFds.end(),
    //                   [fd](const struct pollfd& p) { return p.fd == fd; }),
    //    _pollFds.end());

    // Close socket
    close(fd);
}

bool ClientManager::clientExists(int fd) { return _clients.find(fd) != _clients.end(); }


Client *ClientManager::findByFd(int fd)
{
    log_warning("findByFd: check me plz");
    return _clients.count(fd) ? _clients[fd] : NULL;            //TODO: Check if this is ok
}

Client *ClientManager::findByNick(const std::string &nick)
{
    log_msg("Finding by name from ClientManager: ");
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second->getNick() == nick)
        {
            log_msg("Found: %s", it->second->getNick().c_str());
            return it->second;
        }
    }
    log_msg("User not found by ClientManager");
    return NULL;
}

void ClientManager::broadcast(const std::string &msg, int excludeFd)
{
    log_msg("Broadcasting to all the clients: ");
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->first == excludeFd) continue;
        // sendToClient(it->second, msg); // later use MessageSender
        std::cout << "[Broadcast] " << msg << std::endl;
    }
}

void ClientManager::printClients() const
{
    std::cout << "Active clients:" << std::endl;
    for (std::map<int, Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
        std::cout << " - FD: " << it->first << " Nick: " << it->second->getNick() << std::endl;
}

void ClientManager::freeResources()
{
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
        delete it->second;
    _clients.clear();
    log_debug("Bye bye from the ClientManager, it has been a pleasure :D");
}