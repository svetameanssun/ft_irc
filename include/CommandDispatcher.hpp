 
#ifndef COMMANDDISPATCHER_HPP
#define COMMANDDISPATCHER_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>


#include "Replies.hpp"
#include "ParserResultNick.hpp"
#include "ParserResultJoin.hpp"
#include "ParserResultPass.hpp"
#include "ParserResultUser.hpp"
#include "ParserResultMode.hpp"
#include "ParserResultPrivmsg.hpp"
#include "ParserResultTopic.hpp"
#include "ParserResultKick.hpp"
#include "ParserResultInvite.hpp"
#include "ParserResultPart.hpp"
#include "ParserResultQuit.hpp"
#include "ParserResultNotice.hpp"


class CommandDispatcher{
	public:
		CommandDispatcher();
		
		~CommandDispatcher();
		int dispatch(std::vector <std::string> &messageVec);
		AParserResult * getParserResult() const;
		const std::map<std::string, int (CommandDispatcher::*)(std::vector<std::string>&)>& getDispatcherMap() const;
		void createParserResult(std::string &command);
		int flagMal;
	
		private:
		CommandDispatcher(const CommandDispatcher &other);
		CommandDispatcher&operator=(const CommandDispatcher &other);
		AParserResult *_parserResult; // We have to delete it manually after pasing the data!!!

		std::map<std::string, int (CommandDispatcher::*)(std::vector <std::string> &messageVec)> dispatcherMap;
		int dispatchPass(std::vector <std::string> &messageVec);
		int dispatchNick(std::vector <std::string> &messageVec);
		int dispatchUser(std::vector <std::string> &messageVec);
		int dispatchQuit(std::vector <std::string> &messageVec);
		int dispatchJoin(std::vector <std::string> &messageVec);
		int dispatchPart(std::vector <std::string> &messageVec);
		int dispatchMode(std::vector <std::string> &messageVec);
		int dispatchTopic(std::vector <std::string> &messageVec);
		int dispatchInvite(std::vector <std::string> &messageVec);
		int dispatchKick(std::vector <std::string> &messageVec);
		int dispatchPrivmsg(std::vector <std::string> &messageVec);
		int dispatchNotice(std::vector <std::string> &messageVec);
};


#endif