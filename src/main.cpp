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

    std::cout << "\n========== CLEAN USER REGISTRATION SUITE ==========\n";

    // ======================================================
    // 1️⃣ Correct Registration for all clients
    // ======================================================
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
    //                JOIN COMMAND TESTS
    // ======================================================

    std::cout << "\n============== JOIN COMMAND TESTS ==============\n";

    // 1️⃣ Basic JOIN (create channels)
    runTestJoin(server, &alice, "#room1", "");
    runTestJoin(server, &bob,   "#room1", "");   // join existing
    runTestJoin(server, &carol, "#room2", "");
    runTestJoin(server, &dave,  "#room3", "");

    // 2️⃣ JOIN with bad format
    runTestJoin(server, &eve, "roomNoHash", "");   // ERR_BADCHANMASK
    runTestJoin(server, &eve, "", "");             // ERR_NEEDMOREPARAMS

    // 3️⃣ JOIN multiple channels (RFC allows comma lists — your parser already supports it)
    runTestJoin(server, &carol, "#a,#b,#c", "");

    // 4️⃣ JOIN with key (channel already has a key)
    // Let's manually set channel #locked to have key "1234"
    server.getChannelManager().addChannel("#locked");
    server.getChannelManager().findChannel("#locked")->setKey("1234");
    server.getChannelManager().findChannel("#locked")->setKMode(true);


    runTestJoin(server, &alice, "#locked", "");        // ERR_BADCHANNELKEY
    runTestJoin(server, &alice, "#locked", "1234");    // OK

    // 5️⃣ Invite-only channel test
    Channel *vip = server.getChannelManager().addChannel("#vip");
    server.getChannelManager().findChannel("#vip")->setInviteOnly(true);

    runTestJoin(server, &bob, "#vip", "");             // ERR_INVITEONLYCHAN
    vip->invite(eve.getFd());
    runTestJoin(server, &eve, "#vip", "");             // OK (invited)

    // 6️⃣ Channel full
    Channel *tiny = server.getChannelManager().addChannel("#tiny");
    tiny->setUserLimit(1);  // only 1 member allowed

    runTestJoin(server, &carol, "#tiny", "");          // OK
    runTestJoin(server, &dave,  "#tiny", "");          // ERR_CHANNELISFULL

    // 7️⃣ JOIN 0 (leave all channels)
    runTestJoin(server, &alice, "0", "");              // leave all joined

    // 8️⃣ Joining again a channel you’re already inside
    runTestJoin(server, &bob, "#room1", "");           // should just resend topic+names

    std::cout << "\n============== JOIN TESTS END ==============\n";

    return 0;
}
