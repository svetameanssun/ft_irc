#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdNotice(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    // NOTICE should not generate errors, so
    // if not registered, silently ignore (NO ERR_NOTREGISTERED)
    if (!client->isRegistered())
        return;

    ParserResultNotice *result2 = static_cast<ParserResultNotice*>(result);
    
    const std::vector<std::string> &targetsVec = result2->getTargetVec();
    const std::string &message = result2->getNoticeMessage();
    
    for (size_t i = 0; i < targetsVec.size(); ++i)
    {
        const std::string &target = targetsVec[i];
    
        // Channel NOTICE
        if (!target.empty() && target[0] == '#')
        {
            Channel *chan = _server.getChannelManager().findChannel(target);
        
            // RFC: silently ignore invalid channel or not-on-channel
            if (!chan || !chan->userExists(client->getFd()))
                continue;
        
            std::string msg = ":" + client->getPrefix() +
                              " NOTICE " + target +
                              " :" + message + "\r\n";
        
            chan->broadcast(msg);
        }
        // User NOTICE
        else
        {
            Client *receiver = _server.getClientManager().findByNick(target);
        
            // RFC: silently ignore unknown nick
            if (!receiver)
                continue;
        
            std::string msg = ":" + client->getPrefix() +
                              " NOTICE " + target +
                              " :" + message + "\r\n";
        
            MessageSender::sendToClient(receiver, msg);
        }
    }

}
