#include "AParcerResult.hpp"

AParcerResult::AParcerResult(){};

AParcerResult::AParcerResult(std::string command){
    this->_command = command;
}

AParcerResult::AParcerResult(const AParcerResult &other){
    this->_command = other._command;
};

AParcerResult& AParcerResult::operator=(const AParcerResult& other){
    if (this != &other)
    {
        this->_command = other._command;
    }
    return (*this);
}

std::string AParcerResult::getCommand()const{
    return (_command);
}
