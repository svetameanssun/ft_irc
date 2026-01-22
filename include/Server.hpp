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
#include "CommandHandler.hpp"
#include "ClientManager.hpp"
#include "ChannelManager.hpp"
#include "NetworkManager.hpp"
#include "Channel.hpp"
#include "CommandParser.hpp"
#include "MessageSender.hpp"
#include "utils.hpp"
#include <sstream>
#include <csignal>
#include "signals.hpp"

class Client;   // forward declaration
class Channel;  // forward declaration

class Server
{
    private:
        const std::string           _serverName;    // Name of the server
        int                         _listenFd;      // listening socket
        int                         _port;          // port number
        std::string                 _password;      // optional server password
        std::vector<struct pollfd>  _pollFds;       // list of poll fds
        bool                        _running;       // server loop flag
        AParserResult              *_parsingResult; // result of the parse

        CommandHandler              _cmdHandler;    
        ClientManager               _clientManager;
        ChannelManager              _channelManager;
        NetworkManager              _networkManager;


        Server();                                   // We do not want a server without port   
        Server(const Server &other);                // Copy of the server is not allowed
        Server &operator=(const Server& other);
        //[LANA EDIT]
        CommandParser *_cmdParser;
        //[---------]
        //[---------]
        //[---------]

    public:

        //[LANA EDIT]
        CommandParser *getCmdParser();
        void createCmdParser(std::string rawStr);
        //[---------]
        Server();                                       
        Server(int port, const std::string& password);
        ~Server();                                     

        // core methods
        void    init();
        void    run();

        // is this still needed?
        void    initSocket();
        void    stop();

        // getters
        const   std::string &getServerName() const;
        int     getPort() const;
        const   std::string &getPassword() const;

        // setters
        void    setPort(int port);
        void    setPassword(const std::string password);

        // Managers accessors
        ClientManager &getClientManager() { return _clientManager; }
        ChannelManager &getChannelManager() { return _channelManager; }

        // command handling
        int     launchParsing();
        void    dispatchCommand(Client *client, const std::string &cmd);
        void    executeRoutine(Client *client, std::string &rawCommand);

        // aux
        void    deleteParserResult(); 

        // handle client data 
        void    onClientConnected(int fd);
        void    onClientData(int fd);
        void    disconnectClient(int fd, const std::string &reason);
};
