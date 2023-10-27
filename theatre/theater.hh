#ifndef THEATER_HH
#define THEATER_HH
#include <iostream>
#include <map>
#include <set>
#include <vector>


class Theater
{
public:
    Theater(std::string theater, std::string town, std::map<std::set<std::string>, std::vector<std::string>> play, int seats );
    std::string get_name();
    void put_play(std::set<std::string> new_play);
    void put_actor(std::string actor, std::set<std::string> play_name);
    std::string get_play_name(std::string wanted);
    std::string get_town();
    std::vector<std::string> get_actors(std::set<std::string> play_name);
    void update_seats(int new_seats);
    int get_seats();
    void get_play();
    // string teatterin nimi
    // string kaupunki
    /* map: näyttelyt >
     * set < vector päänäyttelijät,
     *      int vapaat_paikat > */

    /* funtiot:
     * get_näyttelyt >
     * put_näyttely >
     * get_kaupunki
     *
     */

private:
    std::string theater_;
    std::string town_;
    std::map<std::set<std::string>, std::vector<std::string>> play_;
    int seats_;




};

#endif // THEATER_HH
