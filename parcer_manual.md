**-------A WORD ABOUT COMMAND DISPATCHER-------** </br>
The AParcerResult * _parcerResult is an attribute of the class CommandDispatcher.</br>
This class checks whether the input command is valid, and launches a parcing process</br>
depending on the command that entered, and fills AParcerResult *result variable with the address</br>
of the object of a class derived from AParcerResult.</br>

Every derived class has similar content, but as far as all commands are different,</br>
the attributes and methods of classes also differ, and should be implemented</br>
and processes differently.</br>

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
which is named always using the same "logic": vector<string> _commandParamsVec,
so that the elements of the command were kept in this vector.</br>

    Note that,  "INVITE" is not included in the _inviteParamsVec, because we already have the info about the command type in the base class (_command, getCommand());
    Example:
        **INVITE NickName #channelName** --> _inviteParamsVec = {"NickName", "#channelName"}

    Note that, if the command contains only 1 element, the class will still have it as an array, containing only 1 element.
    Example:
       **PASS 1234** --> _passParamsVec = {"1234"}
        
**-------------PASS------------** </br>
        |-------------------|</br>
        | PASS `<password>` |</br>
        |-------------------|</br>
Every user registration starts with the PASS command.
As mentioned before, PASS command has no other parameters than <password>.

We check the number of command parameters in the dispatchPass itself.
If there are more than 1 parameter, the dispatchPass returns ERR_NEEDLESSPARAMS,
if there are no parameters, the dispatchPass returns ERR_NEEDMOREPARAMS.
If the parcing went well, dispatchPass return 0;

The server doesn't have to send any reply after this command to the client, because
users registration hasn't been finished yet.

The _parcerResult pointer will keep and address of the PassParcerResult object,
with a vector containing password.

I tried to avoid  getter "getPassword" because of the security considerations.
To get the password for verification, you will have to get the vector through getPassParams,
and access its first element.


**-------------NICK------------** </br>
        |-------------------|</br>
        | NICK `<nickname>` |</br>
        |-------------------|</br>
After password verification, the user will have to introduce the command NICK
to set the nickname that they will use for this network.
There is set of restrictions for setting a nickname. We check them in the method
isvalidNickname().

<pre> ``` Important notes: isValidNickName() used! ``` </pre>
**isValidNickName() used!**

**-------------KICK------------** </br>
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
**-----------------------------**

