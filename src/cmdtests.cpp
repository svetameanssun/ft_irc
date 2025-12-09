#include <iostream>
#include "Server.hpp"
#include "Client.hpp"
#include "cmdtests.hpp"

// Utility: ensure client exists in the registry
void ensureClientRegistered(Server &server, Client *client)
{
    ClientManager &manager = server.getClientManager();
    int fd = client->getFd();

    if (!manager.clientExists(fd))
    {
        std::cout << "[INFO] Client not found in registry. Registering client with fd " << fd << "...\n";
        manager.addClient(fd);
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
//TODO: Test USER string format missing something; it always gives an error
// === USER Test ===
void runTestUser(Server &server, Client *client,
                 const std::string &username, const std::string &realname)
{
    ensureClientRegistered(server, client);

    std::cout << "\n=== TEST: " << client->getNick() << " USER " << username
              << " " << realname << " ===\n";

    // Proper IRC syntax: USER <username> 0 * :<realname>
    std::string rawCommand = "USER " + username + " 0 * :" + realname;

    server.executeRoutine(client, rawCommand, "USER");

    std::cout << "===========================================\n";
}


// === JOIN Test ===
void runTestJoin(Server &server, Client *client,
                 const std::string &channel, const std::string &whatever)
{
    ensureClientRegistered(server, client);

    const std::string &key = "";
    std::cout << "\n=== TEST: " << client->getNick() << " JOIN " << channel << " ===\n";

    std::string rawCommand = "JOIN " + channel + whatever;
    server.executeRoutine(client, rawCommand, "JOIN");

    std::cout << "===========================================\n";
}
