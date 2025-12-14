
#pragma once

void runTestPass(Server &server, Client *client, const std::string &password);

void runTestJoin(Server &server, Client *client,
                 const std::string &channel, const std::string &whatever);

void runTestNick(Server &server, Client *client, const std::string &newNick);
void runTestUser(Server &server, Client *client,
                 const std::string &username, const std::string &realname);
void runTestPrivmsg(Server &server, Client *client,
                    const std::string &target, const std::string &msg);
void runTestNotice(Server &server, Client *sender,
                   const std::string &target, const std::string &message);
void runTestPart(Server &server, Client *client,
                 const std::string &channels,
                 const std::string &comment);
void runTestQuit(Server &server, Client *client, const std::string &message);
void runTestPing(Server &server, Client *client, const std::string &token);
void runTestPong(Server &server, Client *client, const std::string &token);
void runTestMode(Server &server, Client *client);
void runTestTopic(Server &server, Client *client,
                  const std::string &channel,
                  const std::string &topic);
void runTestKick(Server &server, Client *client,
                 const std::string &channel,
                 const std::string &target,
                 const std::string &reason);
void runTestInvite(Server &server, Client *client,
                   const std::string &target,
                   const std::string &channel);