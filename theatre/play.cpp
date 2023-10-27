#include "play.hh"

play::play(std::string name, std::set<std::string> actors, int available_seats, Theater *theater) :
    name_(name), actors_(actors), available_seats_(available_seats), theater_(theater)
{

}
