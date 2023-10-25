#include <iostream>
#include <vector>

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


// Main function
int main()
{

    // Lue csv tiedosto rivi riviltä, siirä jokainen vektorin pala sopiviin containereihin
    // jokainen rivi muotoa <town>;<theatre>;<play>;<player>;<number_of_free_seats>


    // map: towns > theaters


    // 2. looppi käyttäjän syötteitä

    std::string user_command;


    while(true) {

        std::cout << "the> ";
        std::cin >> user_command;

        std::vector multi_command = split(user_command, ' ');
        std::vector< std::string >::size_type number_of_parameters = multi_command.size();

        std::cout << "number of parameters: " << number_of_parameters << " and at 1 we have " << multi_command.at(0) << std::endl;

        if(multi_command.at(0) == "quit" and number_of_parameters == 1) {
            return EXIT_SUCCESS;
        } else if (multi_command.at(0) == "theaters" and number_of_parameters == 1) {

        } else if (multi_command.at(0) == "plays" and number_of_parameters == 1) {

        } else if (multi_command.at(0) == "theaters_of_play" and number_of_parameters == 2) {

        } else if (multi_command.at(0) == "plays_in_theater" and number_of_parameters == 2) {

        } else if (multi_command.at(0) == "players_in_play" and number_of_parameters >= 2 and number_of_parameters <= 3) {

        } else {
            std::cout << WRONG_PARAMETERS << std::endl;
        }


        /* käyttäjä voi pyytää:
     * - quit
     * - theaters
     * - plays
     * - theaters_of_play <play>
     * - plays_in_theater <town>
     * - players_in_play <play> [<theater>]
     */
    }

    return EXIT_SUCCESS;
}
