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

#include "theater.hh"
#include "play.hh"

//Class constructors
Theater::Theater(std::string name,
                 std::string town,
                 std::vector<Play> plays):
    name_(name), town_(town), plays_(plays)
{
}

Theater::Theater()
{
}

// Class functions
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

// Add a play into specific theater objects plays if it doesn't already exist
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
        // Add the play to the list of plays in the object
        plays_.push_back(new_play);
    }
}


Play Theater::get_play(std::string play_name) {

    for(auto& play : plays_) {
        // search by play names or their aliases
        if(play.get_name() == play_name || play.get_alias() == play_name) {
            return play;

        }
    }

    return {"", "", {}, 0};
}

// Adds an actor into a Play object if it doesn't already exist
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

// Assigns a new value for available seats in a Play object
void Theater::update_seats_in_play(int new_seats, std::string play_name)
{
    // Find the play being asked for
    for (Play& play : plays_) {
        if (play.get_name() == play_name) {
            play.update_seats(new_seats);
        }
    }
}

// Test prints
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




