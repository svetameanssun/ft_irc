#include "ParserResultMode.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParserResultMode::ParserResultMode()
    : AParserResult(){
        _command = "MODE";
}

ParserResultMode::ParserResultMode(const ParserResultMode &other): AParserResult(){
    this->_command = other._command;
    this->_modeFlagsStr = other._modeFlagsStr;
    this->_modeParamsVec = other._modeParamsVec;
}

ParserResultMode& ParserResultMode::operator=(const ParserResultMode& other){
    if(this != &other) {
        this->_modeParamsVec = other._modeParamsVec;
        this->_modeFlagsStr = other._modeFlagsStr;
        this->_command = other._command;
    }
    return (*this);
}

ParserResultMode::~ParserResultMode(){}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/
void ParserResultMode::setParams(std::vector<std::string> modeCommand){
    if (!modeCommand.empty() && modeCommand.size() > 1) {
        modeCommand.erase(modeCommand.begin());  // drop the first element, which is the command itself
    }
    this->_modeParamsVec = modeCommand;
    //I start with i = 1, becase I do not need channel name in my string;
    if (this->_modeParamsVec.size() == 1){
        this->_modeFlagsStr = "";
        return ;
    }
    for (size_t i = 1; i < modeCommand.size(); i++){
        this->_modeFlagsStr += modeCommand.at(i);
        this->_modeFlagsStr += " ";
    }
    if(_modeFlagsStr.at(_modeFlagsStr.length() - 1) == ' '){
		_modeFlagsStr.erase(_modeFlagsStr.length() - 1, 1);
	}

}

const std::vector<std::string> ParserResultMode::getModeParams(void) const{
    return (this->_modeParamsVec);
}

const std::string ParserResultMode::getModeFlagsStr(void) const{
    return (this->_modeFlagsStr);
}

/*==========================================================*/

/*----------------------------------------------------------*/
/*                       IS_VALID...                        */
/*----------------------------------------------------------*/

/*bool ParserResultMode::isValidChanNameChar(int c) {
    if(c == '\0')
        return (false);
    else if(c == '\a')
        return (false);
    else if(c == '\r')
        return (false);
    else if(c == '\n')
        return (false);
    else if(c == ' ')
        return (false);
    else if(c == ',')
        return (false);
    else if(c == ':')
        return (false);
    else {
        return (true);
    }
}*/

/*bool ParserResultMode::isValidChanName(std::string channelName) {
    size_t i = 0;
    if(channelName.empty()) {
        // NOT FORGET EVERYWHERE!
        return false;
    }
    if((channelName.at(0) != '#') && (channelName.at(0) != '&')) {
        std::cout << "THIS\n";
        return (false);
    }
    if((channelName.length() > 200) || (channelName.length() == 1)) {
        return (false);
    }
    i++;
    for(; i < channelName.length(); ++i) {
        if(!isValidChanNameChar(channelName.at(i))) {
            return (false);
        }
    }
    return (true);
}*/

/*bool ParserResultMode::checkFlagCombin(int c, std::vector <std::string> messageVec){

    std::string noParamsFlags = "it\0";
    std::string withParamsFlags = "kol\0";
    if ((withParamsFlags.find(c)) )
    if (c == 'k'  && messageVec.size() != 4){
        return (false);
    }
    if (c == 'o' && messageVec.size() != 4){
        return (false);
    }
    if (c == 'l' && messageVec.size() != 4){
        return (false);
    }
}*/

bool ParserResultMode::isChanFlag(char channelFlag){
    std::string flags = "kolit";
    for (size_t i = 0; i < flags.length() ; i++){
        if (flags.find(channelFlag) == std::string::npos){
            return(false);
        }
    }
    return (true);
}

bool ParserResultMode::hasPlusMinus(std::string channelFlags){
    for (size_t i = 0; i < channelFlags.length() ; i++){
        if (channelFlags.find('+') == std::string::npos && channelFlags.find('-') == std::string::npos){
            return(false);
        }
    }
    return (true);
}

/*Valid combinations of flags (with no parameters)
    +i
    +t
    +it
    +ti
*/

/*With parameters
+k <key>
+o <nick>
+l <limit>
+ko <key> <nick>
+ok <nick> <key>
+kl <key> <limit>
+lk <limit> <key>
+ol <nick> <limit>
+lo <limit> <nick>
+kol <key> <nick> <limit>
+kot <key> <nick>
+itk <key>
+itol <nick> <limit>

(Any order is allowed, as long as parameters follow the same order.)*/


/*bool ParcerResultMode::isValidChanParams(std::vector<std::string> messageVec){
     MODE #channame -flag params 
        0       1       2    3
        itkol
        NO PARAMS:
            i t 
        WITH PARAMS:
            k o l
    
    if (messageVec.at(2).length() > 3){
        return (false);
    }
    std::string flags = messageVec.at(2);
    for (int i = 0; i < flags.length(); ++i){
       if (!checkFlagCombin(flags[i], messageVec))
            return(false);
    }
    //TODO
    return (true);
}*/

/* itkol
---------------------------------------------------------------------
· i: Set/remove Invite-only channel.
    If activated users need to be invited or match a 
    
    should I include this?? -> +I to
              join the channel.
   MODE #Finnish +im             Makes #Finnish channel moderated and
                                'invite-only'.
---------------------------------------------------------------------
· t: Set/remove the restrictions of the TOPIC command to channel operators
   If activated, only opped (+o) users may set the topic.
---------------------------------------------------------------------
· k: Set/remove the channel key (password). Requires users to issue /join #channel KEY to join.
    MODE #42 +k oulu ;          Command to set the channel key to
                                "oulu".
    MODE #channel +k key
---------------------------------------------------------------------
· o: Give/take channel operator privilege
    MODE #Finnish +o Kilroy ;   Command to give ’chanop’ privileges
                                to Kilroy on channel #Finnish.
     -> this is a user mode, not a channel mode! -> MODE WiZ -o
---------------------------------------------------------------------
· l: Set/remove the user limit to channel
    MODE #eu-opers +l 10        Command to set the limit for the
                                number of users on channel
                                "#eu-opers" to 10.
---------------------------------------------------------------------

*/

/*int ParserResultMode::checkModeParams(std::vector<std::string> messageVec){
    if (!isValidChanName(messageVec.at(1))){
        return (ERR_NOSUCHCHANNEL);
    }
    if(!isValidChanFlag(messageVec.at(2))){
        return (ERR_UNKNOWNMODE);
    }
    if(!isValidChanParams(messageVec)){
        return (ERR_UNKNOWNCOMMAND);
    }
    return (0);
}
*/
/*==========================================================*/

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/
void ParserResultMode::printResult() const{
    std::cout << "VECTOR:\n";
    for(std::vector<std::string>::const_iterator itVec = this->_modeParamsVec.begin();
            itVec != this->_modeParamsVec.end(); ++itVec) {
        std::cout << *itVec << "\n";
    }
}
/*==========================================================*/


/* MODE <#/&channel> <-/+flag> [params]*/


/*The channel operators (also referred to as a "chop" or "chanop") on a
   given channel are considered to 'own' that channel.  Ownership of a
   channel is shared among channel operators.

   Channel operators are identified by the '@' symbol next to their
   nickname whenever it is associated with a channel (i.e., replies to
   the NAMES, WHO and WHOIS commands).

   Since channels starting with the character '+' as prefix do not
   support channel modes, no member can therefore have the status of
   channel operator.

   The MODE command is provided so that channel operators may change the
   characteristics of `their' channel.  It is also required that servers
   be able to change channel modes so that channel operators may be
   created.
*/




/* MODE #channel
            the server will return the current modes of that channel: */

