#ifndef PARCER_HPP
#define PARCER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>
#include <map>
#include "CommandHandler.hpp"


class Parcer{
	public:
		Parcer(std::string message): _message(message){};
		Parcer(const Parcer&other);
		Parcer&operator=(const Parcer&other);
		~Parcer();

		void splitMessage(void);
		int commandReply();
		
		void setClientType(void); // TO DO
		bool getClientType(void) const;
		std::string getMessage(void)const;
		std::vector<std::string> getMessageVec(void) const;
		private:
		const std::string _message;
		std::vector<std::string> _messageVec;
		bool _isOperator; // later this "flag" we can introduce
		// in different ways: through parameters, class client
		// as parameter, etc.
		CommandHandler _commandList;
	
};
/**
 * @brief parces and analizes the command and its params.
 * 
 * This function initiates parcing, analizes the command and parameter
 * structure, and passes the data to the server.
 * 
 * @param NOW void
 *		LATER Parcer &parcer, to init Parcer class outside 
 * @returns RPL/0 on  success or l ERR (from Replies.hpp)
 */

int launchParcing(void);

#endif