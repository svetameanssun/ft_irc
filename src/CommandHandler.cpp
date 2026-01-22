#include "CommandHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"

CommandHandler::CommandHandler(Server &server) : _server(server) {}

//       MODE #channame -flag params 
//        0       1       2    3
//       itkol
//          NO PARAMS:
//            i t 
//          WITH PARAMS:
//            k o l

bool CommandHandler::flagNeedsParam(char c, bool adding){
    if(!adding && c == 'o'){
        return (true);
    }
    if (adding && (c == 'k' || c == 'o' || c == 'l')){
        return (true);
    }
    else
        return (false);
}

// Entry point: dispatch commands
void CommandHandler::execute(Client *client, const std::string &command, AParserResult *result)
{
    //TODO:(Optional) Change for switch, or pointers to functions :)
    if (command == "PASS")
        cmdPass(client, result);
    else if (command == "NICK")
        cmdNick(client, result);
    else if (command == "USER")
        cmdUser(client, result);
    else if (command == "JOIN")
        cmdJoin(client, result);
    else if (command == "PRIVMSG")
        cmdPrivmsg(client, result);
    else if (command == "NOTICE")
        cmdNotice(client, result);
    else if (command == "PART")
        cmdPart(client, result);
    else if (command == "QUIT")
        cmdQuit(client, result);
    //else if (command == "PING")
    //    cmdPing(client, result);
    //else if (command == "PONG")
    //    cmdPong(client, result);
    else if (command == "MODE")
        cmdMode(client, result);
    else if (command == "TOPIC")
        cmdTopic(client, result);
    else if (command == "KICK")
        cmdKick(client, result);
    else if (command == "INVITE")
        cmdInvite(client, result);
    else
        MessageSender::sendNumeric(_server.getServerName(), client, 421, command + " :Unknown command");
}
