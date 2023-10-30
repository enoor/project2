/* Theater database
 *
 * Desc:
 *   This program implements a searchable theater database. The program
 * reads a text file with a semicolon (;) delimiter and constructs a
 * database of theaters. The theaters stored can contain information about their
 * town of operation, the plays they have running, the main actors involved
 * in these plays and the number of seats available for an upcoming show.
 *   The text file should follow the form: "Town;Theater name;Play name;
 * Actor;Seats available" and it can not contain empty fields. Whenever a new
 * value for available seats is read for a specific play in a specific theater,
 * the last value read is the up-to-date number of seats available. After
 * reading the file, the program expects commands from the user with the prompt
 * 'the>' after which the user can give the following commands:
 *
 *   theatres - prints all the known theatres in alphabetical order,
 *   plays - prints all the plays in alphabetical order,
 *   theatres_of_play <play> - prints all the theatres that offer the given
 *                             play,
 *   plays_in_theatre <theatre> - prints the plays of the given theatre,
 *   plays_in_town <town> - prints those plays in the given town that has
 *                          free seats,
 *   players_in_play <play> [<theatre>] - prints actors in the given play,
 *   quit - terminates the program.
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
 * Student number:
 * UserID:
 * E-mail: essi.n.asunmaa@tuni.fi
 *
 * Name: Teemu Syrjala
 * Student number: 151461352
 * UserID: nrtesy
 * E-Mail: teemu.syrjala@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 *
 */

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <theater.hh>
#include <play.hh>
#include <boost/algorithm/string.hpp>

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

// Structure for a command
struct Command {
    std::string name;
    std::vector<std::string>::size_type min_param;
    std::vector<std::string>::size_type max_param;
};

// Available commands for user
const std::vector<Command> COMMANDS = {{"quit",1,1},
                                       {"theaters",1,1},
                                       {"plays",1,1},
                                       {"theaters_of_play",2,2},
                                       {"plays_in_theater",2,2},
                                       {"players_in_play",2,3}};

// Casual split function, if delim char is between "'s, ignores it.
std::vector<std::string> split(const std::string& str, char delim)
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delim and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    return result;
}

/* read_file reads a text file with a ';' delimiter character line by line and
 * creates a Theater class object for all the theaters it comes across.
 * Information about the play is read and stored in a Play object, which is then
 * stored inside a Theater object. If a Theater object already exists, the
 * function updates the existing class object. It also constructs and returns a
 * map containing all the class objects, key value being the theater name.
 */
std::map<std::string, Theater> read_file(std::ifstream& file) {

    std::map<std::string, Theater> theaters;

    std::string line;

    int linecount = 0;
    while (getline(file, line)) {
        linecount += 1;
        // std::cout << "test input    " << line << std::endl;
        std::vector info = split(line, ';');
        if (info.size() != NUMBER_OF_FIELDS){
            std::cout << EMPTY_FIELD << linecount << std::endl;
            theaters.clear(); // empty the map to indicate a failed read. This
            // gets returned outside the loop and error is given in main if
            // the map is empty.
            break;
        }
        else {
            for (std::string& i : info){
                boost::trim(i); //utilizing trim function from boost library
                                //to remove possible whitespace from field
                if (i == ""){
                    std::cout << EMPTY_FIELD << linecount << std::endl;
                    theaters.clear();
                    break;
                }
            }
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
        } else {
            seats = std::stoi(info.at(4)); // string to integer conversion
        }

        Play play_data(play_name, play_alias, {actor}, seats); // add play data into an object

        // Check if the theater exists
        if(theaters.find(name) != theaters.end()) {
            //Update existing theater
            Theater& existing_theater = theaters.at(name);
            existing_theater.put_play(play_data); // if play doesn't exist, put play
            existing_theater.put_actor_in_play(actor, play_name); // if play exists, put actor if it doesn't exist
            existing_theater.update_seats_in_play(seats,play_name); // updates seats in said play

        } else {
            // Add new theater
            Theater theater_data(name,town,{play_data});
            theaters.insert({name, theater_data});
        }

    }
    file.close();
    return theaters;
}

// Checks whether the command given by user is valid and gives an error message if not.
bool is_command_valid(std::vector<std::string>& commands) {
    // Checks if a command given in input exists
    for(Command x : COMMANDS) {
        if(commands.at(0) == x.name) {

            // For a correct command, check whether input the right amount of parameters
            if(commands.size() >= x.min_param and commands.size() <= x.max_param) {
                return 1;
            } else {
                std::cout << WRONG_PARAMETERS << std::endl;
                return 0;
            }
        }
    }

    std::cout << COMMAND_NOT_FOUND << std::endl;
    return 0;

}

// Main function
int main()
{

    // Read a file into memory and transform it into Theater objects based on given information
    std::string filename = "plays.csv";
    //std::cout << "Input file: ";
    //std::cin >> filename;

    std::ifstream file_object(filename);
    if (!file_object) {
        std::cout << FILE_ERROR << std::endl;
        return EXIT_FAILURE;
    }

    std::map<std::string, Theater> all_theaters = read_file(file_object);
    if (all_theaters.empty()){
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

        if(commands.at(0) == "quit") {
            return EXIT_SUCCESS;
        }
        else if (commands.at(0) == "theaters") {
            for(auto& theater_info : all_theaters) {
                std::cout << theater_info.first << std::endl;
            }
        }
        else if (commands.at(0) == "plays") {         
            // TO DO: Essi
        }
        else if (commands.at(0) == "theaters_of_play") {
            std::string target_play = commands.at(1);

            for (auto& theater_obj : all_theaters) {
                Theater* theater = &theater_obj.second;
                Play play = theater->get_play(target_play);
                if (play.get_name() == target_play){
                    std::cout << theater->get_name() << std::endl;
            }
            }
            }



        else if (commands.at(0) == "plays_in_theater") {
            std::string target_theater = commands.at(1);
            if (all_theaters.find(target_theater) != all_theaters.end()) {
                // assign pointer to the specific Theater object to access
                // it's plays
                Theater* theater = &all_theaters[target_theater];
                std::vector<Play> plays_to_print = theater->get_plays();
                for (auto& play : plays_to_print){
                    std::cout << play.get_name() << std::endl;
                }
            }
            else {
                std::cout << THEATRE_NOT_FOUND << std::endl;
            }

        }
        else if (commands.at(0) == "players_in_play") {
            std::string target_play = commands.at(1);
            bool play_found = false; // flag for error printing

            // specific theater from input
            if (commands.size() == 3){
                std::string target_theater = commands.at(2);
                if (all_theaters.find(target_theater) != all_theaters.end()) {
                    // use pointer to Theater object to access its plays
                    Theater* theater = &all_theaters[target_theater];
                    Play play = theater->get_play(target_play);
                    if (play.get_name() != ""){
                        play_found = true;
                    std::cout << theater->get_name();
                    // loop through and print actors in the Play oject's set
                    for (const std::string& actor : play.get_actors()) {
                        std::cout << theater->get_name() << " : " << actor << std::endl;
                    }
                    }
                }
                else {
                    std::cout << THEATRE_NOT_FOUND << std::endl;
                }
                }
            // no specific theater from the input
            // iterate through all the theaters searching for the wanted play
            if (commands.size() == 2){
                for (auto& theater_obj : all_theaters ){
                    Theater* target_theater = &theater_obj.second;
                    Play play = target_theater->get_play(target_play);
                    if (play.get_name() != ""){
                        play_found = true;
                    // loop through and print actors in the Play object's set
                    for (const std::string& actor : play.get_actors()) {
                        std::cout << target_theater->get_name() << " : " <<
                        actor << std::endl;
                    }
                  }
               }
            }
            if (play_found == false){
                std::cout << PLAY_NOT_FOUND << std::endl;
            }
        }
    }

}
