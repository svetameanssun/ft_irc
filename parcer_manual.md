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
- bool isValidChanName(string chanName)
-    and its helper, bool isValidChanNameChar(int i);
    
   There are   are 2 pure virtual functions:</br>
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

Note that,  "INVITE" is not included in the _inviteParamsVec, because we already have the info about the command type in the base class (_command, getCommand());</br>

    Example:
        INVITE NickName #channelName --> _inviteParamsVec = {"NickName", "#channelName"}

Note that, if the command contains only 1 element, the class will still have it as an array, containing only 1 element.</br>

    Example:
        PASS 1234 --> _passParamsVec = {"1234"}

**===============================** </br>

**-------------------------------** </br>
**------------- PASS ------------** </br>
**-------------------------------** </br>

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

**-----------------------------------------------** </br>
**----------------------- NICK ------------------** </br>
**-----------------------------------------------** </br>

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
    

<pre>  NB! for Sveta ==> isValidNickName() used!  </pre>
**===============================** </br>

**-----------------------------------------------** </br>
**-------------------- USER ---------------------** </br>
**-----------------------------------------------** </br>

        |------------------------------|
        |USER `<nickname>` `<realname>`|
        |------------------------------|

After PASS and NICK steps, we finally can register our user.
The method dispatchUser checks the parameters with checkUserParams().
If the user's realname complies with the requirements defined in the RFC,
dispatchUser returns 0, else -> ERR_WRONGINPUT (custom error).

The server finally sends a RPL_WELOCME to the client, if the registration was successful!

The _parcerResult pointer will keep an address of the UserParcerResult object,
with a vector containing 3 elements:
- a string with a nickname.
- a string with a realname.
- a rudimantary attribute _userParamsVec (if we have theprevious 2, we do not need this one).

NB! for Ruben ==>

    You will have to check, whether the _nickname of the ParcerResultUser class coincides with other users on the server,
    and if it happens to be like that, send the error ERR_ALREADYREGISTRED.

NB! for Sveta ==>

    USER stitovsk42 :Svetlana Leonidovna Titovskaia <- fullname accepted  
    USER stitovsk42 Svetlana Leonidovna Titovskaia <- only firstname 'Svetlana' is accepted

**===============================** </br>


**-----------------------------------------------** </br>
**-------------------- JOIN ---------------------** </br>
**-----------------------------------------------** </br>

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
    It will contain 3 attributes:
    - bool leaveAllChansOn, which will infrom if the user wants to leave all channels.
    - std::vector <std::string> _joinParamsVec, which just hase a vector with the JOIN parameters
    - std::map<std::string, std::string> _joinParamsMap, which has a map with channel(key) - password(value) pair.


NB! for Sveta ==>
    HOW DO YOU CONTROL THE REPEATED CHANNELNAMES???? YOU DO NOT!!!!
    
**===============================** </br>






**-----------------------------------------------** </br>
**--------------------- KICK --------------------** </br>
**-----------------------------------------------** </br>
I pass a map<int, vector<string>> to the command pointer.</br>
The int — to make it easier to handle — and the vector (of 2 elements)</br>
stores which channel I perform the KICK to and which I kick.</br>

**EXAMPLE**</br>
From this command:</br> 
KICK #channel person1,person2, person3</br>

We get this map:</br>
{</br>
    0: ["#channel", "person1"],</br>
    1: ["#channel", "person2"],</br>
    2: ["#channel", "person3"]</br>
}</br>
</br>
**===============================** </br>

