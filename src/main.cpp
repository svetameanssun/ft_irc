#include <iostream>
#include "Server.hpp"
#include "Client.hpp"
#include "CommandHandler.hpp"
#include "cmdtests.hpp"

// ======================================================
// Utilities
// ======================================================
//
//void ensureClientRegistered(Server &server, Client *client)
//{
//    ClientManager &manager = server.getClientManager();
//    if (!manager.clientExists(client->getFd()))
//        manager.addClient(client);
//}

// ======================================================
// REGISTRATION TESTS
// ======================================================

void testRegistrationSuite(Server &server)
{
    Client alice(3, "localhost");
    Client bob(4, "localhost");
    Client carol(5, "localhost");
    Client dave(6, "localhost");
    Client eve(7, "localhost");

    std::cout << "\n========== REGISTRATION SUITE ==========\n";

    // ✔️ Correct registration
    runTestPass(server, &alice, "password");
    runTestNick(server, &alice, "Alice");
    runTestUser(server, &alice, "aliceUser", "Alice Real");

    // ✔️ Delayed registration
    runTestPass(server, &bob, "password");
    runTestNick(server, &bob, "Bob");
    runTestUser(server, &bob, "bobUser", "Bob Real");

    // ❌ NICK before PASS
    runTestNick(server, &carol, "Carol");

    // ❌ USER before PASS
    runTestUser(server, &carol, "carolUser", "Carol Real");

    // ❌ Wrong password
    runTestPass(server, &dave, "wrongpass");

    // ❌ Duplicate nick
    runTestNick(server, &eve, "Alice");

    // ❌ Empty nick
    runTestNick(server, &eve, "");

    // ❌ Empty username
    runTestUser(server, &eve, "", "Real Name");

    // ❌ Re-registration attempt
    runTestPass(server, &alice, "password");
    runTestNick(server, &alice, "NewAlice");
    runTestUser(server, &alice, "newUser", "New Real");

    std::cout << "\n========== REGISTRATION SUITE END ==========\n";
}

// ======================================================
// JOIN EDGE CASES
// ======================================================

void testJoinEdgeCases(Server &server)
{
    Client alice(10, "localhost");
    Client bob(11, "localhost");
    Client carol(12, "localhost");
    Client dave(13, "localhost");
    Client eve(14, "localhost");

    // Proper registration
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

    std::cout << "\n========== JOIN EDGE CASES ==========\n";

    // ❌ Bad channel mask
    runTestJoin(server, &alice, "roomNoHash", "");

    // ❌ Key mismatch
    server.getChannelManager().addChannel("#locked");
    server.getChannelManager().findChannel("#locked")->setKey("1234");
    server.getChannelManager().findChannel("#locked")->setKMode(true);

    runTestJoin(server, &alice, "#locked", "");

    // ❌ Invite only
    Channel *vip = server.getChannelManager().addChannel("#vip");
    vip->setInviteOnly(true);

    runTestJoin(server, &bob, "#vip", "");

    // ❌ Channel full
    Channel *tiny = server.getChannelManager().addChannel("#tiny");
    tiny->setUserLimit(1);

    runTestJoin(server, &carol, "#tiny", "");
    runTestJoin(server, &dave, "#tiny", "");

    // ✔️ JOIN 0 (leave all)
    runTestJoin(server, &eve, "0", "");

    std::cout << "\n========== JOIN EDGE CASES END ==========\n";
}

// ======================================================
// PRIVMSG EDGE CASES
// ======================================================

void testPrivmsgEdgeCases(Server &server)
{
    Client alice(20, "localhost");
    Client bob(21, "localhost");

    runTestPass(server, &alice, "password");
    runTestNick(server, &alice, "Alice");
    runTestUser(server, &alice, "aliceUser", "Alice Real");

    runTestPass(server, &bob, "password");
    runTestNick(server, &bob, "Bob");
    runTestUser(server, &bob, "bobUser", "Bob Real");

    runTestJoin(server, &alice, "#room1", "");

    std::cout << "\n========== PRIVMSG EDGE CASES ==========\n";

    runTestTopic(server, &alice, "#vip", "");
    // ❌ No such nick
    runTestPrivmsg(server, &alice, "Ghost", "Hello?");

    // ❌ Not on channel
    runTestPrivmsg(server, &bob, "#room1", "Hello");

    // ❌ No such channel
    runTestPrivmsg(server, &alice, "#doesnotexist", "Hello");

    // ======================================================
//  NOTICE COMMAND TESTS
// ======================================================

    std::cout << "\n============== NOTICE TESTS ==============\n";

    // 1️⃣ NOTICE to a user
    runTestNotice(server, &alice, "Bob", "Hello Bob (notice)");

    // 2️⃣ NOTICE to a channel
    runTestNotice(server, &bob, "#room1", "Notice to room1");

    // 3️⃣ NOTICE to non-existing user (MUST SILENTLY FAIL)
    runTestNotice(server, &alice, "GhostUser", "You should not see this");

    // 4️⃣ NOTICE to non-existing channel (MUST SILENTLY FAIL)
    runTestNotice(server, &alice, "#ghost", "This channel does not exist");

    // 6️⃣ NOTICE with empty message (parser may block; OK either way)
    runTestNotice(server, &alice, "Bob", "");

    // 7️⃣ NOTICE to self (allowed)
    runTestNotice(server, &alice, "Alice", "Talking to myself");

    std::cout << "\n============== NOTICE TESTS END ==============\n";

        // 1️⃣ NOTICE to a user
    runTestPrivmsg(server, &alice, "Bob", "Hello Bob (notice)");
    
    // 2️⃣ NOTICE to a channel
    runTestPrivmsg(server, &bob, "#room1", "Notice to room1");
    
    // 3️⃣ NOTICE to non-existing user (MUST SILENTLY FAIL)
    runTestPrivmsg(server, &alice, "GhostUser", "You should not see this");
    
    // 4️⃣ NOTICE to non-existing channel (MUST SILENTLY FAIL)
    runTestPrivmsg(server, &alice, "#ghost", "This channel does not exist");
    
    // 6️⃣ NOTICE with empty message (parser may block; OK either way)
    runTestPrivmsg(server, &alice, "Bob", "");
    
    // 7️⃣ NOTICE to self (allowed)
    runTestPrivmsg(server, &alice, "Alice", "Talking to myself");


    std::cout << "\n========== PRIVMSG EDGE CASES END ==========\n";
}

// ======================================================
// QUIT EDGE CASES
// ======================================================

void testQuitEdgeCases(Server &server)
{
    Client carol(30, "localhost");
    Client eve(31, "localhost");

    runTestPass(server, &carol, "password");
    runTestNick(server, &carol, "Carol");
    runTestUser(server, &carol, "carolUser", "Carol Real");

    runTestPass(server, &eve, "password");
    runTestNick(server, &eve, "Eve");
    runTestUser(server, &eve, "eveUser", "Eve Real");

    runTestJoin(server, &carol, "#roomQuit", "");

    std::cout << "\n========== QUIT EDGE CASES ==========\n";

    // ✔️ QUIT with message
    runTestQuit(server, &carol, "See you!");

    // ✔️ QUIT without message
    runTestQuit(server, &eve, "");

    // ❌ QUIT unregistered client
    Client ghost(99, "localhost");
    runTestQuit(server, &ghost, "Bye");

    
    std::cout << "\n========== QUIT EDGE CASES END ==========\n";
}

// ======================================================
// MAIN
// ======================================================

int main()
{
    Server server(6667, "password");

    testRegistrationSuite(server);
    testJoinEdgeCases(server);
    testPrivmsgEdgeCases(server);
    testQuitEdgeCases(server);

    std::cout << "\n========== ALL TESTS COMPLETED ==========\n";
    return 0;
}
