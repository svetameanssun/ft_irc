#include "ParcerResult.hpp"
class ParcerResult{
  public:
    ParcerResult();
    ~ParcerResult();
     cosnt std::map<std::string, std::string> stringsToMap(std::string keyString, std::string valueString);
    cosnt std::vector<std::string> stringToVec(std::string string,char devisor);
    void setChannelNamePassMap(std::map<std::string, std::string> joinResMap);
    void setChannelnameVec(std::vector <std::string> joinResVec);
    cosnt std::map<std::string, std::string> getChannelNamePassMap(void) const;
    const std::vector <std::string> getChannelNameVec(void) const;
  private:
    std::map<std::string, std::string> _channelNamePassMap;
    std::vector <std::string> _channelNameVec;
};


ParcerResult::ParcerResult(){
}

cosnt std::vector<std::string> ParcerResult::stringToVec(std::string &str,char delim){
    std::vector<std::string> result;
    std::stringstream ss (str);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
  }
    return result;
}

cosnt std::map<std::string, std::string> ParcerResult::stringsToMap(std::string keyString, std::string valueString){
  std::vector<std::string> keyVec =stringToVec(keyString);
  std::vector<std::string> valueVec = stringToVec(valueString);
  const std::map <std::string, std::string> resMap;
  std::vector<std::string>::iterator it1;
  std::vector<std::string>::iterator it2;
  it2=valueVec.begin();
       for (it1 = keyVec.begin(); it1 != keyVec.end(); it1++)
       {
         
         if (*it2).empty(){
             resMap[*it1] = NULL;
         }
         else
        {
              resMap[*it1] = *it2;
          }
          
         it2++;
       }
   retrun (resMap);

}


 void setChannelNamePassMap(std::map<std::string, std::string> ParcerResult::joinResMap(){
   this->_channelNamePassMap = joinResMap;
 }

void setChannelnameVec(std::vector <std::string> ParcerResult::joinResVec(){
  this->_channelNameVec = joinResVec;
}

cosnt std::map<std::string, std::string> ParcerResult::getChannelNamePassMap(void) const{
  return (_channelNamePassMap);
}

const std::vector <std::string> ParcerResult::getChannelNameVec(void) const{
  return (_channelNameVec);
}

ParcerResult::~ParcerResult(){
}
