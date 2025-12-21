#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdPass(Client *client, AParserResult *result)
{
    if (!client || !result) return;
    
    ParserResultPass *result2 = static_cast<ParserResultPass*>(result);
    
    if (client->isRegistered())
    {
        // 462 ERR_ALREADYREGISTRED
        MessageSender::sendNumeric(_server.getServerName(),
                                    client, ERR_ALREADYREGISTRED,
                                    ":You may not reregister");
        return;
    }

    std::vector<std::string> params = result2->getPassParams();

    const std::string &pass = params.at(0);

    if (!_server.getPassword().empty() && pass != _server.getPassword())
    {
        //TODO: [NETWORKING] I believe we need to cut the connection if the password does not match; the user needs to open a new connection
        // 464 ERR_PASSWDMISMATCH
        client->setPassAccepted(false);
        log_warning("Password is not correct, user cannot register");

        MessageSender::sendNumeric(_server.getServerName(),
                                    client, ERR_PASSWDMISMATCH,
                                    ":Password incorrect");
        return;
    }

    client->setPassAccepted(true);
    log_debug("PASS accepted for client fd=%d", client->getFd());
}