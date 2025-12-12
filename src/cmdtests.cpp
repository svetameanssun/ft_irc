#include <iostream>
#include "Server.hpp"
#include "Client.hpp"
#include "cmdtests.hpp"

// Utility: ensure client exists in the registry
//TODO: When networking implemented, we need to move this to its proper location
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
    server.executeRoutine(client, rawCommand, "PASS");

    std::cout << "===========================================\n";
}

// === NICK Test ===
void runTestNick(Server &server, Client *client, const std::string &newNick)
{
    ensureClientRegistered(server, client);

    std::cout << "\n=== TEST: " << client->getNick() << " NICK " << newNick << " ===\n";

    std::string rawCommand = "NICK " + newNick;
    server.executeRoutine(client, rawCommand, "NICK");

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
    //TODO: [LANA]: It seems like the parser does not get correctly the real name
    std::string rawCommand = "USER " + username + " 0 * :" + realname;

    server.executeRoutine(client, rawCommand, "USER");

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

    server.executeRoutine(client, rawCommand, "JOIN");

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
    server.executeRoutine(sender, raw, "PRIVMSG");

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
    server.executeRoutine(sender, raw, "NOTICE");

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

    server.executeRoutine(client, raw, "PART");

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

    server.executeRoutine(client, raw, "QUIT");

    std::cout << "===========================================\n";
}
