#include "ParcerResult.hpp"

ParcerResult::ParcerResult(){
}

 void setChannelNamePassMap(std::map<std::string, std::string> joinResMap){
   this->_channelNamePassMap = joinResMap;
 }

void setChannelnameVec(std::vector <std::string> joinResVec){
  this->_channelNameVec = joinResVec;
}

cosnt std::map<std::string, std::string> getChannelNamePassMap(void) const{
  return (_channelNamePassMap);
}

const std::vector <std::string> getChannelNameVec(void) const{
  return (_channelNameVec);
}

ParcerResult::~ParcerResult(){
}
