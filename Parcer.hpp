#ifndef PARCER_HPP
#define PARCER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>

typedef enum PrefixType{
	PREF_USER,
	PREF_SERVER
} pT;



class Parcer{
	public:
		Parcer(std::string message): _message(message){};
		Parcer(const Parcer&other);
		Parcer&operator=(const Parcer&other);
		~Parcer();
		std::string getMessage(std::string message)const;
		std::vector<std::string> customSplit();
		void setPrefixType(pT &prefixType);
	private:
		std::string _message;
		pT _prefixType;
	
};

#endif