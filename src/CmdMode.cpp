#include "CommandHandler.hpp"
#include "Server.hpp"

//TODO: [LANA] Implement the parser here, Ruben will implement the checks
//       MODE #channame -flag params 
//        0       1       2    3
//       itkol
//          NO PARAMS:
//            i t 
//          WITH PARAMS:
//            k o l

//applyFlag(paramsVec[i][j], paramsVec[iFlagParams])

//+kol
int applyFlag(Client *client, char flag, std::string params){
    
    
}

//+it
int applyFlag(Client *client, char flag){
    if (flag == 'i' ){
        
    }
    if (flag == 't'){
        
    }
    
}

-o
int removeFlag(Client *client, char flag, std::string params){
    
}

-kl
int removeFlag(Client *client, char flag){
    
}

void CommandHandler::cmdMode(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;
    // as far as I understand, only chops can do this actions
    //so I check whether the client has the operator status
    if (!client->isOperator()){
        // [CHECK] 
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_CHANOPRIVSNEEDED, " :You’re not channel operator");
        return;
    }
    ParserResultMode *parserRes = static_cast<ParserResultMode*>(result);
    parserRes->printResult();
    const std::vector<std::string> &paramsVec = parserRes->getModeParams();
    const std::string & modeFlagsStr = parserRes->getModeFlagsStr();
    size_t iFlagParams;
    bool flagOn;
    size_t i;

    //checks if the channel name is valid
    if (!parserRes->isValidChanName(paramsVec.at(0))){
        // returns smth that indicates that the channel name is invalid
        // [CHECK] 
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOSUCHCHANNEL, " :No such channel");
        return;
    }

    for (i = 1; i < paramsVec.size(); i++){
        if (!parserRes->hasPlusMinus(paramsVec[i])){
            iFlagParams = i;
            break;
        }
    }
    for (i = 1; i < paramsVec.size(); i++){
        if (parserRes->hasPlusMinus(paramsVec[i]) &&  i < iFlagParams){
            for(int j = 0; paramsVec[i].length(); j++){
                if (paramsVec[i][j] == '+'){
                    flagOn = true;
                    j++;
                }
                else if (paramsVec[i][j] == '-'){
                    flagOn = false;
                    j++;
                }
                if (paramsVec[i][j] == 'k' || paramsVec[i][j] == 'o'|| paramsVec[i][j] == 'l'){
                    if (flagOn){
                        applyFlag(client, paramsVec[i][j], paramsVec[iFlagParams]);
                        iFlagParams++;
                    }
                    else{
                        if (paramsVec[i][j] == 'k' || paramsVec[i][j] == 'l'){
                            //No parameters needed to remove these flags;
                            removeFlag(client, paramsVec[i][j]);
                        }
                        else if(paramsVec[i][j] == 'o'){
                        removeFlag(client, paramsVec[i][j], paramsVec[iFlagParams]);
                        iFlagParams++;
                        }
                    }
                }
                else if (paramsVec[i][j] == 'i' || paramsVec[i][j] == 't'){
                    if (flagOn){
                        applyFlag(client, paramsVec[i][j]);
                    }
                    else{
                        removeFlag(client, paramsVec[i][j]);
                    }
                }
                else{
                    
                }
            }
        }
    }
    //TODO: [RUBEN] I guess this is needed at the end of the command
    //// Broadcast the final mode change to the channel
    //std::ostringstream oss;
    //oss << ":" << client->getNick() << "!" << client->getUser() << "@" << client->getHost()
    //    << " MODE " << firstParam<< " " << modeStr;
    //// Append arguments used (if any)
    //for (size_t j = 2; j < paramsVec.size(); ++j)
    //    oss << " " << paramsVec[j];
    //oss << "\r\n";
//
    //chan->broadcast(oss.str());
}

    /*const std::string firstParam = paramsVec.at(0);
    // ===============================================
    // USER MODES
    // ===============================================
    if (firstParam.at(0) != '#')
    {
        // Only server can grant +o (IRC operator)
        if (paramsVec.size() == 2)
        {
            // Query user mode
            std::string modes = client->isOperator() ? "+o" : "";
            MessageSender::sendNumeric(_server.getServerName(), client, RPL_UMODEIS, client->getNick() + " " + modes);
            return;
        }
        const std::string &modeStr = paramsVec.at(1);
        if (modeStr.find('o') != std::string::npos)
        {
            // Users cannot set themselves as IRC operators
            return;
        }
        else
        {
            MessageSender::sendNumeric(_server.getServerName(), client, ERR_UNKNOWNMODE, " :Unknown mode flag");
        }
        return;
    }

    // ===============================================
    // CHANNEL MODES
    // ===============================================
    Channel *chan = _server.getChannelManager().findChannel(firstParam);
    if (!chan)
    {
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOSUCHCHANNEL, firstParam + " :No such channel");
        return;
    }

    // Query channel modes, append all the modes that are active
    if (paramsVec.size() == 1)
    {
        std::string modeStr = "+";
        if (chan->isInviteOnly()) modeStr += "i";
        if (chan->isTopicLocked()) modeStr += "t";
        if (chan->hasKey()) modeStr += "k";
        if (chan->hasLimit() > 0) modeStr += "l";
        // +o not listed since it applies to specific users
        MessageSender::sendNumeric(_server.getServerName(), client, 324, chan->getName() + " " + modeStr);
        return;
    }

    // Must be operator to modify modes
    if (!chan->isMember(client->getFd()))
    {
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOTONCHANNEL, firstParam + " :You're not on that channel");
        return;
    }
    if (!chan->isOperator(client->getFd()))
    {
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_CHANOPRIVSNEEDED, firstParam + " :You're not channel operator");
        return;
    }

    // --- Parse and apply modes ---
    const std::string &modeStr = firstParam;
    bool adding = true;
    size_t argIndex = 2;

    for (size_t i = 0; i < modeStr.size(); ++i)
    {
        char mode = modeStr[i];
        if (mode == '+') { adding = true; continue; }
        if (mode == '-') { adding = false; continue; }

        switch (mode)
        {
            case 'i':
                chan->setInviteOnly(adding);
                break;

            case 't':
                chan->setTMode(adding);
                break;

            case 'k':
                if (adding)
                {
                    if (argIndex >= paramsVec.size())
                    {
                        MessageSender::sendNumeric(_server.getServerName(), client, 461, "MODE +k :Not enough parameters");
                        return;
                    }
                    chan->setKey(paramsVec[argIndex++]);
                }
                else
                {
                    chan->setKey("");
                }
                break;

            case 'o':
                if (argIndex >= paramsVec.size())
                {
                    MessageSender::sendNumeric(_server.getServerName(), client, 461, "MODE +o :Not enough parameters");
                    return;
                }
                {
                    std::string targetNick = paramsVec[argIndex++];
                    Client *targetClient = _server.getClientManager().findByNick(targetNick);
                    if (!targetClient || !chan->isMember(targetClient->getFd()))
                    {
                        MessageSender::sendNumeric(_server.getServerName(), client, 441, targetNick + " " + chan->getName() + " :They aren't on that channel");
                        return;
                    }
                    if (adding)
                        chan->promoteToOp(targetClient->getFd());
                    else
                        chan->demoteFromOp(targetClient->getFd());
                }
                break;

            case 'l':
                if (adding)
                {
                    if (argIndex >= paramsVec.size())
                    {
                        MessageSender::sendNumeric(_server.getServerName(), client, 461, "MODE +l :Not enough parameters");
                        return;
                    }
                    int limit = std::atoi(paramsVec[argIndex++].c_str());
                    if (limit <= 0)
                        limit = 0;
                    chan->setUserLimit(limit);
                }
                else
                {
                    chan->setUserLimit(0);
                }
                break;

            default:
                MessageSender::sendNumeric(_server.getServerName(), client, 472, std::string(1, mode) + " :is unknown mode char to me");
                break;
        }
    }*/
