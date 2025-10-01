 
#ifndef COMMANDDISPATCHER_HPP
#define COMMANDDISPATCHER_HPP
#include <iostream>
 #include <sstream>
#include <string>
#include <vector>
#include <map>


#include "Replies.hpp"
#include "ParcerResultNick.hpp"
#include "ParcerResultJoin.hpp"
#include "ParcerResultPass.hpp"

class CommandDispatcher{
	public:
		CommandDispatcher();
		CommandDispatcher(const CommandDispatcher &other);
		CommandDispatcher&operator=(const CommandDispatcher &other);
		~CommandDispatcher();
		int dispatch(std::vector <std::string> messageVec);
		const std::map<std::string, int (CommandDispatcher::*)(std::vector<std::string>)>& getDispatcherMap() const;
	private:
		//AParcerResult _parcerResult;
		std::auto_ptr<AParcerResult> _parcerResult;
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

void printMap(const std::map<std::string, std::string> &myMap);
void printVec(const std::vector<std::string> &myVec);

#endif
