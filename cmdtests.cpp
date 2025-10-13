#include "Client.hpp"
#include "Server.hpp"
#include <iostream>

void runTestPass(Server &server, Client *client, const std::string &password)
{
    std::cout << "\n=== TEST: " << client->getNick()
              << " PASS " << password << " ===\n";

    std::vector<std::string> args;
    args.push_back(password);

    server.dispatchCommand(client, "PASS", args);

    std::cout << "===========================================\n";
}


// === JOIN Test ===
void runTestJoin(Server &server, Client *client,
                 const std::string &channel, const std::string &key = "")
{
    std::cout << "\n=== TEST: " << client->getNick() << " JOIN " << channel << " ===\n";

    std::vector<std::string> args;
    args.push_back(channel);
    if (!key.empty())
        args.push_back(key);

    server.dispatchCommand(client, "JOIN", args);

    std::cout << "===========================================\n";
}

//TODO: Implement test commands
void runTestNick(Server &server, Client *client, const std::string &newNick)
{
    std::cout << "\n=== TEST: " << client->getNick() << " NICK " << newNick << " ===\n";

    std::vector<std::string> args;
    args.push_back(newNick);

    server.dispatchCommand(client, "NICK", args);

    std::cout << "===========================================\n";
}

void runTestUser(Server &server, Client *client,
                 const std::string &username, const std::string &realname)
{
    std::cout << "\n=== TEST: " << client->getNick() << " USER " << username << " " << realname << " ===\n";

    std::vector<std::string> args;
    args.push_back(username);
    args.push_back(realname);

    server.dispatchCommand(client, "USER", args);

    std::cout << "===========================================\n";
}


void runTestPart(Server &server, Client *client, const std::string &channel)
{
    std::cout << "\n=== TEST: " << client->getNick() << " PART " << channel << " ===\n";

    std::vector<std::string> args;
    args.push_back(channel);

    server.dispatchCommand(client, "PART", args);

    std::cout << "===========================================\n";
}

void runTestPrivmsg(Server &server, Client *client,
                    const std::string &target, const std::string &msg)
{
    std::cout << "\n=== TEST: " << client->getNick() << " PRIVMSG " << target << " ===\n";

    std::vector<std::string> args;
    args.push_back(target);
    args.push_back(msg);

    server.dispatchCommand(client, "PRIVMSG", args);

    std::cout << "===========================================\n";
}


void runTestQuit(Server &server, Client *client, const std::string &msg = "Leaving")
{
    std::cout << "\n=== TEST: " << client->getNick() << " QUIT " << msg << " ===\n";

    std::vector<std::string> args;
    if (!msg.empty())
        args.push_back(msg);

    server.dispatchCommand(client, "QUIT", args);

    std::cout << "===========================================\n";
}

void runTestPing(Server &server, Client *client, const std::string &token)
{
    std::cout << "\n=== TEST: " << client->getNick() << " PING " << token << " ===\n";

    std::vector<std::string> args;
    args.push_back(token);

    server.dispatchCommand(client, "PING", args);

    std::cout << "===========================================\n";
}

void runTestPong(Server &server, Client *client, const std::string &token)
{
    std::cout << "\n=== TEST: " << client->getNick() << " PONG " << token << " ===\n";

    std::vector<std::string> args;
    args.push_back(token);

    server.dispatchCommand(client, "PONG", args);

    std::cout << "===========================================\n";
}


void runTestMode(Server &server, Client *client)
{
    std::vector<std::string> args;
    server.dispatchCommand(client, "MODE", args);
}

void runTestTopic(Server &server, Client *client,
                  const std::string &channel,
                  const std::string &topic = "")
{
    std::cout << "\n=== TEST: " << client->getNick()
              << " TOPIC " << channel
              << (topic.empty() ? "" : " :" + topic) << " ===\n";

    std::vector<std::string> args;
    args.push_back(channel);
    if (!topic.empty())
        args.push_back(topic);

    server.dispatchCommand(client, "TOPIC", args);

    std::cout << "===========================================\n";
}


void runTestKick(Server &server, Client *client,
                 const std::string &channel,
                 const std::string &target,
                 const std::string &reason = "Kicked")
{
    std::cout << "\n=== TEST: " << client->getNick()
              << " KICK " << channel << " " << target
              << " (" << reason << ") ===\n";

    std::vector<std::string> args;
    args.push_back(channel);
    args.push_back(target);
    if (!reason.empty())
        args.push_back(reason);

    server.dispatchCommand(client, "KICK", args);

    std::cout << "===========================================\n";
}


void runTestInvite(Server &server, Client *client,
                   const std::string &target,
                   const std::string &channel)
{
    std::cout << "\n=== TEST: " << client->getNick()
              << " INVITE " << target << " " << channel << " ===\n";

    std::vector<std::string> args;
    args.push_back(target);
    args.push_back(channel);

    server.dispatchCommand(client, "INVITE", args);

    std::cout << "===========================================\n";
}
