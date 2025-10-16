#include "ParcerResultMode.hpp"


/*The channel operators (also referred to as a "chop" or "chanop") on a
   given channel are considered to 'own' that channel.  Ownership of a
   channel is shared among channel operators.

   Channel operators are identified by the '@' symbol next to their
   nickname whenever it is associated with a channel (i.e., replies to
   the NAMES, WHO and WHOIS commands).

   Since channels starting with the character '+' as prefix do not
   support channel modes, no member can therefore have the status of
   channel operator.
*/


/* itkol
---------------------------------------------------------------------
· i: Set/remove Invite-only channel
   When the channel flag 'i' is set, new members are only accepted if
   their mask matches Invite-list (See section 4.3.2) or they have been
   invited by a channel operator.  This flag also restricts the usage of
   the INVITE command (See "IRC Client Protocol" [IRC-CLIENT]) to
   channel operators.
   MODE Angel +i

---------------------------------------------------------------------
· t: Set/remove the restrictions of the TOPIC command to channel operators

---------------------------------------------------------------------
· k: Set/remove the channel key (password)
    MODE #42 +k oulu ;          Command to set the channel key to
                                "oulu".

---------------------------------------------------------------------
· o: Give/take channel operator privilege
    MODE #Finnish +o Kilroy ;   Command to give ’chanop’ privileges
    MODE WiZ -o                            to Kilroy on channel #Finnish.
---------------------------------------------------------------------
· l: Set/remove the user limit to channel
    MODE #eu-opers +l 10        Command to set the limit for the
                                number of users on channel
                                "#eu-opers" to 10.
---------------------------------------------------------------------

*/

/* MODE #channel
            the server will return the current modes of that channel: */

