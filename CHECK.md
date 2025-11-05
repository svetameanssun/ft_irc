TODO:
1) Maybe move isValidNick to AParcerResult?
2) check printResult for every class
3) check and remove all the ':' from the ParcerResult.. parameters
4) CHECK KICK (I am not sure IF the checkKickParams is ACTUALLY corrrect :D)

5) TOPIC command - TOPIC #mychan
   in this example, topic message is sent to the client.
   Check how it is handled, because I can assign/check it in ParcerResultTopic,
   but I cannot be sure how the topic is assigned to the channel

6) Make MODE command execute not all the flags at once, but each flag one by one.

7) vprintf - NO EXISTE EN c++98 !!!!!


DONE:
 -  Create a purely virtual function setParams() in AParcerResult, and then redefine it in every derived class:
      void setParamas(std::vector<std::string> commandMessage) = 0;

 - Finish defining ParcerResultUser class

 - specialChars - check how can i apply std:string find() function,
      instead of else if. (in ParcerResultUser.cpp ParcerResultNick.cpp ParcerResultJoin.cpp )


- checked the consistency of the parameters returned in the classes derived from AParcerResult.
      should I return a vector with the whole command  --> vector<string> vec = {"JOIN", "#channel"};
                                                                              OR
      only a vector ONLY with command params           --> vector<string> vec = {"#channel"};
