#ifndef DATABASECLASS_H
#define DATABASECLASS_H

#include <string>
#include <vector>
#include "ChessEngine.h"
#include <sw/redis++/redis++.h>
#include <iostream>

using namespace sw::redis;


class Database {
public:
    

    Database() : {} 

    void initialize_game(int game_id, const std::string& white_player, const std::string& black_player);
    void update_board(int game_id);
    void add_move(int game_id, const std::string& move);
    void add_move_history(int game_id, const std::string& move);
    void update_current_turn(int game_id, bool is_white_turn);
    void update_status(int game_id);
    void update_checks(int game_id);
    void update_checkmates(int game_id);

private:
    
    struct GameData {
        int game_id;
        std::string white_player;
        std::string black_player;
        std::string board_state;
        std::vector<std::string> move_history;
        bool is_white_turn;
        std::string status;
        bool is_white_in_check;
        bool is_black_in_check;
        bool is_white_in_checkmate;
        bool is_black_in_checkmate;
    };

    std::vector<GameData> games; 
    GameData* get_game(int game_id); 
};

#endif // DATABASECLASS_H
