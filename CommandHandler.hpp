
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
		void handle(std::string command);
	
	private:
		const std::vector <std::string> validCommands;
		std::map<std::string, void (CommandHandler::*)(void)> handlerMap;
		void handlePass();
		void handleNick();
		void handleUser();
		void handleQuit();
		void handleJoin();
		void handleMode();
		void handleTopic();
		void handleInvite();
		void handleKick();
		void handlePrivmsg();
		void handleInfo();
		
};

#endif