#ifndef PLAY_HH
#define PLAY_HH
#include "theater.hh"
#include <iostream>
#include <set>
#include <string>



class play
{
public:
    play(std::string name,
         std::set<std::string> actors,
         int available_seats,
         Theater* theater);

    std::string get_name();
    std::string get_actors();
    int get_seats();
    Theater get_theater();

private:
    std::string name_;
    std::set<std::string> actors_;
    int available_seats_;
    Theater* theater_;
};

#endif // PLAY_HH
