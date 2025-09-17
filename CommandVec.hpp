#ifndef COMMANDVEC_HPP
#define COMMANDVEC_HPP

#include <iostream>
#include <string>
#include <vector>

typedef enum CommandEnum{
	// Connection Registration
	PASS, 
	NICK,
	USER,
	QUIT,

	//Channel Operations
	JOIN, 
	PRIVMSG, 

	KICK,
	INVITE, 
	TOPIC, 
	MODE 
} CmdLst;

class CommandVec{
	public:
		CommandVec() : commandVec({"PASS", "NICK", "JOIN", "PRIVMSG", "QUIT",
			"PING", "QUIT", "KICK","INVITE", "TOPIC", "MODE" }){
		};
		
		const std::vector <std::string> &getCommandVec(void) const;
	private:
		const std::vector <std::string> commandVec;
};

#endif
