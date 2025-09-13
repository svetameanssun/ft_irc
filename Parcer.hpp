#ifndef PARCER_HPP
#define PARCER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>
#include <map>
#include "CommandVec.hpp"


class Parcer{
	public:
		Parcer(std::string message): _message(message){};
		Parcer(const Parcer&other);
		Parcer&operator=(const Parcer&other);
		~Parcer();

		std::string getMessage(void)const;
		std::vector<std::string> splitMessage(std::vector<std::string> &messageVec);
		bool isValidCommand(std::string &message);
		bool isValidParam(std::vector<std::string> &messageVec);
		
		bool getClientType(void) const;
		void setClientType(void); // TO DO
		bool isCommonCommand(std::string command);
		bool isOperatorComamnd(std::string command);
	private:
		std::string _message;
		bool isOperator; // later this "flag" we can introduce
						// in different ways: through parameters, class client
						// as parameter, etc.
		CommandVec commands;
	
};

#endif