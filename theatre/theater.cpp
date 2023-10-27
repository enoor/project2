#include "theater.hh"
#include "play.hh"

Theater::Theater(std::string name,
                 std::string town,
                 std::vector<Play> plays):
    name_(name), town_(town), plays_(plays)
{
}

Theater::~Theater()
{
}

std::string Theater::get_name() const
{
    return name_;
}

std::string Theater::get_town() const
{
    return town_;
}

std::vector<Play> Theater::get_plays() const
{
    return plays_;
}

void Theater::put_play(Play& new_play)
{
    bool play_exists = false;
    for (Play& existingPlay : plays_) {
        if (existingPlay.get_name() == new_play.get_name()) {
            play_exists = true;
            break; // No need to continue searching
        }
    }

    if (!play_exists) {
        // Add the actor to the play
        plays_.push_back(new_play);
    }
}

Play Theater::get_play(std::string play_name) {

    for(auto& play : plays_) {
        if(play.get_name() == play_name) {
            return play;

        }
    }

    return {"", {}, 0};
}

void Theater::put_actor_in_play(std::string actor, std::string play_name)
{
    // Find the play being asked for
    for (Play& play : plays_) {
        if (play.get_name() == play_name) {
            // Check if the actor is already in the play
            bool actorExists = false;
            for (const std::string& existingActor : play.get_actors()) {
                if (existingActor == actor) {
                    actorExists = true;
                    break;
                }
            }

            if (!actorExists) {
                // Add the actor to the play, if actor not listed
                play.add_actor(actor);
            }
        }
    }
}

void Theater::update_seats_in_play(int new_seats, std::string play_name)
{
    // Find the play being asked for
    for (Play& play : plays_) {
        if (play.get_name() == play_name) {
            play.update_seats(new_seats);
        }
    }
}

void Theater::print()
{
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Theater name: " << name_ << std::endl;
    std::cout << "In town: " << town_ << std::endl << std::endl;

    std::cout << "With following plays: " << std::endl;
    for(auto play : plays_) {
        std::cout << "     " << std::endl;
        play.print();
    }
    std::cout << std::endl;
}




