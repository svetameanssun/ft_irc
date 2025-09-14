#ifndef COMMANDVEC_HPP
#define COMMANDVEC_HPP

#include <iostream>
#include <string>
#include <vector>

typedef enum CommandEnum{
	PASS, 
	NICK, 
	JOIN, 
	PRIVMSG, 
	QUIT, 
	PING, 

	KICK,
	INVITE, 
	TOPIC, 
	MODE 
} CmdLst;

class CommandVec{
	public:
		CommandVec() : commandVec({"PASS", "NICK", "JOIN", "PRIVMSG", "QUIT",
			"PING", "KICK","INVITE", "TOPIC", "MODE" }){
		};
		
		const std::vector <std::string> &getCommandVec(void) const;
	private:
		const std::vector <std::string> commandVec;
};

#endif
