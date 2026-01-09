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
void CommandHandler::cmdMode(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    ParserResultMode *result2 = static_cast<ParserResultMode*>(result);
    result2->printResult();
    const std::vector<std::string> &paramsVec = result2->getModeParams();
    const std::string & modeFlagsStr = result2->getModeFlagsStr();
    size_t iFlagParms;
    bool flagOn;

    //checks if the channel name is valid
    if (!result2->isValidChanName(paramsVec.at(0))){
        // returns smth that indicates that the channel name is invalid
    }

    for (size_t i = 1; i < paramsVec.size(); i++){
        if (!result2->hasPlusMinus(paramsVec[i])){
            iFlagParams = i;
            break;
        }
    }

    for (i = 1; i < paramsVec.size(); i++){
        if (result2->hasPlusMinus(paramsVec[i]) &&  i < iFlagParams){
            for(int j = 0; paramsVec[i].length(); j++){
                if (iFlagParams >= paramVec.size()){
                            // we need to send back to the client this error:
                            //     ERR_NEEDMOREPARAMS (MODE)
                        break;
                }
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

                        //HERE [RUBEN] has to apply a flag -> paramsVec[i][j]
                        //               with its parameter -> paramsVec[iFlagParams];
                        //Ex. of a function:
                        //  applyFlag(paramsVec[i][j], paramsVec[iFlagParams]);
                        iFlagParams++;
                    }
                    else{
                        if (paramsVec[i][j] == 'k' || paramsVec[i][j] == 'l'){
                            //[RUBEN] removes one of 2 flags, no parameters needed;
                            //Ex. of a function:
                            //  removeFlag(paramsVec[i][j]);
                        }
                        else if(paramsVec[i][j] == 'o'){
                        //HERE [RUBEN] has to remove a flag -> paramsVec[i][j]
                        //               with its parameter -> paramsVec[iFlagParams];

                        //Ex. of a function:
                        //  removeFlag(paramsVec[i][j], paramsVec[iFlagParams]);
                        iFlagParams++;
                        }
                    }
                }
                else if (paramsVec[i][j] == 'i' || paramsVec[i][j] == 't'){
                    if (flagOn){
                        //HERE [RUBEN] has to apply a flag -> paramsVec[i][j], no params needed!
                        ///Ex. of a function:
                        //  applyFlag(paramsVec[i][j]);
                    }
                    else{
                        //HERE [RUBEN] has to remove a flag -> paramsVec[i][j], no params needed!
                        ///Ex. of a function:
                        //  removeFlag(paramsVec[i][j]);
                    }
                }
            }
        }
        if (iFlagParams >= paramVec.size()){
                            // we need to send back to the client this error:
                            //     ERR_NEEDMOREPARAMS (MODE)
            break;
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
            MessageSender::sendNumeric(_server.getServerName(), client, ERR_UNKNOWNMODE, modeStr + " :Unknown mode flag");
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