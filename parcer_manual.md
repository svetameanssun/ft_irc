AParcerResult *result is a variable that will keep the address of
the object of a class derived from AParcerResult.

Every derived class has similar content, but as far as all commands are different,
the attributes and methods of classes also differ, and should be implemented
and processes differently.

So here I leave a short description for each class and its attributes,
with examples.

**----------- KICK -----------** </br>
I pass a map<int, vector<string>> to the command pointer. The int — to make it easier to handle — and the vector (of 2 elements) stores which channel I perform the KICK to and which I kick.

**EXAMPLE**
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

