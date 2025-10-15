#include "ParcerResultMode.hpp"


/* itkol
---------------------------------------------------------------------
· i: Set/remove Invite-only channel

---------------------------------------------------------------------
· t: Set/remove the restrictions of the TOPIC command to channel operators

---------------------------------------------------------------------
· k: Set/remove the channel key (password)
    MODE #42 +k oulu ;          Command to set the channel key to
                                "oulu".

---------------------------------------------------------------------
· o: Give/take channel operator privilege
    MODE #Finnish +o Kilroy ;   Command to give ’chanop’ privileges
                                to Kilroy on channel #Finnish.
---------------------------------------------------------------------
· l: Set/remove the user limit to channel
    MODE #eu-opers +l 10        Command to set the limit for the
                                number of users on channel
                                "#eu-opers" to 10.
---------------------------------------------------------------------

*/

/* MODE #channel
            the server will return the current modes of that channel: */

