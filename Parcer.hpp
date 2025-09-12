
#ifndef PARCER_HPP
#define PARCER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>
#include <map>

typedef enum CommandList{
	PASS, //0
	NICK, //1
	JOIN, //2
	PRIVMSG, //3
	QUIT, //4
	PING, //5

	KICK, //6
	INVITE, //7
	TOPIC, //8
	MODE //9
} CmdLst;



typedef enum PrefixType{
	PREF_USER,
	PREF_SERVER
} PrefT;


class Parcer{
	public:
		Parcer(std::string message): _message(message){};
		//Parcer(const Parcer&other);
		//Parcer&operator=(const Parcer&other);
		~Parcer();

		std::string getMessage(std::string message)const;
		std::vector<std::string> customSplit();
		//void checkCommand(std::string &message);
		//bool Parcer::getClientType(void) const;
		//void Parcer::setClientType(void); // TO DO
	private:
		std::string _message;
		bool isOperator; // later this "flag" we can introduce
						// in different ways: through parameters, class client
						// as parameter, etc.
	
};

#endif
