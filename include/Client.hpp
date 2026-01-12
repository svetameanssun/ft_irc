#pragma once

#include <string>
#include <vector>
#include <netinet/in.h>     //for sockaddr_in, look if if there is another way
#include ""

#define MAX_CHANNELS_JOINED 15

class Client
{
    //TODO: A max limit of joined channels must be set; the implementation depends on the server, but for us, 10 should be just fine
    private:
        int         _fd;            //for the socket
        bool        _passAccepted;  //The client provided the good password
        std::string _nickname;      //9 chars max, need to specifiy it 
        std::string _username;      //USER
        std::string _realname;      //Real name (from USER command)  <<---- check if there are this many fields
        std::string _hostname;      //Hostname (or IP string)
        bool        _registered;    //true if fully registered (NICK+USER)
        bool        _isOperator;    //operator attribute <<---- should be under channel attrs
        std::string _buffer;        //partial data received, until newline
        std::vector<std::string> _channels; // list of joined channels    <<---- check if this is the best design
        int         _nbrChannelJoined; //keep the count of the channels to see if it reachs the limit
        [LANA EDIT]
        CommandParser *_cmdParser;
        [---------]
        //copy not available
        Client(const Client &other);
        Client &operator=(const Client &other);
    
    public:
        Client();
        Client(int fd);
        Client(int fd, const std::string &hostname);
        ~Client();

        //getters
        int   getFd() const;
        const std::string &getNick() const;
        const std::string &getUser() const;
        const std::string &getRealName() const;
        const std::string &getHost() const;
        std::string getPrefix() const;
        bool isRegistered() const;
        bool isOperator() const;
        bool getPassAccepted() const;
        bool isChanLimitReached() const;

        //setters
        void setNick(const std::string &nick);
        void setUser(const std::string &user);
        void setRealName(const std::string &realname);
        void setRegistered(bool value);
        void setOperator(bool value);
        void setPassAccepted(bool value);
        void setLimitReached(bool value);

        [LANA EDIT]
        void createCmdParser(std::string rawStr);
        [---------]
        

        //buffer handling, do it when we know how to handle data
        void appendToBuffer(const std::string &data);
        const std::string &getBuffer();
        std::vector<std::string> extractMessages();

        //channel handling; look if it is really necessary to get the channels
        void joinChannel(const std::string &name);
        void leaveChannel(const std::string &name);
        const std::vector<std::string> &getChannels() const;
};

