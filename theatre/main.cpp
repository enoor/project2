/* Theatre database
 *
 * Desc:
 *   This program implements a searchable theatre database. The program
 * reads a text file with a semicolon (;) delimiter and constructs a
 * database of theatres. The theatres stored can contain information about their
 * town of operation, the plays they have running, the main actors involved
 * in these plays and the number of seats available for an upcoming show.
 *   The text file should follow the form: "Town;Theatre name;Play name;
 * Actor;Seats available" and it can not contain empty fields. Whenever a new
 * value for available seats is read for a specific play in a specific theatre,
 * the last value read is the up-to-date number of seats available. After
 * reading the file, the program expects commands from the user with the prompt
 * 'the>' after which the user can give the following commands:
 *
 *   quit - terminates the program,
 *   theatres - prints all the known theatres in alphabetical order,
 *   plays - prints all the plays in alphabetical order,
 *   theatres_of_play <play> - prints all the theatres that offer the given
 *                             play,
 *   plays_in_theatre <theatre> - prints the plays of the given theatre,
 *   plays_in_town <town> - prints those plays in the given town that has
 *                          free seats,
 *   players_in_play <play> [<theatre>] - prints actors in the given play.
 *
 * Quotation marks should be used when giving parameters consisting of multiple
 * words. Quotation marks can also be used for single word parameters if
 * preferred. For example, 'theatres_of_play Evita' and
 * 'theatres_of_play "Evita"' have the same output.
 *
 *
 * Program authors
 *
 * Name: Essi Asunmaa
 * Student number: 151876727
 * UserID: bmesas
 * E-mail: essi.n.asunmaa@tuni.fi
 *
 * Name: Teemu Syrjala
 * Student number: 151461352
 * UserID: nrtesy
 * E-Mail: teemu.syrjala@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 * Map structures have been utilized to deal with the need for alphabetical
 * printing.
 *
 * PLEASE NOTE we have worked with the project on GitHub at:
 * https://github.com/enoor/project2
 *
 */

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <play.hh>
#include <theatre.hh>

// Fields in the input file
const int NUMBER_OF_FIELDS = 5;

// Command prompt
const std::string PROMPT = "the> ";

// Error and other messages
const std::string EMPTY_FIELD = "Error: empty field in line ";
const std::string FILE_ERROR = "Error: input file cannot be opened";
const std::string WRONG_PARAMETERS = "Error: wrong number of parameters";
const std::string THEATRE_NOT_FOUND = "Error: unknown theatre";
const std::string PLAY_NOT_FOUND = "Error: unknown play";
const std::string PLAYER_NOT_FOUND = "Error: unknown player";
const std::string TOWN_NOT_FOUND = "Error: unknown town";
const std::string COMMAND_NOT_FOUND = "Error: unknown command";
const std::string NOT_AVAILABLE = "No plays available";

// Structure for a user command, containing name of command and amount of parameters required.
struct Command {
    std::string name;
    std::vector<std::string>::size_type min_param;
    std::vector<std::string>::size_type max_param;
};

// Available valid commands
const std::vector<Command> AVAILABLE_COMMANDS = {{"quit",1,1},
                                                 {"theatres",1,1},
                                                 {"plays",1,1},
                                                 {"theatres_of_play",2,2},
                                                 {"plays_in_theatre",2,2},
                                                 {"plays_in_town",2,2},
                                                 {"players_in_play",2,3}};

// Casual split function, if delim char is between "'s, ignores it.
std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str){
        if(current_char == '"') {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delim and not inside_quotation) {
            result.push_back("");
        }
        else {
            result.back().push_back(current_char);
        }
    }
    return result;
}

/* is_wrong_number_of_fields tests if a row in data file contains exactly NUMBER_OF_FIELDS.
 * A field is considered valid, as long as it contains any other character than empty_char.
 */
bool is_wrong_number_of_fields(const std::vector<std::string>& fields, char empty_char = ' ') {

    if(fields.size() != NUMBER_OF_FIELDS) {
        return true;
    }
    else {
        // If vector size is five, checks whether any of the fields are empty
        int field_not_empty = 0;
        for(std::string str : fields) {
            for(char c : str) {
                if(c != empty_char) {
                    field_not_empty++;
                    break;
                }
            }
        }
        return field_not_empty != NUMBER_OF_FIELDS;
    }
}

/* read_file reads a text file with a ';' delimiter character line by line and
 * creates a Theatre class object for all the theatres it comes across.
 * Information about the play is read and stored in a Play object, which is then
 * stored inside a Theatre object. If a Theatre object already exists, the
 * function updates the existing class object. It also constructs and returns the
 * theatres map containing all the class objects where the key is the theatre name.
 */
std::map<std::string, Theatre> read_file(std::ifstream& file) {

    std::map<std::string, Theatre> theatres;
    std::string line;

    int linecount = 0;
    while (getline(file, line)) {

        linecount += 1;
        std::vector info = split(line, ';');

        if (is_wrong_number_of_fields(info)){
            std::cout << EMPTY_FIELD << linecount << std::endl;
            theatres.clear(); // Empty the map to indicate a failed read.
            break;
        }

        std::string town = info.at(0);
        std::string name = info.at(1);
        std::vector play = split(info.at(2), '/');
        std::string play_name = play.at(0);
        std::string play_alias;
        if (play.size() > 1){
            play_alias = play.at(1);
        }
        std::string actor = info.at(3);

        int seats;
        if(info.at(4) == "none") {
            seats = 0;
        }
        else {
            seats = std::stoi(info.at(4));
        }

        Play play_data(play_name, play_alias, {actor}, seats);

        // Check if the theatre exists
        if(theatres.find(name) != theatres.end()) {
            //Update existing theatre
            Theatre& existing_theatre = theatres.at(name);
            existing_theatre.put_play(play_data); // if play doesn't exist, put play
            existing_theatre.put_actor_in_play(actor, play_name); // if play exists, put actor if it doesn't exist
            existing_theatre.update_seats_in_play(seats,play_name); // updates seats in said play

        }
        else {
            // Add new theatre
            Theatre theatre_data(name,town,{play_data});
            theatres.insert({name, theatre_data});
        }

    }
    file.close();
    return theatres;
}

/* is_command_valid checks whether the command given by user is valid
 * based on what is in AVAILABLE_COMMANDS. Returns the following error messages.
 * - WRONG_PARAMETERS: if command is correct but has wrong amount of parameteres.
 * - COMMAND_NOT_FOUND: if no commands of the given name exists.
 */
bool is_command_valid(std::vector<std::string>& commands) {
    // Checks if a command given in input exists
    for(Command x : AVAILABLE_COMMANDS) {
        if(commands.at(0) == x.name) {
            // For a correct command, check whether input the right amount of parameters
            if(commands.size() >= x.min_param and commands.size() <= x.max_param) {
                return true;
            }
            else {
                std::cout << WRONG_PARAMETERS << std::endl;
                return false;
            }
        }
    }

    std::cout << COMMAND_NOT_FOUND << std::endl;
    return false;

}

int main() {

    // Read a file into memory and transform it into Theatre objects based on given information
    std::string filename;
    std::cout << "Input file: ";
    std::getline(std::cin, filename);

    std::ifstream file_object(filename);

    // Exit program if a file does not exist.
    if (!file_object) {
        std::cout << FILE_ERROR << std::endl;
        return EXIT_FAILURE;
    }

    std::map<std::string, Theatre> all_theatres = read_file(file_object);

    // Exit program if no theatres were added from the file
    // due to empty or missing fields on any row of the input file.
    if (all_theatres.empty()){
        return EXIT_FAILURE;
    }

    // Read user input from standard input and ask for commands to access information given in the file
    std::string input = "";
    Command command;

    while(true) {
        std::cout << PROMPT;
        std::getline(std::cin, input);

        std::vector<std::string> commands = split(input, ' ');

        // Checks command validity, throws errors messages, and prompts again if not valid
        if(!is_command_valid(commands)) {
            continue;
        }

        // Actions for valid commands
        if(commands.at(0) == "quit") {
            // quit - terminates the program successfully
            return EXIT_SUCCESS;
        }

        else if (commands.at(0) == "theatres") {
            // theatres - prints all the theatres from input file in alphabetical order
            for(auto& theatre_info : all_theatres) {
                std::cout << theatre_info.first << std::endl;
            }
        }

        else if (commands.at(0) == "plays") {
            // plays - prints all the plays in all the theaters in alphabetical order
            std::map<std::string, std::string> unique_plays = {};
            for(auto& theatre_pair : all_theatres){
                Theatre* theatre = &theatre_pair.second;
                std::vector<Play> plays = theatre->get_plays();

                for (auto& item : plays){
                    std::string play_name = item.get_name();
                    if (unique_plays.find(play_name) == unique_plays.end()){
                        if (item.get_alias() != ""){
                            unique_plays[play_name] = item.get_alias();
                        }
                        else {
                            unique_plays[play_name] = "";
                        }
                    }
                }
            }
            for (auto& play_pair : unique_plays){
                if (play_pair.second == ""){
                    std::cout << play_pair.first << std::endl;
                }
                else{
                    std::cout << play_pair.first << " *** " << play_pair.second << std::endl;
                }
            }
        }

        else if (commands.at(0) == "theatres_of_play") {
            // theatres_of_play <target_play> - prints all the theatres that offer the target_play
            std::map<std::string, std::string> theatrename_map;
            std::string target_play = commands.at(1);

            bool play_found = false;
            for (auto& theatre_pair : all_theatres) {
                Theatre* theatre = &theatre_pair.second;
                Play play = theatre->get_play(target_play);
                if (play.get_name() == target_play or play.get_alias() == target_play){
                    play_found = true;
                    theatrename_map[theatre->get_name()];
                }
            }
            if (!play_found){
                std::cout << PLAY_NOT_FOUND << std::endl;
            }
            else{
                for (auto& theatre : theatrename_map){
                    std::cout << theatre.first << std::endl;
                }
            }
        }

        else if (commands.at(0) == "plays_in_theatre") {
            // plays_in_theatre <target_theatre> - prints the plays of the target_theatre
            std::string target_theatre = commands.at(1);
            std::map<std::string, std::string> playname_map;
            if (all_theatres.find(target_theatre) != all_theatres.end()) {
                Theatre* theatre = &all_theatres[target_theatre]; // assign pointer to the specific Theatre object to access it's plays
                std::vector<Play> plays_to_print = theatre->get_plays();
                for (auto& play : plays_to_print){
                    playname_map[play.get_name()];
                }
            }
            else {
                std::cout << THEATRE_NOT_FOUND << std::endl;
            }
            for (auto& name : playname_map){
                std::cout << name.first << std::endl;
            }

        }

        else if (commands.at(0) == "plays_in_town"){
            // plays_in_town <target_town> - prints those plays in the given town that has free seats
            std::string target_town = commands.at(1);
            std::map<std::string, std::map<std::string, Play>> theatres_and_plays;

            bool town_found = false;
            int total_seats_available = 0;
            for (auto& theatre_pair : all_theatres){
                // Find theaters in the target town
                if(theatre_pair.second.get_town() == target_town) {
                    town_found = true;

                    // Add theatre_name as key initialized with empty value for plays
                    theatres_and_plays.insert({theatre_pair.first, {{}}});

                    // Add plays if plays do not already exist in the theatres_and_plays map
                    for(auto& play_obj : theatre_pair.second.get_plays()) {
                        const std::string& play_name = play_obj.get_name();
                        const std::string& alias = play_obj.get_alias();

                        // Pointer to value of theatres_and_plays map where key is the foudn theatre of the town
                        std::map<std::string, Play>* plays_in_theater = &theatres_and_plays.at(theatre_pair.first);

                        if(plays_in_theater->find(play_name) == plays_in_theater->end()
                                and plays_in_theater->find(alias) == plays_in_theater->end()) {
                            theatres_and_plays.at(theatre_pair.first).insert({play_name, play_obj});
                            total_seats_available += play_obj.get_seats();
                        }
                    }
                }
            }
            if (town_found == true){
                if(total_seats_available == 0) {
                    std::cout << "No plays available" << std::endl;
                }
                else {
                    // Print out all names and their aliases of a specific time
                    for(const auto& theatre_pair : theatres_and_plays) {
                        for(const auto& play_pair : theatre_pair.second) {

                            int seats = play_pair.second.get_seats();
                            if(seats > 0) {
                                std::cout << theatre_pair.first << " : " << play_pair.first;
                                std::string alias = play_pair.second.get_alias();
                                if(alias != "") {
                                    std::cout << " --- " << alias;
                                }
                                std::cout << " : " << play_pair.second.get_seats() << std::endl;
                            }
                        }
                    }
                }
            }
            else {
                // Error message when no town of said name exists
                std::cout << TOWN_NOT_FOUND << std::endl;
            }
        }

        else if (commands.at(0) == "players_in_play") {
            /* players_in_play <target_play> [<target_theatre>] - prints actors in target_play.
             * If commannd consists of two parameters, prints actors in all theatres the play is showing.
             * If command consists of three parameters, prints actors for target_play in target_theatre only.
             */
            std::string target_play = commands.at(1);

            // Initialize map containing theatres playing target_play and for each play the actors in it
            std::map<std::string, std::map<std::string, std::string>> theatres_and_actors;

            // Initializing flags for error printing.
            bool play_found = false;
            bool theatre_found = false;

            // Command consists of three parameteres, i.e. has a target_theatre as well
            if (commands.size() == 3){
                std::string target_theatre = commands.at(2);
                if (all_theatres.find(target_theatre) != all_theatres.end()) {
                    theatre_found = true;
                    Theatre* theatre = &all_theatres[target_theatre];
                    Play play = theatre->get_play(target_play);

                    // Check if the play exists by checking whether it has a name
                    if (play.get_name() != ""){
                        play_found = true;

                        // Create a map of actors to be put inside the theatre
                        std::map<std::string, std::string>& play_actors = theatres_and_actors[target_theatre];

                        // Create a key for each actor in the play
                        for (const std::string& actor : play.get_actors()) {
                            play_actors[actor] = "";
                        }
                    }
                }

                // Raise error if threatre is not found
                if(!theatre_found) {
                    std::cout << THEATRE_NOT_FOUND << std::endl;
                }
                // Raise error if theatre is found but the target_play is not found within the theatre
                else if(!play_found) {
                    std::cout << PLAY_NOT_FOUND << std::endl;
                }
            }

            // Command consists of two parameteres, i.e. wants plays printed from all theatres
            if (commands.size() == 2){
                for (auto& theatre_pair : all_theatres){
                    Theatre* target_theatre = &theatre_pair.second;
                    Play play = target_theatre->get_play(target_play);
                    if (play.get_name() != ""){
                        play_found = true;
                        std::map<std::string, std::string>& actor_map = theatres_and_actors[target_theatre->get_name()];

                        // loop through and print actors in the Play object's set
                        for (const std::string& actor : play.get_actors()) {
                            actor_map[actor] = "";
                        }
                    }
                }

                if(!play_found) {
                    std::cout << PLAY_NOT_FOUND << std::endl;
                }
            }

            if (play_found == true){
                for (const auto& entry : theatres_and_actors) {
                    for (const auto& play_actor : entry.second) {
                        std::cout << entry.first << " : " << play_actor.first << std::endl;
                    }
                }
            }

        }
    }
}
