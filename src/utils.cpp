#include "utils.hpp"
#include "Replies.hpp"

void log_msg(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    std::cout << GREEN << "[LOG]: ";
    vprintf(format, args);
    va_end(args);
    std::cout << std::endl << RESET;
}

void log_debug(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    std::cout << YELLOW << "[DEBUG]: ";
    vprintf(format, args);
    va_end(args);
    std::cout << std::endl << RESET;
}

void log_warning(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    std::cout << ORANGE << "[WARNING]: ";
    vprintf(format, args);
    va_end(args);
    std::cout << std::endl << RESET;  
}


void log_err(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    std::cerr << RED << "[ERROR]: ";
    vprintf(format, args);
    va_end(args);
    std::cerr << std::endl << RESET;
}

//Verbosity for clearness
bool isAllowed(int code)
{
    switch (code)
    {
        /* replies considered successful */
        case RPL_WELCOME:
        case RPL_YOURHOST:
        case RPL_CREATED:
        case RPL_MYINFO:
        case RPL_NAMREPLY:
        case RPL_ENDOFNAMES:
        case RPL_NOTOPIC:
        case RPL_TOPIC:
        case RPL_CHANNELMODEIS:
        case RPL_UNIQOPIS:
        case RPL_BANLIST:
        case RPL_ENDOFBANLIST:
        case RPL_EXCEPTLIST:
        case RPL_ENDOFEXCEPTLIST:
        case RPL_INVITELIST:
        case RPL_ENDOFINVITELIST:
        case RPL_INVITING:
        case RPL_AWAY:
        case RPL_INFO:
        case RPL_ENDOFINFO:
            return true;

        /* known error codes (explicit) */
        case ERR_PASSWDMISMATCH:
        case ERR_NEEDLESSPARAMS:
        case ERR_NONICKNAMEGIVEN:
        case ERR_ERRONEUSNICKNAME:
        case ERR_NICKNAMEINUSE:
        case ERR_NICKCOLLISION:
        case ERR_RESTRICTED:
        case ERR_NOSUCHCHANNEL:
        case ERR_TOOMANYCHANNELS:
        case ERR_CHANNELISFULL:
        case ERR_INVITEONLYCHAN:
        case ERR_BANNEDFROMCHAN:
        case ERR_BADCHANNELKEY:
        case ERR_BADCHANMASK:
        case ERR_KEYSET:
        case ERR_UNKNOWNMODE:
        case ERR_NOTONCHANNEL:
        case ERR_USERNOTINCHANNEL:
        case ERR_NORECIPIENT:
        case ERR_NOTEXTTOSEND:
        case ERR_NOTOPLEVEL:
        case ERR_WILDTOPLEVEL:
        case ERR_NOSUCHSERVER:
        case ERR_NOSUCHNICK:
        case ERR_CANNOTSENDTOCHAN:
        case ERR_UNKNOWNCOMMAND:
        case ERR_UNAVAILRESOURCE:
        case ERR_NEEDMOREPARAMS:
        case ERR_ALREADYREGISTRED:
        case ERR_CHANOPRIVSNEEDED:
        case ERR_NOCHANMODES:
        case ERR_TOOMANYTARGETS:
        case ERR_WRONGINPUT:
            return false;

        default:
            /* fallback: por rango numérico (RFC): 001-399 -> no error, >=400 -> error */
            if (code >= 400) return false;
            return true;
    }
}

// the suite for the check params function
static bool isNumber(const std::string &s)
{
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); i++)
        if (!std::isdigit(s[i]))
            return false;
    return true;
}

static bool isValidPassword(const std::string &pass)
{
    if (pass.empty())
        return false;

    for (size_t i = 0; i < pass.size(); i++)
    {
        if (std::isspace(pass[i]) || !std::isprint(pass[i]))
            return false;
    }
    return true;
}

int checkParams(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return -1;
    }

    std::string portStr = argv[1];
    std::string password = argv[2];

    if (!isNumber(portStr))
    {
        std::cerr << "Error: Port must be numeric." << std::endl;
        return -1;
    }

    int port = std::atoi(portStr.c_str());

    if (port < 1024 || port > 65535)
    {
        std::cerr << "Error: Port must be between 1024 and 65535." << std::endl;
        return -1;
    }

    if (!isValidPassword(password))
    {
        std::cerr << "Error: Invalid password." << std::endl;
        return -1;
    }

    return 0;
}
