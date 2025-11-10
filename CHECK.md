TODO:
1) INVITE - instroduce commands, that are need from Channel and Client classes
2) Maybe move isValidNick to AParcerResult?
3) check printResult for every class
4) check and remove all the ':' from the ParcerResult.. parameters
5) CHECK KICK (I am not sure IF the checkKickParams is ACTUALLY corrrect :D)

6) TOPIC command - TOPIC #mychan
   in this example, topic message is sent to the client.
   Check how it is handled, because I can assign/check it in ParcerResultTopic,
   but I cannot be sure how the topic is assigned to the channel

7) Make MODE command execute not all the flags at once, but each flag one by one.

8) vprintf - NO EXISTE EN c++98 !!!!!


DONE:
 - JOIN
 - KICK
 - PRIVMSG
 - TOPIC
 - USER
 - PASS
 - NICK
 - 
 -  Create a purely virtual function setParams() in AParcerResult, and then redefine it in every derived class:
      void setParamas(std::vector<std::string> commandMessage) = 0;

 - Finish defining ParcerResultUser class

 - specialChars - check how can i apply std:string find() function,
      instead of else if. (in ParcerResultUser.cpp ParcerResultNick.cpp ParcerResultJoin.cpp )


- checked the consistency of the parameters returned in the classes derived from AParcerResult.
      should I return a vector with the whole command  --> vector<string> vec = {"JOIN", "#channel"};
                                                                              OR
      only a vector ONLY with command params           --> vector<string> vec = {"#channel"};
