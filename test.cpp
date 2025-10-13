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

    // ----------------------------------------------------------------
    // PASS tests
    // ----------------------------------------------------------------
    // Correct password before registration
    runTestPass(server, &alice, "password");     // ✅ should succeed
    // Wrong password
    runTestPass(server, &bob, "wrongpass");      // ❌ ERR_PASSWDMISMATCH
    // Already registered client tries PASS again
    runTestPass(server, &alice, "password");     // ❌ ERR_ALREADYREGISTRED
    // Missing parameter (simulate with empty string)
    runTestPass(server, &bob, "");               // ❌ ERR_NEEDMOREPARAMS

    // ----------------------------------------------------------------
    // NICK + USER tests
    // ----------------------------------------------------------------
    // Valid nick change
    runTestNick(server, &alice, "AliceNew");     // ✅ nick change
    // Duplicate nick
    runTestNick(server, &bob, "AliceNew");       // ❌ ERR_NICKNAMEINUSE
    // Empty nick
    runTestNick(server, &bob, "");               // ❌ ERR_NONICKNAMEGIVEN

    // Valid USER
    runTestUser(server, &bob, "bobuser2", "Bob Realname"); // ✅
    // Missing params
    runTestUser(server, &bob, "bobuser2", "");             // ❌ ERR_NEEDMOREPARAMS

    // ----------------------------------------------------------------
    // JOIN tests
    // ----------------------------------------------------------------
    runTestJoin(server, &alice, "#42");                  // ✅ join channel
    runTestJoin(server, &bob, "#42");                    // ✅ join channel
    runTestJoin(server, &bob, "");                       // ❌ ERR_NEEDMOREPARAMS
    runTestJoin(server, &bob, "InvalidChanName");        // ❌ could add validation error

    // ----------------------------------------------------------------
    // PRIVMSG tests
    // ----------------------------------------------------------------
    runTestPrivmsg(server, &alice, "#42", "Hello channel!"); // ✅ to channel
    runTestPrivmsg(server, &bob, "AliceNew", "Hello Alice!"); // ✅ to user
    runTestPrivmsg(server, &alice, "#doesnotexist", "Hi");    // ❌ ERR_NOSUCHCHANNEL
    runTestPrivmsg(server, &alice, "NoSuchNick", "Hi");       // ❌ ERR_NOSUCHNICK
    runTestPrivmsg(server, &alice, "#42", "");                // ❌ ERR_NEEDMOREPARAMS

    // ----------------------------------------------------------------
    // PART tests
    // ----------------------------------------------------------------
    runTestPart(server, &alice, "#42");            // ✅ leave channel
    runTestPart(server, &alice, "#42");            // ❌ ERR_NOTONCHANNEL
    runTestPart(server, &alice, "");               // ❌ ERR_NEEDMOREPARAMS

    // ----------------------------------------------------------------
    // QUIT tests
    // ----------------------------------------------------------------
    runTestQuit(server, &bob, "Goodbye!");         // ✅ broadcast quit
    runTestQuit(server, &bob, "");                 // ✅ quit with default msg

    // ----------------------------------------------------------------
    // PING / PONG tests
    // ----------------------------------------------------------------
    runTestPing(server, &alice, "12345");          // ✅ should reply with PONG
    runTestPing(server, &alice, "");               // ❌ ERR_NOORIGIN
    runTestPong(server, &alice, "12345");          // ✅ server logs PONG

    // ----------------------------------------------------------------
    // TOPIC tests
    // ----------------------------------------------------------------
    runTestTopic(server, &alice, "#42");                         // ✅ query topic
    runTestTopic(server, &alice, "#42", "New project topic");    // ✅ set topic
    runTestTopic(server, &bob, "#notjoined");                    // ❌ ERR_NOTONCHANNEL
    runTestTopic(server, &alice, "");                            // ❌ ERR_NEEDMOREPARAMS

    // ----------------------------------------------------------------
    // KICK tests
    // ----------------------------------------------------------------
    runTestKick(server, &alice, "#42", "Bob", "Breaking rules"); // ✅ kick Bob
    runTestKick(server, &alice, "#42", "Bob", "Again");          // ❌ ERR_USERNOTINCHANNEL
    runTestKick(server, &bob, "#42", "AliceNew");                // ❌ ERR_NOTONCHANNEL (Bob isn’t in)
    runTestKick(server, &alice, "#notfound", "Bob");             // ❌ ERR_NOSUCHCHANNEL
    runTestKick(server, &alice, "#42", "", "");                  // ❌ ERR_NEEDMOREPARAMS

    // ----------------------------------------------------------------
    // INVITE tests
    // ----------------------------------------------------------------
    runTestInvite(server, &alice, "Bob", "#42");       // ✅ invite Bob
    runTestInvite(server, &bob, "AliceNew", "#42");    // ❌ ERR_NOTONCHANNEL
    runTestInvite(server, &alice, "Ghost", "#42");     // ❌ ERR_NOSUCHNICK
    runTestInvite(server, &alice, "Bob", "#notfound"); // ❌ ERR_NOSUCHCHANNEL
    runTestInvite(server, &alice, "", "#42");          // ❌ ERR_NEEDMOREPARAMS

    return 0;
}
