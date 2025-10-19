#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "CommandHandler.hpp"
#include "cmdtests.hpp"
#include <iostream>
#include <vector>

int main()
{
    // Create server with a password requirement
    Server server(6667, "password");

    // Fake clients
    Client alice(1, "localhost");
    alice.setNick("Alice");     // (in real IRC, PASS/NICK/USER come before)
    alice.setUser("aliceuser");

    Client bob(2, "localhost");
    bob.setNick("Bob");
    bob.setUser("bobuser");

    // =====================================================
    // PASS COMMAND TESTS
    // =====================================================
    std::cout << "\n================ PASS TESTS ================\n";
    runTestPass(server, &alice, "password");   // ✅ correct password
    runTestPass(server, &bob, "wrongpass");    // ❌ ERR_PASSWDMISMATCH
    runTestPass(server, &alice, "password");   // ❌ ERR_ALREADYREGISTRED
    runTestPass(server, &bob, "");             // ❌ ERR_NEEDMOREPARAMS

    // =====================================================
    // NICK COMMAND TESTS
    // =====================================================
    std::cout << "\n================ NICK TESTS ================\n";
    runTestNick(server, &alice, "AliceNew");   // ✅ nick change
    runTestNick(server, &bob, "AliceNew");     // ❌ ERR_NICKNAMEINUSE
    runTestNick(server, &bob, "");             // ❌ ERR_NONICKNAMEGIVEN

    // =====================================================
    // USER COMMAND TESTS
    // =====================================================
    std::cout << "\n================ USER TESTS ================\n";
    runTestUser(server, &bob, "bobuser2", "Bob Realname"); // ✅
    runTestUser(server, &bob, "bobuser2", "");             // ❌ ERR_NEEDMOREPARAMS

    // =====================================================
    // JOIN COMMAND TESTS
    // =====================================================
    std::cout << "\n================ JOIN TESTS ================\n";
    runTestJoin(server, &alice, "#42", "");         // ✅ create & join channel
    runTestJoin(server, &bob, "#42", "");           // ✅ join existing channel
    runTestJoin(server, &bob, "", "");              // ❌ ERR_NEEDMOREPARAMS
    runTestJoin(server, &bob, "InvalidChanName", ""); // ❌ invalid format

    // =====================================================
    // FUTURE COMMANDS (commented for now)
    // =====================================================
    /*
    // PRIVMSG TESTS
    runTestPrivmsg(server, &alice, "#42", "Hello channel!");
    runTestPrivmsg(server, &bob, "AliceNew", "Hello Alice!");

    // PART TESTS
    runTestPart(server, &alice, "#42");

    // QUIT TESTS
    runTestQuit(server, &bob, "Goodbye!");

    // PING / PONG TESTS
    runTestPing(server, &alice, "12345");
    runTestPong(server, &alice, "12345");

    // TOPIC TESTS
    runTestTopic(server, &alice, "#42");
    runTestTopic(server, &alice, "#42", "New topic");

    // KICK TESTS
    runTestKick(server, &alice, "#42", "Bob", "Bye Bob!");

    // INVITE TESTS
    runTestInvite(server, &alice, "Bob", "#42");
    */

    std::cout << "\n========= TEST SUITE FINISHED =========\n";
    return 0;
}
