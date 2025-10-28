#include "ParcerResultMode.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParcerResultMode::ParcerResultMode()
    : AParcerResult(){
        _command = "MODE";
}

ParcerResultMode::ParcerResultMode(const ParcerResultMode &other){
    this->_command = other._command;
    this->_modeParamsVec = other._modeParamsVec;
    this->_modeParamsMap = other._modeParamsMap;
}

ParcerResultMode& ParcerResultMode::operator=(const ParcerResultMode& other){
    if(this != &other) {
        this->_modeParamsVec = other._modeParamsVec;
        this->_modeParamsMap = other._modeParamsMap;
        this->_command = other._command;
    }
    return (*this);
}

ParcerResultMode::~ParcerResultMode(){}