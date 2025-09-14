#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "CommandHandler.hpp"
#include <iostream>
#include <vector>

// === JOIN Test ===
void runTestJoin(CommandHandler& handler, Client* client,
                 const std::string& channel, const std::string& key = "") {
    std::cout << "\n=== TEST: " << client->getNick() << " JOIN " << channel << " ===\n";

    std::vector<std::string> args;
    args.push_back(channel);
    if (!key.empty())
        args.push_back(key);

    handler.execute(client, "JOIN", args);

    std::cout << "===========================================\n";
}

int main() {
    // Create server
    Server server(6667, "password");
    CommandHandler handler(server);

    // Fake clients
    Client alice(1, "localhost");
    alice.setNick("Alice");
    alice.setUser("aliceuser");

    Client bob(2, "localhost");
    bob.setNick("Bob");
    bob.setUser("bobuser");

    // Run JOIN tests
    runTestJoin(handler, &alice, "#42");
    runTestJoin(handler, &bob, "#42");

    return 0;
}
