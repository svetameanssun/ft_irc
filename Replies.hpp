#ifndef REPLIES_HPP
#define REPLIES_HPP

// ========================
// IRC Numeric Replies
// ========================

// ------------------------------------------------------
// PASS Command
// ------------------------------------------------------
// Notes: Must be sent before NICK/USER during registration.
// On success: no direct numeric reply (server waits for USER+NICK).
#define ERR_PASSWDMISMATCH     464 // Incorrect password supplied
#define ERR_NEEDLESSPARAMS     250  // if there are more then 2 params.
// ------------------------------------------------------
// NICK Command
// ------------------------------------------------------
// Notes: Sets or changes the user's nickname.
// - If the user is already registered, a successful NICK change is broadcast
//   to all relevant clients: ":oldnick!user@host NICK :newnick"
// - If the user is registering for the first time, the NICK is not broadcast;
//   server waits for USER command and then sends welcome numerics (001-004).
#define ERR_NONICKNAMEGIVEN    431 // No nickname was given in the NICK command
#define ERR_ERRONEUSNICKNAME   432 // Invalid nickname format
#define ERR_NICKNAMEINUSE      433 // Nickname already in use by another client
#define ERR_NICKCOLLISION      436 // Nickname collision detected between servers
#define ERR_RESTRICTED         484 // Nickname is restricted and cannot be used


// ------------------------------------------------------
// USER Command
// ------------------------------------------------------
// Notes: Defines user info. Used once at registration.
// Errors: see ERR_NEEDMOREPARAMS (461) and ERR_ALREADYREGISTRED (462).

// ---- Registration Success (after USER + NICK accepted) ----
#define RPL_WELCOME            001 // Welcome message after successful registration
#define RPL_YOURHOST           002 // Info about the server you connected to
#define RPL_CREATED            003 // Server creation date
#define RPL_MYINFO             004 // Server info and supported features


// ---------------------------------------------------------------
//  QUIT 
// ---------------------------------------------------------------
// QUIT :<message>
// Notes: No numeric reply, message broadcast to relevant channels

// ---------------------------------------------------------------
//  JOIN Command
// ---------------------------------------------------------------
// Used by a client to join one or more channels.
// Parameters: <channel> *( "," <channel> ) [ <key> *( "," <key> ) ]
// On success: server sends JOIN message to channel members + topic info.
// On failure: one of the errors below is returned.
// ---- JOIN Command Errors ---------------------------------------
#define ERR_NOSUCHCHANNEL      403 // No such channel exists
#define ERR_TOOMANYCHANNELS    405 // Client has joined too many channels
#define ERR_CHANNELISFULL      471 // Cannot join channel (channel is full)
#define ERR_INVITEONLYCHAN     473 // Cannot join channel (invite-only)
#define ERR_BANNEDFROMCHAN     474 // You are banned from the channel
#define ERR_BADCHANNELKEY      475 // Incorrect channel key (password required)
#define ERR_BADCHANMASK        476 // Invalid channel name mask

// ---- JOIN Command Replies ---------------------------------------
// When a user successfully joins a channel,
// the server usually sends back:
// Channel topic (sent after JOIN if topic exists)

#define RPL_NAMREPLY           353 // List of users in the channel after JOIN
#define RPL_ENDOFNAMES         366 // End of NAMES list
// Other Replies: RPL_TOPIC (332) or RPL_NOTOPIC (331)


// ---------------------------------------------------------------
//  CHANNEL MODE 
// ---------------------------------------------------------------
// Command: MODE <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
// Purpose: Query or change channel modes (topic-lock, invite-only, ban, etc.)
// Notes: RPL_UNIQOPIS 325 (unique channel operators) → channel MODE-specific, only needed if implement modes
// ---- CHANNEL MODE Command Errors ----
#define ERR_KEYSET             467 // Channel already has a key set (+k)
#define ERR_UNKNOWNMODE        472 // Unknown MODE flag for a channel
#define RPL_UNIQOPIS           325 // List of channel operators with "@" or similar prefix



// Other Errors: ERR_USERNOTINCHANNEL   (441) - to remove(-o) or add (+o) operator

// ---- CHANNEL MODE Command Replies ----
#define RPL_CHANNELMODEIS      324 // Current channel modes
#define RPL_BANLIST            367 // List of bans set on the channel
#define RPL_ENDOFBANLIST       368 // End of ban list
#define RPL_EXCEPTLIST         348 // List of exceptions to channel bans
#define RPL_ENDOFEXCEPTLIST    349 // End of exception list
#define RPL_INVITELIST         346 // List of users with invitation rights
#define RPL_ENDOFINVITELIST    347 // End of invite list

// ---------------------------------------------------------------
//  TOPIC
// ---------------------------------------------------------------
// Command: TOPIC <channel> [<topic>]
// Purpose: View, set, or clear the topic of a channel
// Notes:  - Without <topic>: server replies with current topic
//         - With <topic>: attempt to set channel topic
//         - With empty string: remove the channel topic
// Other Errors:  

// ---- TOPIC Command Errors ----
// Errors: see ERR_CHANOPRIVSNEEDED (482) 
// ERR_NOTONCHANNEL (442) // User is not on the specified channel

// ---- TOPIC Command Replies ----
#define RPL_NOTOPIC            331 // No topic is set on the channel
#define RPL_TOPIC              332 // Channel topic


// ---------------------------------------------------------------
//  INVITE
// ---------------------------------------------------------------
// Command: INVITE <nickname> <channel>
// Purpose: Invite a user to a channel
// Notes: 
//  - Only channel members may invite others to that channel
//  - For invite-only channels (+i), only channel operators may invite
//  - Only the inviter and the invited user are notified

// ---- INVITE Command Errors ----
#define ERR_NOTONCHANNEL    442  // Inviter is not on the specified channel
#define ERR_USERONCHANNEL      443 // Target user is already on the channel

// ---- INVITE Command Replies ----
#define RPL_INVITING           341 // Confirming that the user has been invited
#define RPL_AWAY               301 // Optional: target user is marked as away

// ---------------------------------------------------------------
//  KICK
// ---------------------------------------------------------------
// Command: KICK <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>]
// Purpose: Forcefully remove a user from a channel
// Notes:
//  - Either one channel with multiple users, or equal number of channels and users
//  - If a comment is provided, it is sent instead of the default message
//  - Server MUST NOT send multi-channel/multi-user KICKs to clients (backward compatibility)

// ---- KICK Command Errors ----
//Error: ERR_USERNOTINCHANNEL   (441)
#define ERR_BADCHANMASK        476 // Invalid channel name/mask
// ---------------------------------------------------------------
//  PRIVMSG
// ---------------------------------------------------------------
// Command: PRIVMSG <msgtarget> <text to be sent>
// Purpose: Send a private message to a user, channel, or (for operators) a host/server mask
// Notes: 
//  - <msgtarget> is usually a nickname or channel name
//  - Operators may use masks: #<mask> (host) or $<mask> (server)
//  - Server enforces rules to prevent sending to "#*" or "$*"

// ---- PRIVMSG Command Errors ----
#define ERR_NORECIPIENT        411 // No recipient given (missing <msgtarget>)
#define ERR_NOTEXTTOSEND       412 // No text to send (missing <text>)

#define ERR_NOTOPLEVEL         413 // Cannot send to a non-valid top-level target
#define ERR_WILDTOPLEVEL       414 // Cannot send to wildcard target

// ---- PRIVMSG Command Replies ----
// RPL_AWAY  (301) // Target user is marked as away (optional reply)

// ---------------------------------------------------------------
//  INFO
// ---------------------------------------------------------------
// Command: INFO [<target>]
// Purpose: Return information about the server (version, compile date, uptime, etc.)
// Notes:
//  - Wildcards allowed in <target>
//  - Used by clients to query server info

// ---- INFO Command Errors ----
#define ERR_NOSUCHSERVER       402 // Target server does not exist (INFO, SERVER)

// ---- INFO Command Replies ----
#define RPL_INFO               371 // Server information line
#define RPL_ENDOFINFO          374 // End of server information


// ------------------------------------------------------
// General Errors
// ------------------------------------------------------
#define ERR_NOSUCHNICK         401 // Target nickname does not exist (e.g., for PRIVMSG or WHOIS, INVITE)
#define ERR_NOSUCHCHANNEL      403 // Target channel does not exist (KICK, JOIN, MODE)
#define ERR_CANNOTSENDTOCHAN   404 // Cannot send message to channel (no access,e.g., +n, +m, banned) (PRIVMSG)
#define ERR_UNKNOWNCOMMAND     421 // Command not recognized by the server (sent after any command the server doesn’t know)
#define ERR_UNAVAILRESOURCE    437 // Target nickname temporarily unavailable (JOIN, NICK)
#define ERR_NEEDMOREPARAMS     461 // Not enough parameters supplied to the command
#define ERR_ALREADYREGISTRED   462 // USER command sent after client has already registered (PASS, USER, NICK)
#define ERR_CHANOPRIVSNEEDED   482 // Inviter lacks privileges to do that (INVITE, TOPIC, MODE, KICK )
#define ERR_NOCHANMODES        477 // Channel does not support channel modes (MODE, TOPIC)
#define ERR_USERNOTINCHANNEL  441 // User is not on the specified channel (KICK, MODE)
#define ERR_TOOMANYTARGETS     407 // Too many recipients/targets (applies to some cmds, incl. JOIN, PRIVMSG)


#endif

