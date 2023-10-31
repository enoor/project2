/* Class Theatre defines a Theatre object which stores information about
* one specific theatre, its location and its plays. The class utilizes another
* class Play in order to store the information relevant to the plays.
*
* <name>      : string - name of the theatre
* <town>      : string - the town of operation
* <plays>     : vector<Play> - a vector of Play objects related to this theatre
*
* Program authors
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

#ifndef THEATER_HH
#define THEATER_HH
#include <iostream>
#include <play.hh>
#include <map>
#include <vector>

class Theatre
{
public:
    Theatre(std::string name,
            std::string town,
            std::vector<Play> plays);

    Theatre();

    // Get details about theatre
    std::string get_name() const;
    std::string get_town() const;
    std::vector<Play> get_plays() const; // get all plays
    Play get_play(std::string play_name); // get a specific play

    void put_play(Play& new_play);
    void put_actor_in_play(std::string actor, std::string play_name);
    void update_seats_in_play(int new_seats, std::string play_name);

private:
    std::string name_;
    std::string town_;
    std::vector<Play> plays_;

};

#endif // THEATER_HH
