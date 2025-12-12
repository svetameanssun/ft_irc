#include "Server.hpp"
#include "Client.hpp"
#include "CommandHandler.hpp"
#include "cmdtests.hpp"
#include <iostream>

int main()
{
    Server server(6667, "password");

    // Fake clients (5 users)
    Client alice(3, "localhost");
    Client bob(4, "localhost");
    Client carol(5, "localhost");
    Client dave(6, "localhost");
    Client eve(7, "localhost");

    std::cout << "\n========== USER REGISTRATION SUITE ==========\n";

    // All users correctly register
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
    //  JOIN COMMAND (simple, no edge cases)
    // ======================================================

    std::cout << "\n============== JOIN TESTS ==============\n";

    runTestJoin(server, &alice, "#room1", "");
    runTestJoin(server, &bob,   "#room1", "");
    runTestJoin(server, &carol, "#room2", "");
    runTestJoin(server, &dave,  "#room3", "");

    std::cout << "\n============== JOIN DONE ==============\n";


    // ======================================================
    //  PRIVMSG / NOTICE TESTS
    // ======================================================

    runTestPrivmsg(server, &alice, "Bob", "Hello Bob!");
    runTestNotice(server, &bob, "Alice", "Notice for Alice");

    runTestPrivmsg(server, &carol, "#room2", "Hello room2!");

    // ======================================================
    //  PART TESTS
    // ======================================================

    runTestPart(server, &alice, "#room1", "Goodbye room1");
    runTestPart(server, &bob, "#room1", "");

    // ======================================================
    //  QUIT TESTS
    // ======================================================

    runTestQuit(server, &carol, "See you!");
    runTestQuit(server, &eve, "");

    std::cout << "\n============== TEST SUITE END ==============\n";
    return 0;
}
