#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

class Client; 

class Channel
{
    private:
        std::string             _name;      //channel name; up to 200 chars
        std::string             _topic;     //current topic
        std::map<int, Client *> _members;   //Client has already its fd, check if this is necessary
        std::set<int>           _operators; //who are operators; check if this is a good approach
        bool                    _inviteOnly; //if the channel is invite only (+i flag?)
        bool                    _kMode;     //If it has a password
        bool                    _lMode;     //If it has a limit
        std::string             _key;       //password if mode +k
        int                     _userLimit; //if mode +l
        std::set<int>           _invited;   //invited clients; set to avoid duplicates

        //forbid copy
        Channel(const Channel &other);
        Channel &operator=(const Channel &other);

    public:
        Channel(const std::string &name);
        ~Channel();

        //getters 
        const std::string &getName() const;
        const std::string &getTopic() const;
        int                getUserCount() const;
        bool               isInviteOnly() const;
        bool               hasKey() const;
        bool               hasLimit() const;
        const std::string &getKey() const;
        int                getUserLimit() const;
        const std::map<int, Client *> getChannelMembers() const;

        // mutators
        void setTopic(const std::string& topic);
        void setInviteOnly(bool value);
        void setKey(const std::string& key);
        void setKMode(bool value);
        void removeKey();
        void setUserLimit(int limit);

        // membership management
        bool addMember(Client *client, bool isOp = false);
        void removeMember(Client *client);
        bool isMember(int fd) const;
        bool isOperator(int fd) const;
        void promoteToOp(int fd);
        void demoteFromOp(int fd);

        // invite handling
        void invite(int fd);
        bool isInvited(int fd) const;

        // broadcasting
        void broadcast(const std::string &message) const; //Check params

        //aux functions
        bool isEmpty();

};