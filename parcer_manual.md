**-------A WORD ABOUT COMMAND DISPATCHER-------** </br>
The AParcerResult * _parcerResult is an attribute of the class CommandDispatcher.</br>
This class checks whether the input command is valid, and launches a parcing process</br>
depending on the command that entered, and fills AParcerResult *result variable with the address</br>
of the object of a class derived from AParcerResult.</br>

Every derived class has similar content, but as far as all commands are different,</br>
the attributes and methods of classes also differ, and should be implemented</br>
and processed differently.</br>

So here I leave a short description for each class and its attributes,</br>
with examples.</br>

**-------COMMON FEATURES-------** </br>
Obvously, all the subclasses will share the methods and attributes of their base class.</br>
The base class AParcerResult methods that can be accessed through derived classes are:</br>
- getCommand();
- bool isValidChanName(string chanName)</br>
     </tab>and its helper, bool isValidChanNameChar(int i);
- bool isValidNick(string nickname)</br>
     </tab>and its helper, bool isSpecialChar(int i);
    
There are 2 pure virtual functions:</br>
- virtual void printResult() const = 0;
- virtual void setParams(std::vector<std::string> commandMessage) = 0;

Pure virtual functions are not defined in AParcerResult,</br>
I had to define them in every derived class, because depending on the attributes of the derived class,</br>
these 2 methods can vary.</br>

There is only 1 attrubute of the base class -> string _command, which can be accessed through getCommand.</br>
It comntains the name of the command, the  result of which is being kept in the AParcerResult * _parcerResult;</br>

Every subclass, in its turn, has a vector of parameters,
which is named ALMOST always using the same "logic": vector<string> _*command*ParamsVec,
so that the elements of the command were kept in this vector.</br>
The getter of the parameters is also almost always is called "get*Command*Params". </br>
</tab>**EXCEPTION: getNikcname in ParcerResultNick** </br>

Note that,  "INVITE" is not included in the _inviteParamsVec, because we already have the info
about the command type in the base class (_command, getCommand());</br>

    Example:
        INVITE NickName #channelName --> _inviteParamsVec = {"NickName", "#channelName"}

Note that, if the command contains only 1 element, the class will still have it as an array, containing only 1 element.</br>

    Example:
        PASS 1234 --> _passParamsVec = {"1234"}

**===============================** </br>

**----------------------------------------------------** </br>
**------------- PASS ---------------------------------** </br>
**----------------------------------------------------** </br>

        |--------------------|
        |  PASS `<password>` |
        |--------------------|

Every user registration starts with the PASS command.
As mentioned before, PASS command has no other parameters than <password>.

We check the number of command parameters in the dispatchPass itself.
If there are more than 1 parameter, the dispatchPass returns ERR_NEEDLESSPARAMS,
if there are no parameters, the dispatchPass returns ERR_NEEDMOREPARAMS.
If the parcing went well, dispatchPass return 0;

The server doesn't have to send any reply after this command to the client, because
users registration hasn't been finished yet.

The _parcerResult pointer will keep an address of the PassParcerResult object,
with a vector containing password.

I tried to avoid  getter "getPassword()" because of the security considerations.
To get the password for verification, you will have to get the vector through *getPassParams()*,
and access its first element.

NB! for Ruben ==>
    I have NO IDEA how you will process this =D

**===============================** </br>

**----------------------------------------------------** </br>
**----------------------- NICK -----------------------** </br>
**----------------------------------------------------** </br>

        |--------------------|
        |  NICK `<nickname>` |
        |--------------------|
        nickname = ( letter / special ) *8( letter / digit / special / "-" )
        special = %x5B-60 / %x7B-7D; "[", "]", "\", "‘", "_", "^", "{", "|", "}"

After password verification, the user will have to introduce the command NICK
to set the nickname that they will use for this network.
There is set of restrictions for a nickname.  In the method *isValidNickName()*,
we verify if the nickname introduced by the user is valid. </br>

    nickname = ( letter / special ) *8( letter / digit / special / "-" )

The number of paramters is checked in the dispatchNick method.
If there are no parameters given, the dispatchPass returns ERR_NONICKNAMEGIVEN,
if the command has more than 1 parameter, it returns a CUSTOM error -> ERR_NEEDLESSPARAMS (custom error)
If the parcing went well, dispatchPass returns 0;

The server doesn't have to send any reply after this command to the client, because
users registration hasn't been finished yet.

The _parcerResult pointer will keep an address of the NickParcerResult object,
with a vector containing only one element -> a string with a nickname.

YES! I tried to improvise and instead of the common vector _nickParamsVec,
I just used just a string which will contain the nickname -> _nickname,
and its getter -> *getNickname()*.


NB! for Ruben ==>

    "NICK command is used to give user a nickname or change the existing one."
    So, if the client sending this command is a new user -> you have to create a new client.
    If this command is sent by already existing client -> you have to change the client's _nickname
    

**===============================** </br>

**----------------------------------------------------** </br>
**-------------------- USER --------------------------** </br>
**----------------------------------------------------** </br>

        |------------------------------|
        |USER `<nickname>` `<realname>`|
        |------------------------------|

After PASS and NICK steps, we finally can register our user.
The method dispatchUser checks the parameters with checkUserParams().
If the user's realname complies with the requirements defined in the RFC,
dispatchUser returns 0, else -> ERR_WRONGINPUT (custom error).

The server finally sends a RPL_WELOCME to the client, if the registration was successful!

The _parcerResult pointer will keep an address of the UserParcerResult object,
with a vector containing 3 attributes:
- a string with a nickname.
- a string with a realname.
- a rudimantary attribute _userParamsVec (if we have the previous 2, we do not need this one).

NB! for Ruben ==>

    You will have to check, whether the _nickname of the ParcerResultUser class coincides with other users on the server,
    and if it happens to be like that, send the error ERR_ALREADYREGISTRED.

NB! for Sveta ==>

    USER stitovsk42 :Svetlana Leonidovna Titovskaia <- fullname accepted  
    USER stitovsk42 Svetlana Leonidovna Titovskaia <- only firstname 'Svetlana' is accepted

**===============================** </br>


**----------------------------------------------------** </br>
**-------------------- JOIN --------------------------** </br>
**----------------------------------------------------** </br>

    |-----------------------------------------------------------------------------| 
    |  JOIN                                                                       |
    | Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] ) / "0" |
    |-----------------------------------------------------------------------------| 
    
Now we have a user, and they can finally join some channels.
This command is quite tricky to handle, because it may have various parameter combinations.
    
First, we check the number of command parameters in the dispatchJoin itself.
    
The method dispatchJoin uses checkJoinParams() to (guesss what???) check if the parameters of join are correct!
If everything is OK -> the dispatchJoin returns 0, else -> it returns the kind of error that has been detected: ERR_NOSUCHCHANNEL,ERR_NEEDLESSPARAMS(custom error) or ERR_WRONGINPUT(custom error).
    
The _parcerResult pointer will keep an address of the JoinParcerResult object.
It will contain 4 attributes:
    - bool leaveAllChansOn, which is TRUE if the user wants to leave all channels;
    - vector <string> _joinParamsVec, which will contain raw join parameters (only channel(s) or channel(s) with password(s);
    - vector <string> _joinChannelsVec, which will contain an array of channel names.
    - vector <string> _joinPasswordsVec, which will contain an array of passwords to the channels.
    
First I wanted to make a channel-password map, but I abandoned this idea,
because it doesn´t take the repeated channels into consideration. We will just have to access _joinChannelsVec[i],
and check, if _joinPasswordsVec[i] exists, or the password is not right.

NB! for Ruben ==></br>
</tab>If the flag leaveAllChans is activated (== true), the given client has to leave all the channels he/she belongs to.</br>
</tab>If this flag is not activated, then the client wants INDEED join the channel(s).</br>
What can become an obstacle on their way of joining a channel?</br>
- It may be an invite only channel! We will have to send back ERR_INVITEONLYCHAN error;
- The channel might be full! Oh, no! We will have to notify the client by sending them ERR_CHANNELISFULL error;
- The user might be on too many channels! (greedy bastard)! We have to politely put our limits to their outragious behaviour, sending the ERR_TOOMANYCHANNELS error;
- The user uses a wrong password, then... (I have not find anywhere what happens then!)
If you cannot find the channel in the existing channels -> you have to create a new channel with the given name, and make the user its operator.
     
    NB! for Ruben and Sveta ==>

      Some questions, left with no answer:
        if there is a list of channels given, should the user be able to join other channels on the list?
        Or the joining process stops, if there is a problem only with one channel?

        What is the error returned to the client, if the password does not match???

        "If a JOIN is successful, the user receives a JOIN message as
         confirmation and is then sent the channel’s topic (using RPL_TOPIC) and
         the list of users who are on the channel (using RPL_NAMREPLY)"
         It is an excerpt from the rfc, I do not quite understand, how it should be handled.
    
**===============================** </br>


**----------------------------------------------------** </br>
**------------------- INVITE -------------------------** </br>
**----------------------------------------------------** </br>

        |----------------------------------|
        |  INVITE `<nickname>` `<channel>` |
        |----------------------------------|

Our users not only can join the channels by themsleves, but also can be invited!
The checkInviteParams() method within dispatchInvite() is quite simple:
I can only check the number of parameters, and whether the nickname is on its place. 
Thus, dispatchInvite returns 0 if everything is OK,
or ERR_NEEDMOREPARAMS, ERR_NEEDLESSPARAMS, ERR_NOSUCHNICK.

Because of this line in RFC2812, I do not check channel parameter ->
	"There is no requirement that the channel,
	the target user is being invited to,
	must exist or be a valid channel."

The _parcerResult pointer will keep an address of the InviteParcerResult object.
It will contatin only one private attribute: **vector <string> _inviteParamsVec**

	NB! for Ruben ==></br>
	The main work in this command is left for you!
	You have to check that:
		- The inviting party belongs to the channel, the target is being invited to,
		- If the channel has the invite-only flag set, only a channel OPER can invite new users to the channel.
	

I have drafted some code that might serve (or might be not!) as a prototype for your code:</br>
	Given that</br>
	vector <string> messageVec = INVITE `<nickname>` `<channel>`,</br>
	and</br>
	string myName equals the name of the sender of the command,</br>
	then:</br>
	
	if (!userOnChannel(myName, channelName)){ // bool userOnChannel(std::stirng myName, std::string channelName) (not sure about parameters)
		return(ERR_NOTONCHANNEL);
	}
	if (inviteFlagOn() && !iAmOperator()){ //  bool inviteFlagOn(); bool iAmOperator();
			return (ERR_CHANOPRIVSNEEDED);
	}	
	if (!userExists(messageVec[1])){  // bool userExists(std::string userName).
		return (ERR_NOSUCHNICK);
	}
	if (userOnChannel(messageVec[1], channelName)) // same as the ast one{
		return (ERR_USERONCHANNEL);
	}

NB! for Sveta and Ruben ==></br>
RFC2812 -> "Only the user inviting and the user being invited will receive notification of the invitation."

**===============================** </br>

**-----------------------------------------------** </br>
**--------------------- KICK --------------------** </br>
**-----------------------------------------------** </br>

    |-----------------------------------------------------------------------------| 
    |  KICK                                                                       |
    | Parameters: <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>] |
    |-----------------------------------------------------------------------------| 
 
If a user can join, and be invited to a channel,
we have to be able to KICK THEM OUT of the channel !!!
This command, as well as join, can have different parameter combinaions.

We check the number of parameters with checkKickParams within dicpatchKick.
We also check whether the channel name(s) and the user name(s) is/are valid (needlessly, indeed).
If everything is OK -> the dispatchKick returns 0, else -> it returns the kind of error that has been detected:
- ERR_NOSUCHCHANNEL -> when the channel name is not valid,
- ERR_NEEDLESSPARAMS(custom error),
- ERR_NEEDMOREPARAMS,
- (ERR_UNKNOWNCOMMAND) -> when the nickname is not valid.

The _parcerResult pointer will keep an address of the KickParcerResult object.
It will contain 5 attributes:
    - vector <string> _kickParamsVec, a raw kick parameters 
    - vector <string> _kickChannelsVec, an array of channel names,
    - vector <string> kickUsersVec, an array of users names,
    - map<int, vector<string>> _kickParamsMap,  with this structure → [index] = {channel, user},
    - string _kickComment;  -> optional trailing comment.

From this command:
    KICK channel name1,name2,name3
We get this map:</br>
{</br>
    0: ["#channel", "name1"],</br>
    1: ["#channel", "name2"],</br>
    2: ["#channel", "name3"]</br>
}</br>
And from this command:
    KICK channel,channel2,channel3 name1,name2,name3
We get this map:</br>
{</br>
    0: ["#channel", "name1"],</br>
    1: ["#channe2", "name2"],</br>
    2: ["#channe3", "name3"]</br>
}</br>
Thus, the most IMPORTANT attributes are _kickParamsMap and _kickComment,
the latter being a string that needs to be printed in the message.

    NB! for Ruben ==>
    You will have to check:
        - if the channel actually exists, if not -> ERR_NOSUCHCHANNEL
        - if the user, who is being kicked out (target), is on the channel. If not -> ERR_USERNOTINCHANNEL
        - if the user, who is kicking out, is on channel. If not -> ERR_NOTONCHANNEL.
        - if the user, who is kicking out, is the OPER of the channel, if not -> ERR_CHANOPRIVSNEEDED
        
                                
NB! for Sveta and Ruben ==>
    If the command if successful, these 2 types of messages should be sent:
         "Command to kick name1 from channel1 using "a very compelling reason" as the reason (comment).",
             if the comment is given.
         "Command to kick name1 from channel1.",
             if no comment is given
        
             
</br>
**===============================** </br>

**-----------------------------------------------** </br>
**-------------------- PRIVMSG ------------------** </br>
**-----------------------------------------------** </br>

    |------------------------------------------| 
    |  PRIVMSG  <msgtarget> <text to be sent>  |
    |------------------------------------------|
		-->msgtarget = msgto *( "," msgto )<--

It is time to send messages! With PRIVMSG you can send a message
to another users, as well as to the channels.

	Examples:
		PRIVMSG userA :hello, userA!
		PRIVMSG userA,userB,channelC,serverD :Hello everybody!
		
We check the PRIVMSG parameters with checkPrivmsgParams within dicpatchPrivmsg.
We check the first parameter of the command PRIVMSG.
If everything is OK -> the dispatchPrivmsg returns 0, else -> it returns the kind of error that has been detected:
- ERR_NORECIPIENT -> if there are no parameters,
- ERR_NOTEXTTOSEND -> if there is no message to send,
- ERR_WRONGINPUT(custom command) -> if the targetname is not a channel, nor a user.

The _parcerResult pointer will keep an address of the PrivmsgParcerResult object.
It will contain 3 attributes:
    - vector <string> _privmsgParamsVec -> a raw privmsg parameter vector,
    - vector <string> _targetVec-> a vector with all the targets we need to send a message,
    - string _privmsgMessage -> the message to be sent to the target/targets.

	NB! for Ruben ==>
		The only thing left to do (as if it were not much!) is to actually send the message the target or targets.
		What can go wrong??
		- ERR_NOSUCHNICK -> 
					If a nick from _targetVec do not exist in the network 
		- ERR_CANNOTSENDTOCHAN -> 
					If the sender is not on a channel.
		- ERR_TOOMANYTARGETS ->
					I do not know how many targets are too many targets!
						I check the maximum length of the message (512 letters), and maximum number of parameters(15).
						But here we are talking about the 1st parameter of the command PRIVMSG.
						I have not found anywhere what is allowed number of targets.
		
</br>
**===============================** </br>

**-----------------------------------------------** </br>
**--------------------- NOTICE ------------------** </br>
**-----------------------------------------------** </br>

Quote from RFC2812:

	"The NOTICE command is used similarly to PRIVMSG. The difference
 	between NOTICE and PRIVMSG is that automatic replies MUST NEVER be
 	sent in response to a NOTICE message. This rule applies to servers
	too - they MUST NOT send any error reply back to the client on
 	receipt of a notice. The object of this rule is to avoid loops
 	between clients automatically sending something in response to
 	something it received.
 	This command is available to services as well as users.
 	This is typically used by services, and automatons (clients with
 	either an AI or other interactive program controlling their actions).
 	See PRIVMSG for more details on replies and examples."

For me, it meant that I just had to copy/paste all the parcing logic.</br>
For you (Ruben), it means(I think) that we do not send anything(nor error, nor reply) to the user,</br>
even if the command was wrong.

The _parcerResult pointer will keep an address of the NoticeParcerResult object.
It will contain 3 attributes:
    - vector <string> _noticeParamsVec -> a raw notice parameter vector,
    - vector <string> _targetVec-> a vector with all the targets we need to send a message,
    - string _noticeMessage -> the message to be sent to the target/targets.

</br>
**===============================** </br>

**-----------------------------------------------** </br>
**---------------------- PART -------------------** </br>
**-----------------------------------------------** </br>

    |-----------------------------------------------------------------------------| 
    |  PART                                                                       |
    | Parameters: <channel> *( "," <channel> ) [<Part Message>]                   |
    |-----------------------------------------------------------------------------| 

A user should be able to leave any channel whenever they please, right?
Mash Alah (thanks God), there is a special command for this! -> PART




































