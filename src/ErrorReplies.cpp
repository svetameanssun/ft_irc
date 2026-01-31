#include "ErrorReplies.hpp"

void ErrorReplies::needMoreParams(Server &server, Client *client, const std::string &cmd)
{
    MessageSender::sendNumeric(
        server.getServerName(),
        client,
        ERR_NEEDMOREPARAMS,
        cmd + " :Not enough parameters"
    );
}

void ErrorReplies::unknownCommand(Server &server, Client *client, const std::string &cmd)
{
    MessageSender::sendNumeric(
        server.getServerName(),
        client,
        ERR_UNKNOWNCOMMAND,
        cmd + " :Unknown command"
    );
}

void ErrorReplies::noSuchNick(Server &server, Client *client, const std::string &nick)
{
    MessageSender::sendNumeric(
        server.getServerName(),
        client,
        ERR_NOSUCHNICK,
        nick + " :No such nick"
    );
}

void ErrorReplies::noSuchChannel(Server &server, Client *client, const std::string &channel)
{
    MessageSender::sendNumeric(
        server.getServerName(),
        client,
        ERR_NOSUCHCHANNEL,
        channel + " :No such channel"
    );
}

void ErrorReplies::notRegistered(Server &server, Client *client)
{
    MessageSender::sendNumeric(
        server.getServerName(),
        client,
        ERR_NOTREGISTERED,
        ":You have not registered"
    );
}

void ErrorReplies::alreadyRegistered(Server &server, Client *client)
{
    MessageSender::sendNumeric(
        server.getServerName(),
        client,
        ERR_ALREADYREGISTRED,
        ":You may not reregister"
    );
}

void ErrorReplies::passwdMismatch(Server &server, Client *client)
{
    MessageSender::sendNumeric(
        server.getServerName(),
        client,
        ERR_PASSWDMISMATCH,
        ":Password incorrect"
    );
}

void ErrorReplies::wrongInput(Server &server, Client *client)
{
    MessageSender::sendNumeric(
        server.getServerName(),
        client,
        666, // Custom WRONGINPUT
        ":Wrong input"
    );
}

void ErrorReplies::noRecipient(Server &server, Client *client, const std::string &cmd)
{
    MessageSender::sendNumeric(
        server.getServerName(),
        client,
        ERR_NORECIPIENT,
        cmd + " :No recipient given"
    );
}

void ErrorReplies::noTextToSend(Server &server, Client *client)
{
    MessageSender::sendNumeric(
        server.getServerName(),
        client,
        ERR_NOTEXTTOSEND,
        ":No text to send"
    );
}

void ErrorReplies::chooseError(Server &server, Client *client, int ret)
{
    switch (ret)
    {
        case ERR_UNKNOWNCOMMAND:
            ErrorReplies::unknownCommand(server, client, server.getParsingResult()->getCommand());
            break;

        case ERR_NEEDMOREPARAMS:
            ErrorReplies::needMoreParams(server, client, server.getParsingResult()->getCommand());
            break;

        case ERR_NOTREGISTERED:
            ErrorReplies::notRegistered(server, client);
            break;

        //case ERR_NOSUCHNICK:
        //    ErrorReplies::noSuchNick(server, client, server.getParsingResult()->getModeParams[0]);
        //    break;
//
        //case ERR_NOSUCHCHANNEL:
        //    ErrorReplies::noSuchChannel(server, client, server.getParsingResult()->get[0]);
        //    break;

        case ERR_ALREADYREGISTRED:
            ErrorReplies::alreadyRegistered(server, client);
            break;

        case ERR_PASSWDMISMATCH:
            ErrorReplies::passwdMismatch(server, client);
            break;
        
        case ERR_NORECIPIENT:
            ErrorReplies::noRecipient(server, client, server.getParsingResult()->getCommand());
            break;

        case ERR_NOTEXTTOSEND:
            ErrorReplies::noTextToSend(server, client);
            break;

        case 666: // Custom WRONGINPUT
            ErrorReplies::wrongInput(server, client);
            break;

        default:
            MessageSender::sendNumeric(
                server.getServerName(),
                client,
                ret,
                ":Unknown error"
            );
    }
}