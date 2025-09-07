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

class Client;   // forward declaration
class Channel;  // forward declaration

class Server {
private:
    int                         _listenFd;      // listening socket
    int                         _port;          // port number
    std::string                 _password;      // optional server password
    std::map<int, Client*>      _clients;       // fd -> Client*
    std::map<std::string, Channel*> _channels;  // name -> Channel*
    std::vector<struct pollfd>  _pollFds;       // list of poll fds
    bool                        _running;       // server loop flag

    Server(const Server &other);                // Copy of the server is not allowed
    Server &operator=(const Server& other);

public:
    Server();                                       
    Server(int port, const std::string& password);
    ~Server();                                     

    // core methods
    void    initSocket();
    void    run();
    void    stop();

    // getters
    int     getPort() const;
    const std::string &getPassword() const;

    // setters
    void    setPort(int port);
    void    setPassword(std::string password);
    
    // client/channel management
    void    addClient(int fd);
    void    removeClient(int fd);
    void    addChannel(const std::string &name);
    Channel *findChannel(const std::string &name);
};
