#ifndef PARCERRESULT_HPP
#define PARCERRESULT_HPP

#icnlude <map>
#include <vector>
#include <string>


class ParcerResult{
  public:
    ParcerResult();
    ~ParcerResult();
    void setChannelNamePassMap(std::map<std::string, std::string> joinResMap);
    void setChannelnameVec(std::vector <std::string> joinResVec);
    cosnt std::map<std::string, std::string> getChannelNamePassMap(void) const;
    const std::vector <std::string> getChannelNameVec(void) const;
  private:
    std::map<std::string, std::string> channelNamePassMap;
    std::vector <std::string> channelNameVec;
};


#endif
