#ifndef THEATER_HH
#define THEATER_HH
#include <iostream>
#include <play.hh>
#include <map>
#include <vector>

class Theater
{
public:
    Theater(std::string name,
            std::string town,
            std::vector<Play> plays);

    Theater();

    // Get details about theater
    std::string get_name() const;
    std::string get_town() const;
    std::vector<Play> get_plays() const;
    Play get_play(std::string play_name); // get a specific play

    void put_play(Play& new_play); // Adds play to theater, if it isn't already listed
    void put_actor_in_play(std::string actor, std::string play_name); // Adds actor to specific play, if they aren't already listed
    void update_seats_in_play(int new_seats, std::string play_name); // Updates seats of specific play

    void print(); // Prints the contents of the object

private:
    std::string name_;
    std::string town_;
    std::vector<Play> plays_;

};

#endif // THEATER_HH
