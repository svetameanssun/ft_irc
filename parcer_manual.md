AParcerResult *result is a variable that will keep the address of
the object of a class derived from AParcerResult.

Every derived class has similar content, but as far as all commands are different,
the attributes and methods of classes also differ, and should be implemented
and processes differently.

So here I leave a short description for each class and its attributes,
with examples.

**-------COMMON FEATURES-------** </br>
Obvously, all the subclasses will share the methods and attributes of their base class.
The base class AParcerResult methods that can be accessed through derived classes are:
        - getCommand();
        - bool isValidChanName(string chanName)
        -    and its helper, bool isValidChanNameChar(int i);
There are 2 pure virtual functions:
        - virtual void printResult() const = 0;
        - virtual void setParams(std::vector<std::string> commandMessage) = 0;
Pure virtual functions are not defined in AParcerResult,
I had to define them in every derived class, because depending on the attributes of the derived class,
these 2 methods can vary.

There is only 1 attrubute of the base class -> string _command, which can be accessed through getCommand.
It comntains the name of the command, the  result of which is being kept in the AParcerResult * _parcerResult;

**-------A WORD ABOUT COMMAND DISPATCHER-------** </br>
The AParcerResult * _parcerResult is an attribute of the class CommandDispatcher.
This class checks whether the input command is valid, and launches a parcing process
depending on the command that entered.

**-------------PASS------------** </br>

**-------------KICK------------** </br>
I pass a map<int, vector<string>> to the command pointer. The int — to make it easier to handle — and the vector (of 2 elements) stores which channel I perform the KICK to and which I kick.

**EXAMPLE**</br>
From this command: 
KICK #channel person1,person2, person3

We get this map:
{
    0: ["#channel", "person1"],
    1: ["#channel", "person2"],
    2: ["#channel", "person3"]
}
</br>
**-----------------------------**

