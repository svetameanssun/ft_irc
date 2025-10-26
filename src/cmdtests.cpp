#include <iostream>
#include "Server.hpp"
#include "Client.hpp"
#include "cmdtests.hpp"

// === PASS Test ===
void runTestPass(Server &server, Client *client, const std::string &password)
{
    std::cout << "\n=== TEST: " << client->getNick() << " PASS " << password << " ===\n";

    std::string rawCommand = "PASS " + password;
    server.executeRoutine(client, rawCommand, "PASS");

    std::cout << "===========================================\n";
}


// === NICK Test ===
void runTestNick(Server &server, Client *client, const std::string &newNick)
{
    std::cout << "\n=== TEST: " << client->getNick() << " NICK " << newNick << " ===\n";

    std::string rawCommand = "NICK " + newNick;
    server.executeRoutine(client, rawCommand, "NICK");

    std::cout << "===========================================\n";
}


// === USER Test ===
void runTestUser(Server &server, Client *client,
                 const std::string &username, const std::string &realname)
{
    std::cout << "\n=== TEST: " << client->getNick() << " USER " << username
              << " " << realname << " ===\n";

    std::string rawCommand = "USER " + username + " " + realname;
    server.executeRoutine(client, rawCommand, "USER");

    std::cout << "===========================================\n";
}


// === JOIN Test ===
void runTestJoin(Server &server, Client *client,
                 const std::string &channel, const std::string &whatever)
{
    const std::string &key = "";
    std::cout << "\n=== TEST: " << client->getNick() << " JOIN " << channel << " ===\n";

    std::string rawCommand = "JOIN " + channel + whatever;
    server.executeRoutine(client, rawCommand, "JOIN");

    std::cout << "===========================================\n";
}
