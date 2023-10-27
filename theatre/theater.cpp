#include "theater.hh"

Theater::Theater(std::string theater, std::string town, std::map<std::set<std::string>, std::vector<std::string>> play, int seats):
    theater_(theater), town_(town), play_(play), seats_(seats) {
}

std::string Theater::get_name() {
    return theater_;
}

std::string Theater::get_town() {
    return town_;
}

std::string Theater::get_play_name(std::string wanted) {
    for (auto& i : play_) {
        std::set<std::string> play_names = i.first; //first element of the set
        if (play_names.find(wanted) != play_names.end()) {
            return i.second[0];  // Return the name of the play
        }
    }
    return "";  // Play does not exist
}

std::vector<std::string> Theater::get_actors(std::set<std::string> play_name) {

    std::vector<std::string> actors;
    actors = play_[play_name];

    return actors;
}

void Theater::put_play(std::set<std::string> new_play) {
    play_[new_play] = std::vector<std::string>();
}

void Theater::put_actor(std::string actor, std::set<std::string> play_name) {

    play_[play_name].push_back(actor); // add actor to vector of actors in specific play

    }

void Theater::update_seats(int new_seats){
    seats_ = new_seats;
}

void Theater::get_play() {

}

int Theater::get_seats(){
    return seats_;
}
