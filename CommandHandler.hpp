
#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <map>

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



class CommandHandler{
	public:
		CommandHandler()
		: validCommands({"PASS",
			"NICK",
			"USER",
			"QUIT",

			"JOIN",
			"PRIVMSG",
			"KICK",
			"INVITE",
			"TOPIC",
			"MODE" }){
		};
		
		const std::vector <std::string> &getValidCommands(void) const;
		std::vector<std::string>::const_iterator begin() const;
		std::vector<std::string>::const_iterator end() const;
		int handle(std::string command);
	
	private:
		const std::vector <std::string> validCommands;
		std::map<std::string, void (CommandHandler::*)(void)> handlerMap;
		int handlePass();
		int handleNick();
		int handleUser();
		int handleQuit();
		int handleJoin();
		int handleMode();
		int handleTopic();
		int handleInvite();
		int handleKick();
		int handlePrivmsg();
		int handleInfo();
		
};

#endif
