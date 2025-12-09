#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "CommandHandler.hpp"
#include "cmdtests.hpp"
#include <iostream>

int main()
{
    Server server(6667, "password");

    // Fake clients
    Client alice(1, "localhost");
    Client bob(2, "localhost");
    Client eve(3, "localhost");

    std::cout << "\n========== MIXED WORKFLOW TEST SUITE ==========\n";

    // ============================
    // 1️⃣ Alice registers correctly
    // ============================
    std::cout << "\n--- Alice Full Registration Workflow ---\n";
    runTestPass(server, &alice, "password");          // ✅ PASS accepted
    runTestNick(server, &alice, "Alice");             // ✅ NICK ok
    runTestUser(server, &alice, "aliceUser", "Alice"); // ✅ USER ok
    runTestJoin(server, &alice, "#coolkids", "");     // ✅ join first channel

    // ============================
    // 2️⃣ Bob tries wrong order / wrong password
    // ============================
    std::cout << "\n--- Bob Wrong Sequence and Corrections ---\n";
    runTestNick(server, &bob, "Bob");                 // ❌ should wait PASS first
    runTestUser(server, &bob, "bobUser", "Bob");      // ❌ still not allowed
    runTestPass(server, &bob, "wrongpass");           // ❌ incorrect password
    runTestPass(server, &bob, "password");            // ✅ PASS accepted
    runTestNick(server, &bob, "Alice");               // ❌ already in use
    runTestNick(server, &bob, "Bob");                 // ✅ ok
    runTestUser(server, &bob, "bobUser", "Bob");      // ✅ registered
    runTestJoin(server, &bob, "#coolkids", "");       // ✅ joins Alice

    // ============================
    // 3️⃣ Eve tries dangerous + malformed cmds
    // ============================
    std::cout << "\n--- Eve Malformed Input Tests ---\n";
    runTestJoin(server, &eve, "#hackers", "");        // ❌ no PASS/NICK/USER
    runTestPass(server, &eve, "password");            // ✅ PASS ok
    runTestUser(server, &eve, "", "RealEve");         // ❌ missing username
    runTestNick(server, &eve, "");                    // ❌ missing nick
    runTestNick(server, &eve, "Bob");                 // ❌ in use
    runTestNick(server, &eve, "Eve");                 // ✅ ok
    runTestUser(server, &eve, "eveUser", "Eve");      // ✅ registered
    runTestJoin(server, &eve, "", "");                // ❌ missing params
    runTestJoin(server, &eve, "@@@@", "");            // ❌ invalid format (if implemented)
    runTestJoin(server, &eve, "#coolkids", "");       // ✅ joins channel

    // ============================
    // 4️⃣ Alice tries a duplicate process
    // ============================
    std::cout << "\n--- Alice Attempts to Re-register ---\n";
    runTestPass(server, &alice, "password");          // ❌ ERR_ALREADYREGISTRED
    runTestNick(server, &alice, "Alice");             // ✅ just renaming (same)
    runTestUser(server, &alice, "aliceUser", "Alice");// ✅ still ok

    std::cout << "\n============== TEST SUITE END ==============\n";
    return 0;
}
