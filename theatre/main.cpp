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
    // Currently does not work as intended

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
    Play p1("Testi näytelmä", {"Maija Meikäläinen", "Hemmo Harjava", "Katti Matikainen"}, 20);
    Play p2("Testi näytelmä 2", {"Kaija Koo", "Lordi", "Seppä Ilmarinen"}, 0);

    Theater testi("Testi Teatteri",
                  "Tampere",
                  {p1, p2});
    testi.print();

    Play p3("Uusi näytelmä", {"Mari Mantunen", "Heikki Herras"}, 15);
    testi.put_play(p3);


    testi.print();


}
