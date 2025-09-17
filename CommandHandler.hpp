
#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Replies.hpp"

/*typedef enum CommandEnum{
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
} CmdLst;*/



class CommandHandler{
	public:
		CommandHandler();
		int handle(std::vector <std::string> messageVec);
		const std::map<std::string, int (CommandHandler::*)(std::vector<std::string>)>& getHandlerMap() const;
		

	private:
		std::map<std::string, int (CommandHandler::*)(std::vector <std::string> messageVec)> handlerMap;
		int handlePass(std::vector <std::string> messageVec);
		int handleNick(std::vector <std::string> messageVec);
		int handleUser(std::vector <std::string> messageVec);
		int handleQuit(std::vector <std::string> messageVec);
		int handleJoin(std::vector <std::string> messageVec);
		int handleMode(std::vector <std::string> messageVec);
		int handleTopic(std::vector <std::string> messageVec);
		int handleInvite(std::vector <std::string> messageVec);
		int handleKick(std::vector <std::string> messageVec);
		int handlePrivmsg(std::vector <std::string> messageVec);
		int handleInfo(std::vector <std::string> messageVec);
		
};

#endif
