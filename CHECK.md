TODO:


1) check the consistency of the parameters returned in the classes derived from AParcerResult.
      should I return a vector with the whole command  --> vector<string> vec = {"JOIN", "#channel"};
                                                                              OR
      only a vector ONLY with command params           --> vector<string> vec = {"#channel"};


2) Should I include +I exception for MODE?

3) vprintf - NO EXISTE EN c++98 !!!!!


DONE:
 -  Create a purely virtual function setParams() in AParcerResult, and then redefine it in every derived class:
      void setParamas(std::vector<std::string> commandMessage) = 0;

 - Finish defining ParcerResultUser class

 - specialChars - check how can i apply std:string find() function,
      instead of else if. (in ParcerResultUser.cpp ParcerResultNick.cpp ParcerResultJoin.cpp )