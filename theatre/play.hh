/* Class Play defines objects containing information about a play and actors
* related to the play. A Play object can have a name and an alias for flexible
* calling. It also stores information about the available seats for the play.
* The Play objects defined by class Play are used inside another class
* "Theatre" to bind them to specific theatres.
*
* <name>             : string - name of the play
* <alias>            : string - alias name of the play
* <actors>           : set<string> - actor or actors involved in the play
* <available_seats>  : int - number of available seats in this play
*
*
* Name: Essi Asunmaa
* Student number: 151876727
* UserID: bmesas
* E-mail: essi.n.asunmaa@tuni.fi
*
* Name: Teemu Syrjala
* Student number: 151461352
* UserID: nrtesy
* E-Mail: teemu.syrjala@tuni.fi
 */

#ifndef PLAY_HH
#define PLAY_HH
#include <iostream>
#include <set>
#include <string>

class Play
{
public:
    Play(std::string name,
         std::string alias,
         std::set<std::string> actors,
         int available_seats);

    ~Play();

    // Get details about play
    std::string get_name() const;
    std::string get_alias() const;
    std::set<std::string> get_actors() const;
    int get_seats() const;

    void update_seats(int new_seats); // Updates available seats
    void add_actor(std::string actor); // Adds actor if they aren't already listed

private:
    std::string name_;
    std::string alias_;
    std::set<std::string> actors_;
    int available_seats_;
};

#endif // PLAY_HH
