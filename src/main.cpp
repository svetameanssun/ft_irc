#include "Server.hpp"
#include "Client.hpp"
#include "CommandHandler.hpp"
#include "cmdtests.hpp"
#include <iostream>

int main()
{
    Server server(6667, "password");

    // Fake clients
    Client alice(3, "localhost");
    Client bob(4, "localhost");
    Client carol(5, "localhost");
    Client dave(6, "localhost");
    Client eve(7, "localhost");

    std::cout << "\n========== CLEAN USER REGISTRATION SUITE ==========\n";

    // 1️⃣ Clean correct registrations
    runTestPass(server, &alice, "password");
    runTestNick(server, &alice, "Alice");
    runTestUser(server, &alice, "aliceUser", "Alice Real");

    runTestPass(server, &bob, "password");
    runTestNick(server, &bob, "Bob");
    runTestUser(server, &bob, "bobUser", "Bob Real");

    runTestPass(server, &carol, "password");
    runTestNick(server, &carol, "Carol");
    runTestUser(server, &carol, "carolUser", "Carol Real");

    runTestPass(server, &dave, "password");
    runTestNick(server, &dave, "Dave");
    runTestUser(server, &dave, "daveUser", "Dave Real");

    runTestPass(server, &eve, "password");
    runTestNick(server, &eve, "Eve");
    runTestUser(server, &eve, "eveUser", "Eve Real");

    std::cout << "\n============== REGISTRATION DONE ==============\n";


    // ======================================================
    //                CLEAN JOIN TESTS (no edge cases)
    // ======================================================

    std::cout << "\n============== JOIN COMMAND TESTS ==============\n";

    // Basic channel creation + joining
    runTestJoin(server, &alice, "#room1", "");
    runTestJoin(server, &bob,   "#room1", "");

    runTestJoin(server, &carol, "#room2", "");
    runTestJoin(server, &dave,  "#room3", "");

    // Channel with key (only successful case)
    server.getChannelManager().addChannel("#locked");
    server.getChannelManager().findChannel("#locked")->setKey("1234");
    server.getChannelManager().findChannel("#locked")->setKMode(true);

    runTestJoin(server, &eve, "#locked", "1234");

    std::cout << "\n============== JOIN TESTS END ==============\n";


    // ======================================================
    //                PRIVMSG TESTS
    // ======================================================

    std::cout << "\n============== PRIVMSG TESTS ==============\n";

    // User-to-user messaging
    runTestPrivmsg(server, &alice, "Bob", "Hello Bob!");
    runTestPrivmsg(server, &bob, "Alice", "Hey Alice!");

    // Channel messaging
    runTestPrivmsg(server, &carol, "#room2", "Hello everyone in room2");
    runTestPrivmsg(server, &dave, "#room3", "Any news?");

    std::cout << "\n============== PRIVMSG TESTS END ==============\n";


    // ======================================================
    //                NOTICE TESTS (clean)
    // ======================================================

    std::cout << "\n============== NOTICE TESTS ==============\n";

    // User notices
    runTestNotice(server, &eve, "Alice", "This is a NOTICE");
    runTestNotice(server, &alice, "Bob", "Remember to update configs.");

    // Channel notices
    runTestNotice(server, &carol, "#room2", "System message to room2");
    runTestNotice(server, &dave, "#room3", "Maintenance at midnight.");

    std::cout << "\n============== NOTICE TESTS END ==============\n";


    return 0;
}
