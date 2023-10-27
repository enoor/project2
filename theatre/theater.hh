#ifndef THEATER_HH
#define THEATER_HH
#include <iostream>
#include <map>
#include <set>

struct Play {
    std::string name = "";
    std::set<std::string> actors = {};
    int available_seats = 0;
};

class Theater
{
public:
    Theater(std::string name,
            std::string town, 
            std::set<Play> plays);
    
    ~Theater();
    
    // Get details about theater
    std::string get_name();
    std::string get_town();
    std::set<Play> get_all_plays(); // TO DO: Essi
    
    void put_play(Play& new_play); // Adds play to theater, if it isn't already listed
    Play get_play(std::string play_name); // get a specific play
    void put_actor(std::string actor, std::string play_name); // Adds actor to specific play, if they aren't already listed
    void update_seats(int new_seats, std::string play_name); // Updates seats of specific play
    
    void print_info(bool name, bool town, bool plays); // TO DO: Essi
    
private:
    std::string name_;
    std::string town_;
    std::set<Play> plays_;
    
};

#endif // THEATER_HH
