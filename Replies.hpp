#ifndef REPLIES_HPP
#define REPLIES_HPP

// ========================
// IRC Numeric Replies
// ========================

// ---- PASS Command Errors ----
#define ERR_PASSWDMISMATCH     464 // Incorrect password supplied

// ---- NICK Command Errors ---- (Creating a new user)
#define ERR_NONICKNAMEGIVEN    431 // No nickname was given in the NICK command
#define ERR_ERRONEUSNICKNAME   432 // Invalid nickname format
#define ERR_NICKNAMEINUSE      433 // Nickname already in use by another client
#define ERR_NICKCOLLISION      436 // Nickname collision detected between servers
#define ERR_UNAVAILRESOURCE    437 // Target nickname temporarily unavailable
#define ERR_RESTRICTED         484 // Nickname is restricted and cannot be used

// N.B! If a user changes their nick with this command, server broadcasts it to all the clients.
// EXAMPLE :NICK_OLD!user@host NICK :NICK_NEW

// ---- USER Command Errors ---- 
// All errors a USER command can give is in General Errors

// ---- Registration Success (after USER + NICK accepted) ----
#define RPL_WELCOME            001 // Welcome message after successful registration
#define RPL_YOURHOST           002 // Info about the server you connected to
#define RPL_CREATED            003 // Server creation date
#define RPL_MYINFO             004 // Server info and supported features

// ---- MODE Command Errors ----
#define ERR_USERSDONTMATCH     502 // Attempt to change modes for another user (nick mismatch)
#define ERR_UMODEUNKNOWNFLAG   501 // Unknown mode flag supplied

// ---- MODE Command Replies ----
#define RPL_UMODEIS            221 // Reply with the user’s current mode settings

// ---- General Errors ----
#define ERR_NOSUCHNICK         401 // Target nickname does not exist (e.g., for PRIVMSG or WHOIS)
#define ERR_NOSUCHSERVER       402 // Target server does not exist
#define ERR_NOSUCHCHANNEL      403 // Target channel does not exist
#define ERR_CANNOTSENDTOCHAN   404 // Cannot send message to channel (no access, etc.)
#define ERR_UNKNOWNCOMMAND     421 // Command not recognized by the server
#define ERR_ERRONEUSCOMMAND    422 // Command parameters invalid or malformed
#define ERR_NEEDMOREPARAMS     461 // Not enough parameters supplied to the command
#define ERR_ALREADYREGISTRED   462 // USER command sent after client has already registered (PASS, USER)

#endif

