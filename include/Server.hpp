#pragma once

#include <map>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>
#include <iostream>
#include "Client.hpp"

class Client;   // forward declaration
class Channel;  // forward declaration

class Server
{
    private:
        const std::string           _serverName;    // Name of the server
        int                         _listenFd;      // listening socket
        int                         _port;          // port number
        std::string                 _password;      // optional server password
        std::map<int, Client *>      _clients;       // fd -> Client*
        std::map<std::string, Channel *> _channels;  // name -> Channel*
        std::vector<struct pollfd>  _pollFds;       // list of poll fds
        bool                        _running;       // server loop flag

        Server(const Server &other);                // Copy of the server is not allowed
        Server &operator=(const Server& other);

    public:
        Server();                                       
        Server(int port, const std::string& password);
        ~Server();                                     

        // core methods
        void    init(char *argv[]);
        void    initSocket();
        void    stop();

        // getters
        const std::string &getServerName() const;
        int     getPort() const;
        const std::string &getPassword() const;

        // setters
        void    setPort(int port);
        void    setPassword(const std::string password);

        // client management
        void    addClient(int fd);
        void    removeClient(int fd);

        // Channel management 
        Channel *addChannel(const std::string &name);
        Channel *findChannel(const std::string &name) const;
        void    removeChannel(const std::string& name);

        // command handling 
        void handleJoin(Client *client, const std::string &chanName, const std::string &key);
        //void sendToClient(Client *client, const std::string &msg);
        //void sendNumeric(Client *client, int code, const std::string &msg);
};
