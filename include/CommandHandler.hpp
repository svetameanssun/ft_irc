#pragma once

#include <string>
#include <vector>
#include "Server.hpp"
#include "Client.hpp"

class CommandHandler {
private:
    Server& _server; // reference to server state

    // command implementations
    void cmdJoin(Client* client, const std::vector<std::string>& args);

public:
    CommandHandler(Server& server);

    // entry point for commands
    void execute(Client* client, const std::string& command,
                 const std::vector<std::string>& args);
};
