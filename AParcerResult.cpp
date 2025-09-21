#include "AParcerResult.hpp"

cosnt std::vector<std::string> ParcerResultJoin::stringToVec(std::string &str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while(getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

cosnt std::map<std::string, std::string> ParcerResultJoin::stringsToMap(std::string keyString, std::string valueString) {
    std::vector<std::string> keyVec = stringToVec(keyString);
    std::vector<std::string> valueVec = stringToVec(valueString);
    std::map <std::string, std::string> resMap;
    std::vector<std::string>::iterator it1;
    std::vector<std::string>::iterator it2;
    it2 = valueVec.begin();
    for(it1 = keyVec.begin(); it1 != keyVec.end(); it1++) {

        if (it2->empty()){
            resMap[*it1] = "";
        } else {
            resMap[*it1] = *it2;
        }
        it2++;
    }
    return(resMap);
}