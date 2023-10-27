#ifndef PLAY_HH
#define PLAY_HH
#include <iostream>
#include <set>
#include <string>



class Play
{
public:
    Play(std::string name,
         std::set<std::string> actors,
         int available_seats);

    ~Play();

    // Program behavior for <, so that set functions with class
    bool operator<(const Play& other) const;

    // Get details about play
    std::string get_name() const;
    std::set<std::string> get_actors() const;
    int get_seats() const;

    void update_seats(int new_seats); // Updates available seats
    void add_actor(std::string actor); // Adds actor if they aren't already listed

    void print(); // Prints the contents of the object

private:
    std::string name_;
    std::set<std::string> actors_;
    int available_seats_;
};

#endif // PLAY_HH
