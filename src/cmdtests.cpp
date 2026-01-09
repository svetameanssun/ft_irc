#include <iostream>
#include "Server.hpp"
#include "Client.hpp"
#include "cmdtests.hpp"

//TODO: Remove this file once it is done
// Utility: ensure client exists in the registry
void ensureClientRegistered(Server &server, Client *client)
{
    ClientManager &manager = server.getClientManager();
    int fd = client->getFd();

    if (!manager.clientExists(fd))
    {
        std::cout << "[INFO] Client not found in registry. Registering client with fd " << fd << "...\n";
        manager.addClient(client);
    }
    else
    {
        std::cout << "[INFO] Client already with fd (fd " << fd << ").\n";
    }
}

// === PASS Test ===
void runTestPass(Server &server, Client *client, const std::string &password)
{
    ensureClientRegistered(server, client);

    std::cout << "\n=== TEST: " << client->getNick() << " PASS " << password << " ===\n";

    std::string rawCommand = "PASS " + password;
    server.executeRoutine(client, rawCommand);

    std::cout << "===========================================\n";
}

// === NICK Test ===
void runTestNick(Server &server, Client *client, const std::string &newNick)
{
    ensureClientRegistered(server, client);

    std::cout << "\n=== TEST: " << client->getNick() << " NICK " << newNick << " ===\n";

    std::string rawCommand = "NICK " + newNick;
    server.executeRoutine(client, rawCommand);

    std::cout << "===========================================\n";
}

// === USER Test (FIXED, RFC-compliant) ===
void runTestUser(Server &server, Client *client,
                 const std::string &username, const std::string &realname)
{
    ensureClientRegistered(server, client);

    std::cout << "\n=== TEST: " << client->getNick() << " USER " << username
              << " " << realname << " ===\n";

    // RFC format: USER <username> 0 * :<realname>
    std::string rawCommand = "USER " + username + " 0 * :" + realname;

    server.executeRoutine(client, rawCommand);

    std::cout << "===========================================\n";
}

// === JOIN Test (FIXED to comply with RFC) ===
void runTestJoin(Server &server, Client *client,
                 const std::string &channel, const std::string &key)
{
    ensureClientRegistered(server, client);

    std::cout << "\n=== TEST: " << client->getNick() << " JOIN " << channel;
    if (!key.empty()) std::cout << " " << key;
    std::cout << " ===\n";

    std::string rawCommand = "JOIN " + channel;
    if (!key.empty())
        rawCommand += " " + key;

    server.executeRoutine(client, rawCommand);

    std::cout << "===========================================\n";
}

// === PRIVMSG Test ===
void runTestPrivmsg(Server &server, Client *sender,
                    const std::string &target, const std::string &message)
{
    ensureClientRegistered(server, sender);

    std::cout << "\n=== TEST: " << sender->getNick()
              << " PRIVMSG " << target << " :"
              << message << " ===\n";

    std::string raw = "PRIVMSG " + target + " :" + message;
    server.executeRoutine(sender, raw);

    std::cout << "===========================================\n";
}

// === NOTICE Test ===
void runTestNotice(Server &server, Client *sender,
                   const std::string &target, const std::string &message)
{
    ensureClientRegistered(server, sender);

    std::cout << "\n=== TEST: " << sender->getNick()
              << " NOTICE " << target << " :"
              << message << " ===\n";

    std::string raw = "NOTICE " + target + " :" + message;
    server.executeRoutine(sender, raw);

    std::cout << "===========================================\n";
}

// === PART Test ===
void runTestPart(Server &server, Client *client,
                 const std::string &channels,
                 const std::string &comment)
{
    ensureClientRegistered(server, client);

    std::cout << "\n=== TEST: " << client->getNick()
              << " PART " << channels;
    if (!comment.empty())
        std::cout << " :" << comment;
    std::cout << " ===\n";

    std::string raw = "PART " + channels;
    if (!comment.empty())
        raw += " :" + comment;

    server.executeRoutine(client, raw);

    std::cout << "===========================================\n";
}

// === QUIT Test ===
void runTestQuit(Server &server, Client *client, const std::string &message)
{
    ensureClientRegistered(server, client);

    std::cout << "\n=== TEST: " << client->getNick()
              << " QUIT " << (message.empty() ? "" : ":" + message)
              << " ===\n";

    std::string raw = "QUIT";
    if (!message.empty())
        raw += " :" + message;

    server.executeRoutine(client, raw);

    std::cout << "===========================================\n";
}

// === KICK Test ===
void runTestKick(Server &server, Client *sender,
                 const std::string &channel,
                 const std::string &target,
                 const std::string &comment)
{
    ensureClientRegistered(server, sender);

    std::cout << "\n=== TEST: " << sender->getNick()
              << " KICK " << channel << " " << target;
    if (!comment.empty())
        std::cout << " :" << comment;
    std::cout << " ===\n";

    std::string raw = "KICK " + channel + " " + target;
    if (!comment.empty())
        raw += " :" + comment;

    server.executeRoutine(sender, raw);

    std::cout << "===========================================\n";
}

// === INVITE Test ===
void runTestInvite(Server &server, Client *sender,
                   const std::string &target,
                   const std::string &channel)
{
    ensureClientRegistered(server, sender);

    std::cout << "\n=== TEST: " << sender->getNick()
              << " INVITE " << target << " " << channel << " ===\n";

    std::string raw = "INVITE " + target + " " + channel;
    server.executeRoutine(sender, raw);

    std::cout << "===========================================\n";
}


void runTestTopic(Server &server, Client *client,
                  const std::string &channel,
                  const std::string &topic)
{
    ensureClientRegistered(server, client);

    std::cout << "\n=== TEST: " << client->getNick() << " TOPIC " << channel;
    if (!topic.empty())
        std::cout << " :" << topic;
    std::cout << " ===\n";

    std::string raw = "TOPIC " + channel;
    if (!topic.empty())
        raw += " :" + topic;

    server.executeRoutine(client, raw);

    std::cout << "===========================================\n";
}

// === MODE Test ===
void runTestMode(Server &server, Client *client,
                 const std::string &target,
                 const std::string &modes,
                 const std::string &params)
{
    ensureClientRegistered(server, client);

    std::cout << "\n=== TEST: " << client->getNick()
              << " MODE " << target;

    if (!modes.empty())
        std::cout << " " << modes;
    if (!params.empty())
        std::cout << " " << params;

    std::cout << " ===\n";

    std::string raw = "MODE " + target;
    if (!modes.empty())
        raw += " " + modes;
    if (!params.empty())
        raw += " " + params;

    server.executeRoutine(client, raw);

    std::cout << "===========================================\n";
}
