#include "Server.hpp"
#include "Client.hpp"
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

    std::cout << "\n========== USER REGISTRATION TEST SUITE ==========\n";

    // ======================================================
    // 1️⃣ Alice registers correctly (ideal workflow)
    // ======================================================
    std::cout << "\n--- Alice Correct Registration Sequence ---\n";
    runTestPass(server, &alice, "password");                 // PASS OK
    runTestNick(server, &alice, "Alice");                    // NICK OK
    runTestUser(server, &alice, "aliceUser", "Alice Real");  // USER OK

    // ======================================================
    // 2️⃣ Bob attempts incorrect flows before succeeding
    // ======================================================
    std::cout << "\n--- Bob Incorrect Sequence + Fixes ---\n";

    runTestNick(server, &bob, "Bob");                       // ❌ NICK before PASS
    runTestUser(server, &bob, "bobUser", "Bob Real");       // ❌ USER before PASS
    runTestPass(server, &bob, "wrongpass");                 // ❌ Wrong PASS
    runTestPass(server, &bob, "password");                  // PASS OK
    runTestNick(server, &bob, "Alice");                     // ❌ Nick already in use
    runTestNick(server, &bob, "Bob");                       // NICK OK
    runTestUser(server, &bob, "bobUser", "Bob Real");       // USER OK

    // ======================================================
    // 3️⃣ Eve tries malformed and edge cases
    // ======================================================
    std::cout << "\n--- Eve Malformed Registration Attempts ---\n";

    runTestUser(server, &eve, "eveUser", "Eve Real");       // ❌ USER before PASS
    runTestNick(server, &eve, "Eve");                       // ❌ NICK before PASS
    runTestPass(server, &eve, "password");                  // PASS OK
    runTestUser(server, &eve, "", "Name");                  // ❌ Missing username
    runTestNick(server, &eve, "");                          // ❌ Missing nick
    runTestNick(server, &eve, "Bob");                       // ❌ Nick in use
    runTestNick(server, &eve, "Eve");                       // NICK OK
    runTestUser(server, &eve, "eveUser", "Eve Real");       // USER OK

    // ======================================================
    // 4️⃣ Alice attempts re-registration
    // ======================================================
    std::cout << "\n--- Alice Attempts to Re-register ---\n";

    runTestPass(server, &alice, "password");                // ❌ ERR_ALREADYREGISTRED
    runTestNick(server, &alice, "Alice");                   // OK (simple rename)
    runTestUser(server, &alice, "aliceUser", "Alice Real"); // OK (already set)

    std::cout << "\n============== REGISTRATION TESTS END ==============\n";
    return 0;
}
