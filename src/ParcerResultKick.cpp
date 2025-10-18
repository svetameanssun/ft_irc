#include "ParcerResultMode.hpp"

/*For the message to be syntactically correct, there MUST be
   either one channel parameter and multiple user parameter, 
   Ex: KICK channel person1 person2 person3 ...
 
   or as many channel parameters as there are user parameters.
   Ex: KICK channel person
   
   If a "comment" is given, this will be sent instead of the default message,
   the nickname of the user issuing the KICK.
 */