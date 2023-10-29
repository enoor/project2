/* Program authors
 *
 * Name: Essi Asunmaa
 * Student number:
 * UserID:
 * E-mail: essi.n.asunmaa@tuni.fi
 *
 * Name: Teemu Syrjala
 * Student number: 151461352
 * UserID: nrtesy
 * E-Mail: teemu.syrjala@tuni.fi
 */

#include "play.hh"

Play::Play(std::string name, std::set<std::string> actors, int available_seats) :
    name_(name), actors_(actors), available_seats_(available_seats)
{

}

Play::~Play()
{

}

std::string Play::get_name() const
{
    return name_;
}

std::set<std::string> Play::get_actors() const
{
    return actors_;
}

int Play::get_seats() const
{
    return available_seats_;
}

void Play::update_seats(int new_seats)
{
    available_seats_ = new_seats;
}

void Play::add_actor(std::string actor)
{
    if(actors_.find(actor) == actors_.end()) {
        actors_.insert(actor);
    }
}

void Play::print()
{
    std::cout << name_ << ": " << available_seats_ << std::endl;

    for(auto& actor : actors_) {
        std::cout << "- " << actor << std::endl;
    }
}
