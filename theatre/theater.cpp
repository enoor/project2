#include "theater.hh"

Theater::Theater(std::string name,
                 std::string town,
                 std::set<Play> plays):
    name_(name), town_(town), plays_(plays) {
}

Theater::~Theater()
{
}

std::string Theater::get_name() {
    return name_;
}

std::string Theater::get_town() {
    return town_;
}

std::set<Play> Theater::get_all_plays() {
    return plays_;
}

void Theater::put_play(Play& new_play) {
    if(plays_.find(new_play) == plays_.end()) {
        plays_.insert(new_play);
    }
}

Play Theater::get_play(std::string play_name) {

    for(auto& play : plays_) {
        if(play.name == play_name) {
            return play;

        }
    }

    return {"", {}, 0};
}

void Theater::put_actor(std::string actor, std::string play_name) {

    // Find the play being asked for and add the actor to the play, if it doesn't already exist there
    for(auto& play : plays_) {
        if(play.name == play_name) {

            if(play.actors.find(actor) != play.actors.end()) {
                //play.actors.insert(actor);
            }

        }
    }

}

void Theater::update_seats(int new_seats, std::string play_name){

}

void Theater::print_info(bool name = true, bool town = true, bool plays = true)
{

    std::cout << "Information about theater object:" << std::endl;

    if(name) {
        std::cout << "Theater name: " << name_ << std::endl;
    }

    if(town) {
        std::cout << "In town: " << town_ << std::endl;
    }

    if(plays) {
        std::cout << "With following plays: " << std::endl;

        for(auto play : plays_) {
            std::cout << play.name << " : " << play.available_seats << std::endl;

            for(auto& actor : play.actors) {
                std::cout << "- " << actor << std::endl;
            }

        }
    }
}




