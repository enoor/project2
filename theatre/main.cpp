#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <theater.hh>

// there's a "smalltest.txt" file in the build folder which can be used for
// initial testing, it's just 3 rows with 2 theaters.

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


std::vector<Theater> read_file(std::ifstream& file) {

   // TO DO: Teemu make into map: string:name > Theater object
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

        int seats;
        if(info.at(4) == "none") {
            seats = 0;
        } else {
            seats = std::stoi(info.at(4)); // string to integer conversion
        }

        // check if we already have a class object for this theater:
        bool exists = false;
        for (Theater& theater : theaters) {
            if (theater.get_name() == name) {
                exists = true;
                if (theater.get_play_name(name) == "") {
                    theater.put_play({info.at(2)});
                    theater.put_actor(actor[0], {info.at(2)});
                }
                else {
                    std::vector<std::string> lst_of_actors = theater.get_actors({info.at(2)});
                    for (std::string& a : lst_of_actors){
                        if (a != actor[0]){
                           theater.put_actor(actor[0], {info.at(2)});
                        }
                    }
                }
              theater.update_seats(seats);
            }
        }

        if (exists == false) {
            std::cout << "creating a class object" << std::endl;
            Theater my_theater(name, town, play_data, seats); // create a class object
            theaters.push_back(my_theater); // add object to vector of objects
        }
    }

    std::cout  << "\ntest print to see if 2 theaters have been created:" << std::endl; //test
    for (Theater& theater : theaters) { // test
        std::cout << theater.get_town() << " - " << theater.get_name() << theater.get_seats() << std::endl; //test
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

void order_alphabetically(std::vector<Theater>& all_theaters) {

    //TO DO: Essi fix this

    std::vector<Theater> alphabetized_theaters;
    std::string previous = "";
    for(Theater t : all_theaters) {

        bool is_smaller = t.get_name() < previous;

        if(is_smaller) {
           alphabetized_theaters.insert(alphabetized_theaters.begin(), t);
        } else {
           alphabetized_theaters.push_back(t);
        }

        previous = t.get_name();
    }

    all_theaters = alphabetized_theaters;

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

    std::vector<Theater> all_theaters = read_file(file_object);

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
            order_alphabetically(all_theaters);
            for(Theater theater : all_theaters) {
                std::cout << theater.get_name() << std::endl;
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
