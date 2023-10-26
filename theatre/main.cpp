#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <theater.hh>

// there's a "smalltest.txt" file in the build folder which can be used for
// initial testing, it's just 3 rows with 2 theaters.


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

// structure for a command
struct Command {
    std::string name;
    std::vector<std::string>::size_type min_param;
    std::vector<std::string>::size_type max_param;
    std::pair<std::vector<std::string>::size_type, std::vector<std::string>::size_type> limits = {min_param, max_param};
};

// available commands
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



void read_file(std::ifstream& file) {
    std::vector<Theater> theaters; // vector of class objects for future checking

    std::string line;

    while (getline(file, line)) {
        std::cout  << "test print       " << line << std::endl; //test

        std::vector info = split(line, ';');
        std::string town = info.at(0);
        std::string name = info.at(1);
        std::set<std::string> play = {info.at(2)};
        std::vector<std::string> actor = {info.at(3)};

        std::map<std::set<std::string>, std::vector<std::string>> play_data;
        play_data[play] = actor;

        int seats = std::stoi(info.at(4)); // string to integer conversion

        // check if we already have a class object for this theater:
        bool exists = false;
        for (Theater& theater : theaters) {
            if (theater.get_name() == name) {
                exists = true;
                break;
            }
        }

        if (exists == false) {
            std::cout << "creating a class object" << std::endl;
            Theater my_theater(name, town, play_data, seats); // create a class object
            theaters.push_back(my_theater); // add object to vector of objects
        }
        //else if {
        // update the existing object.
        // else if get_play_name == "" (function not confirmed functional yet!)
        // -> add play
        //}
    }
    std::cout  << "test print to see if 2 theaters have been created:" << std::endl; //test
    for (Theater& theater : theaters) { // test
        std::cout << theater.get_town() << " - " << theater.get_name() << std::endl; //test
    }
    file.close();

}


bool is_right_amount_of_inputs(const std::vector<std::string>& commands, const std::pair<std::vector<std::string>::size_type, std::vector<std::string>::size_type>& limits) {
    if(commands.size() >= limits.first and commands.size() <= limits.second) {
        return true;
    } else {
        std::cout << WRONG_PARAMETERS << std::endl;
        return 0;
    }
}

bool is_command_valid(std::vector<std::string>& commands) {

    // Checks if any such command exists
    // TO DO: IF FUNCTION FOR COMMAND EXISTING

    // Checks if you have given the right amount of parameters for the command
    // TO DO: IF FUNCTION FOR LENGTH OF THE VECTOR OF COMMANDS VS LIMITS FOR SAID COMMAND

    return 1;
}

// Main function
int main()
{
    std::map<std::string, std::vector<Theater>> theaters_in_town;

    std::string filename = "plays.csv";
    std::cout << "Input file: ";
    std::cin >> filename;

    std::ifstream file_object(filename);
    if (!file_object) {
        std::cout << FILE_ERROR << std::endl;
        return EXIT_FAILURE;
    }

    read_file(file_object);
    // Lue csv tiedosto rivi riviltä, siirä jokainen vektorin pala sopiviin containereihin
    // jokainen rivi muotoa <town>;<theatre>;<play>;<player>;<number_of_free_seats>

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

        if(commands.at(0) == "quit" and is_right_amount_of_inputs(commands, {1,1})) {
            return EXIT_SUCCESS;
        }
        else if (commands.at(0) == "theaters" and is_right_amount_of_inputs(commands, {1,1})) {

        }
        else if (commands.at(0) == "plays" and is_right_amount_of_inputs(commands, {1,1})) {

        }
        else if (commands.at(0) == "theaters_of_play" and is_right_amount_of_inputs(commands, {2,2})) {

        }
        else if (commands.at(0) == "plays_in_theater" and is_right_amount_of_inputs(commands, {2,2})) {

        }
        else if (commands.at(0) == "players_in_play" and is_right_amount_of_inputs(commands, {2,3})) {

        }


    }

    return EXIT_SUCCESS;
}
