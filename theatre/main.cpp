#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <theater.hh>
#include <play.hh>

/* Comment by Teemu
 */

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

std::map<std::string, Theater> read_file(std::ifstream& file) {

    std::map<std::string, Theater> theaters;

    std::string line;

    while (getline(file, line)) {

        std::cout << "test input    " << line << std::endl;
        std::vector info = split(line, ';');
        std::string town = info.at(0);
        std::string name = info.at(1);
        std::string play = info.at(2);
        std::set<std::string> actors = {info.at(3)};

        int seats;
        if(info.at(4) == "none") {
            seats = 0;
        } else {
            seats = std::stoi(info.at(4)); // string to integer conversion
        }

        Play play_data(play, actors, seats); // add play data into an object

        // Check if the theater exists

        if(theaters.find(name) != theaters.end()) {
            //TO DO: DOES NOT WORK, DOES NOT UPDATE CONTENT!!!!!
            /* if exists, check whether the play data exists already
             * check the play name
             * check the actors
             * change the seats */

            Theater existing_theater = theaters.at(name);
            existing_theater.print();
            existing_theater.put_play(play_data);

        } else {
            Theater theater_data(name,town,{play_data});
            theaters.insert({name, theater_data});
        }

    }

    // testing what was created
    std::cout << "Test what was created after reading file: " << std::endl;
    for (auto& theater_info : theaters) {
        theater_info.second.print();
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
            // TO DO: Essi
        }
        else if (commands.at(0) == "plays_in_theater") {
            // TO DO: Teemu
        }
        else if (commands.at(0) == "players_in_play") {
            // TO DO: Teemu
        }


    }


}
