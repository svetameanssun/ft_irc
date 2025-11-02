#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdPass(Client *client, AParcerResult *result)
{
    if (!client || !result) return;
    
    ParcerResultPass *result2 = static_cast<ParcerResultPass*>(result);
    
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
        //TODO: the RFC does not specify this, but to me it is pretty logic to implement it
        // 464 ERR_PASSWDMISMATCH
        client->setPassAccepted(false);
        log_debug("Password not correct, user cannot register");

        MessageSender::sendNumeric(_server.getServerName(),
                                    client, ERR_PASSWDMISMATCH,
                                    ":Password incorrect");
        return;
    }

    client->setPassAccepted(true);
    log_debug("PASS accepted for client fd=%d", client->getFd());
}