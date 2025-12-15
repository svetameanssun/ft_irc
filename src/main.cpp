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
    //  JOIN TESTS (simple, valid cases)
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

    //runTestPart(server, &alice, "#room1", "Goodbye room1");
    //runTestPart(server, &bob, "#room1", "");


    // ======================================================
    //  KICK TESTS
    // ======================================================

    std::cout << "\n============== KICK TESTS ==============\n";

    // Alice kicks Bob from #room1 (Alice created it, so she is op)
    //runTestKick(server, &alice, "#room1", "Bob", "Spamming");

    // Carol creates a channel and kicks Dave
    runTestJoin(server, &carol, "#mods", "");
    runTestJoin(server, &dave, "#mods", "");
    runTestKick(server, &carol, "#mods", "Dave", "Rule violation");

    std::cout << "\n============== KICK DONE ==============\n";

    // ======================================================
    //  INVITE TESTS
    // ======================================================

    std::cout << "\n============== INVITE TESTS ==============\n";

    // Create invite-only channel
    //Channel *vip = server.getChannelManager().addChannel("#vip");

    // Alice joins and becomes operator
    runTestJoin(server, &alice, "#vip", "");
    server.getChannelManager().findChannel("#vip")->setInviteOnly(true);


    // Bob tries to join without invite
    runTestJoin(server, &bob, "#vip", "");      // ERR_INVITEONLYCHAN

    // Alice invites Bob
    runTestInvite(server, &alice, "Bob", "#vip");

    // Bob can now join
    runTestJoin(server, &bob, "#vip", "");
    runTestInvite(server, &alice, "Bob", "#vip");   // Already invited
    
    std::cout << "\n============== WRONG INVITE TESTS ==============\n";

    runTestInvite(server, &bob, "Carol", "#vip");  // ERR_CHANOPRIVSNEEDED
    runTestInvite(server, &alice, "Ghost", "#vip");// ERR_NOSUCHNICK
    runTestInvite(server, &alice, "Bob", "#nope"); // ERR_NOSUCHCHANNEL


    std::cout << "\n============== INVITE DONE ==============\n";

    // ======================================================
    //  TOPIC COMMAND TESTS
    // ======================================================

    std::cout << "\n============== TOPIC BASIC TESTS ==============\n";

    // Alice sets topic
    runTestTopic(server, &alice, "#room1", "Welcome to room1");

    // Bob queries topic
    runTestTopic(server, &bob, "#room1", "");

    // Carol sets topic in her own channel
    runTestTopic(server, &carol, "#room2", "Room2 discussion");

    // Carol queries again
    runTestTopic(server, &carol, "#room2", "");


    // ======================================================
    //  TOPIC OVERWRITE (NO +t MODE)
    // ======================================================

    std::cout << "\n============== TOPIC OVERWRITE TESTS ==============\n";

    // Bob overwrites topic (allowed when +t not set)
    runTestTopic(server, &bob, "#room1", "New topic by Bob");

    // Alice queries to confirm update
    runTestTopic(server, &alice, "#room1", "");


    // ======================================================
    //  TOPIC +t (TOPIC PROTECTED)
    // ======================================================

    std::cout << "\n============== TOPIC +t MODE TESTS ==============\n";

    Channel *room1 = server.getChannelManager().findChannel("#room1");
    room1->setTMode(true);   // +t

    // Non-operator tries to change topic
    runTestTopic(server, &bob, "#room1", "Bob tries to change topic");

    // Operator changes topic
    runTestTopic(server, &alice, "#room1", "Operator topic change");

    // Bob queries topic
    runTestTopic(server, &bob, "#room1", "");


    // ======================================================
    //  TOPIC CLEARING
    // ======================================================

    std::cout << "\n============== TOPIC CLEAR TEST ==============\n";

    // Alice clears topic
    runTestTopic(server, &alice, "#room1", "");

    // Bob queries -> no topic
    runTestTopic(server, &bob, "#room1", "");


    // ======================================================
    //  TOPIC NOT-ON-CHANNEL
    // ======================================================

    std::cout << "\n============== TOPIC NOT-ON-CHANNEL TESTS ==============\n";

    // Eve is not in #room1
    runTestTopic(server, &eve, "#room1", "");
    runTestTopic(server, &eve, "#room1", "Trying to set topic");


    // ======================================================
    //  TOPIC INVALID CHANNEL
    // ======================================================

    std::cout << "\n============== TOPIC INVALID CHANNEL TESTS ==============\n";

    // Channel does not exist
    runTestTopic(server, &alice, "#ghost", "");
    runTestTopic(server, &alice, "#ghost", "Hello?");

    // ======================================================
    //  MODE COMMAND TESTS
    // ======================================================

    std::cout << "\n============== MODE TESTS ==============\n";

    // Precondition: Alice and Bob are in #room1
    // Alice is channel operator (creator)

    // 1️⃣ Query channel modes
    runTestMode(server, &alice, "#room1", "", "");

    // 2️⃣ Set invite-only (+i)
    runTestMode(server, &alice, "#room1", "+i", "");

    // 3️⃣ Remove invite-only (-i)
    runTestMode(server, &alice, "#room1", "-i", "");

    // 4️⃣ Set topic lock (+t)
    runTestMode(server, &alice, "#room1", "+t", "");

    // 5️⃣ Set channel key (+k)
    runTestMode(server, &alice, "#room1", "+k", "secret");

    // 6️⃣ Remove channel key (-k)
    runTestMode(server, &alice, "#room1", "-k", "");

    // 7️⃣ Set user limit (+l)
    runTestMode(server, &alice, "#room1", "+l", "2");

    // 8️⃣ Remove user limit (-l)
    runTestMode(server, &alice, "#room1", "-l", "");

    // 9️⃣ Promote Bob to operator (+o)
    runTestMode(server, &alice, "#room1", "+o", "Bob");

    // 🔟 Demote Bob from operator (-o)
    runTestMode(server, &alice, "#room1", "-o", "Bob");

    // 1️⃣1️⃣ Bob tries to set a mode without privileges (should fail)
    runTestMode(server, &bob, "#room1", "+i", "");

    // 1️⃣2️⃣ User MODE query (Bob querying his own modes)
    runTestMode(server, &bob, "Bob", "", "");

    // 1️⃣3️⃣ User tries to give himself +o (should fail or ignore)
    runTestMode(server, &bob, "Bob", "+o", "");

    std::cout << "\n============== MODE TESTS END ==============\n";

    std::cout << "\n============== TEST SUITE END ==============\n";
    return 0;
}
