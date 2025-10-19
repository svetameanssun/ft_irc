#include <iostream>
#include "Server.hpp"
#include "Client.hpp"
#include "cmdtests.hpp"

// === PASS Test ===
void runTestPass(Server &server, Client *client, const std::string &password)
{
    std::cout << "\n=== TEST: " << client->getNick() << " PASS " << password << " ===\n";

    std::string rawCommand = "PASS " + password;
    server.launchParcing(rawCommand);
    server.dispatchCommand(client, "PASS");
    server.deleteParserResult();

    std::cout << "===========================================\n";
}


// === NICK Test ===
void runTestNick(Server &server, Client *client, const std::string &newNick)
{
    std::cout << "\n=== TEST: " << client->getNick() << " NICK " << newNick << " ===\n";

    std::string rawCommand = "NICK " + newNick;
    server.launchParcing(rawCommand);
    server.dispatchCommand(client, "NICK");
    server.deleteParserResult();

    std::cout << "===========================================\n";
}


// === USER Test ===
void runTestUser(Server &server, Client *client,
                 const std::string &username, const std::string &realname)
{
    std::cout << "\n=== TEST: " << client->getNick() << " USER " << username
              << " " << realname << " ===\n";

    std::string rawCommand = "USER " + username + " " + realname;
    server.launchParcing(rawCommand);
    server.dispatchCommand(client, "USER");
    server.deleteParserResult();

    std::cout << "===========================================\n";
}


// === JOIN Test ===
void runTestJoin(Server &server, Client *client,
                 const std::string &channel, const std::string &key = "")
{
    std::cout << "\n=== TEST: " << client->getNick() << " JOIN " << channel << " ===\n";

    std::string rawCommand = "JOIN " + channel;
    if (!key.empty())
        rawCommand += " " + key;

    server.launchParcing(rawCommand);
    server.dispatchCommand(client, "JOIN");
    server.deleteParserResult();

    std::cout << "===========================================\n";
}
