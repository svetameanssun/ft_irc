AParcerResult *result is a variable that will keep the address of</br>
the object of a class derived from AParcerResult.</br>

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
</br>
There are 2 pure virtual functions:</br>
- virtual void printResult() const = 0;
- virtual void setParams(std::vector<std::string> commandMessage) = 0;
Pure virtual functions are not defined in AParcerResult,</br>
I had to define them in every derived class, because depending on the attributes of the derived class,</br>
these 2 methods can vary.</br>

There is only 1 attrubute of the base class -> string _command, which can be accessed through getCommand.</br>
It comntains the name of the command, the  result of which is being kept in the AParcerResult * _parcerResult;</br>

**-------A WORD ABOUT COMMAND DISPATCHER-------** </br>
The AParcerResult * _parcerResult is an attribute of the class CommandDispatcher.</br>
This class checks whether the input command is valid, and launches a parcing process</br>
depending on the command that entered.</br>

**-------------PASS------------** </br>

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

