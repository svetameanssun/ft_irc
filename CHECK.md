TODO:

1) TOPIC command - TOPIC #mychan
   in this example, topic message is sent to the client.
   Check how it is handled, because I can assign/check it in ParcerResultTopic,
   but I cannot be sure how the topic is assigned to the channel

3) Make MODE command execute not all the flags at once, but each flag one by one.

4) vprintf - NO EXISTE EN c++98 !!!!!


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
