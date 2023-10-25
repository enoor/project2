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
    // not tested, confusing!! :D Does this search for the right thing?
    // this is supposed to return the name of the play if it exists and
    // "" if it does not
    std::set<std::string> key = {wanted};
    std::vector<std::string> play_names = play_[key];

    if (!play_names.empty()) {
        return wanted;
    }
    else {
        return "";
    }
}

void Theater::put_play(std::string new_play) {

}

