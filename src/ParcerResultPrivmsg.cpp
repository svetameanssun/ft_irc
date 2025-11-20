#include "ParcerResultPrivmsg.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParcerResultPrivmsg::ParcerResultPrivmsg()
    : AParcerResult(){
        _command = "PRIVMSG";
}

ParcerResultPrivmsg::ParcerResultPrivmsg(const ParcerResultPrivmsg &other){
    this->_command = other._command;
    this->_privmsgParamsVec = other._privmsgParamsVec;
    this->_targetVec = other._targetVec;
}

ParcerResultPrivmsg& ParcerResultPrivmsg::operator=(const ParcerResultPrivmsg& other){
    if(this != &other) {
        this->_privmsgParamsVec = other._privmsgParamsVec;
        this->_targetVec = other._targetVec;
        this->_command = other._command;
    }
    return (*this);
}

ParcerResultPrivmsg::~ParcerResultPrivmsg(){}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParcerResultPrivmsg::setParams(std::vector<std::string> privmsgCommand) {
  if (!privmsgCommand.empty()) {
    privmsgCommand.erase(privmsgCommand.begin());  // drop the first element, which is the command
  }
  this->_privmsgParamsVec = privmsgCommand;
}

const std::vector<std::string> ParcerResultPrivmsg::getPrivmsgParams(void) const {
  return (this->_privmsgParamsVec);

/*==========================================================*/
/*----------------------------------------------------------*/
/*                        SPLIT                             */
/*----------------------------------------------------------*/
const std::vector<std::string> ParcerResultJoin::stringToVec(std::string str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while(getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                       S_VALID_PARAM                      */
/*----------------------------------------------------------*/
int ParcerResultPrivmsg::checkPrivmsgTarget(std::string privmsgTarget){
    std::vector <string> targetVec;
    targetVec = stringToVec(privmsgTarget, ',');
    for (string elem : targetVec){
        if (!isValidChanName(elem) && !isValidNick(elem)){
            return (ERR_WRONGINPUT);
        }
        else{
            this->_targetVec.push_back(elem);
        }
    }
    return (0);
}

int ParcerResultTopic::checkPrivmsgParams(std::vector <std::string> messageVector){
    if (messageVector.size() == 1 ){
        return (ERR_NORECIPIENT);
    }
    if (messageVector.size() == 2 ){
        return (ERR_NOTEXTTOSEND);
    }
    if (messageVector[2][0] != ':'){
        this->_privmsgMessage = messageVector[2]; 
    }
    else{
        for (int i = 2; i < messageVector.size(); ++i){
            this->_privmsgMessage += messageVector[i];
        }
        this->_privmsgMessage.erase(0, 1); // It removes the 1st char
                                            // (which in this case is ':')
    }
    int res = checkPrivmsgTarget(messageVector[1]);
    if (res > 0){
        return res;
    }
    return (res);
}
/*==========================================================*/

/*
Privmsg
The command mIRC use when you are chatting in channels and queries.

privmsg <target> :<message>
<target> is where you want the message to end up. Can be multiple targets if you seperate them with a , (comma).
<message> needs to be prefixed with a : (semicolon),
!!!!!!------> OTHERWISE the IRC server will only take the first word after target. <------ !!!!!!!
1 Private messages
 Command: PRIVMSG
 Parameters: <msgtarget> <text to be sent>
 PRIVMSG is used to send private messages between users, as well as to
 send messages to channels. <msgtarget> is usually the nickname of
 the recipient of the message, or a channel name.
 The <msgtarget> parameter may also be a host mask (#<mask>) or server
 mask ($<mask>). In both cases the server will only send the PRIVMSG
 to those who have a server or host matching the mask. The mask MUST
 have at least 1 (one) "." in it and no wildcards following the last
 ".". This requirement exists to prevent people sending messages to
 "#*" or "$*", which would broadcast to all users. Wildcards are the
 ’*’ and ’?’ characters. This extension to the PRIVMSG command is
 only available to operators.

Numeric Replies:
 ERR_NORECIPIENT
 ERR_NOTEXTTOSEND
 ERR_CANNOTSENDTOCHAN
 ERR_NOTOPLEVEL
 ERR_WILDTOPLEVEL
 ERR_TOOMANYTARGETS
 ERR_NOSUCHNICK
 RPL_AWAY


 Examples:
 /privmsg Dana,#help.script :How are you?                It will send "How are you?"
                                                         to both Dana and #help.script,
                                                         from https://script.quakenet.org/wiki/Privmsg
 :Angel!wings@irc.org PRIVMSG Wiz :Are you receiving this message ?
                                                         Message from Angel to Wiz.
 PRIVMSG Angel :yes I’m receiving it !
                                                         Command to send a message to Angel.
 PRIVMSG jto@tolsun.oulu.fi :Hello !
                                                         Command to send a message to a user
                                                         on server tolsun.oulu.fi with
                                                         username of "jto".
 PRIVMSG kalt%millennium.stealth.net@irc.stealth.net :Are you a frog?
                                                         Message to a user on server
                                                         irc.stealth.net with username of
                                                        "kalt", and connected from the host
                                                         millennium.stealth.net.
 PRIVMSG kalt%millennium.stealth.net :Do you like cheese?
                                                        Message to a user on the local
                                                        server with username of "kalt", and
                                                        connected from the host
                                                        millennium.stealth.net.
 PRIVMSG Wiz!jto@tolsun.oulu.fi :Hello !
                                                         Message to the user with nickname
                                                         Wiz who is connected from the host
                                                         tolsun.oulu.fi and has the username
                                                         "jto".
 PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.
                                                         Message to everyone on a server
                                                         which has a name matching *.fi.
 
 PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions
                                                         Message to all users who come from
                                                         a host which has a nam

*/
