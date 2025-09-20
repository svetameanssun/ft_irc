 
#ifndef COMMANDDISPATCHER_HPP
#define COMMANDDISPATCHER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Replies.hpp"
#include "ParcerFlags.hpp"
#include "ParcerResult.hpp"

class CommandDispatcher{
	public:
		CommandDispatcher();
		int dispatch(std::vector <std::string> messageVec);
		const std::map<std::string, int (CommandDispatcher::*)(std::vector<std::string>)>& getDispatcherMap() const;
		bool isValidNick(std::string nick);
		bool isValidJoin(std::vector <std::string> messageVector);
	private:
		ParcerFlags flags;
		ParcerResult parcRes;
		std::map<std::string, int (CommandDispatcher::*)(std::vector <std::string> messageVec)> dispatcherMap;
		int dispatchPass(std::vector <std::string> messageVec);
		int dispatchNick(std::vector <std::string> messageVec);
		int dispatchUser(std::vector <std::string> messageVec);
		int dispatchQuit(std::vector <std::string> messageVec);
		int dispatchJoin(std::vector <std::string> messageVec);
		int dispatchMode(std::vector <std::string> messageVec);
		int dispatchTopic(std::vector <std::string> messageVec);
		int dispatchInvite(std::vector <std::string> messageVec);
		int dispatchKick(std::vector <std::string> messageVec);
		int dispatchPrivmsg(std::vector <std::string> messageVec);
		int dispatchInfo(std::vector <std::string> messageVec);
};

#endif
