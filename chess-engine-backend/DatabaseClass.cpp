#include "DatabaseClass.h"

const std::string VAR = []{ std::ifstream myfile("data.txt"); std::string var; if (myfile.is_open()) std::getline(myfile, var); return var; }();




void Database::initialize_game(int game_id, const std::string& white_player, const std::string& black_player) {
    auto redis = Redis("");

    redis.hset("game:" + std::to_string(game_id), "white_player", white_player);
    redis.hset("game:" + std::to_string(game_id), "black_player", black_player);
    redis.hset("game:" + std::to_string(game_id), "status", "ongoing");
    redis.hset("game:" + std::to_string(game_id), "is_white_turn", "1");
}

void Database::update_board(int game_id) {
    auto redis = Redis(VAR);
    
    std::string board_state = engine.board.serialize(); 
    redis.hset("game:" + std::to_string(game_id), "board_state", board_state);
}

void Database::add_move(int game_id, const std::string& move) {
    auto redis = Redis(VAR);
    
    
    redis.rpush("game:" + std::to_string(game_id) + ":moves", move);
}

void Database::add_move_history(int game_id, const std::string& move) {
    auto redis = Redis(VAR);
    
    
    redis.rpush("game:" + std::to_string(game_id) + ":move_history", move);
}

void Database::update_current_turn(int game_id, bool is_white_turn) {
    auto redis = Redis(VAR);
    
    
    redis.hset("game:" + std::to_string(game_id), "is_white_turn", is_white_turn ? "1" : "0");
}

void Database::update_status(int game_id) {
    auto redis = Redis(VAR);

    std::string status;
    if (engine.is_checkmate(true)) {
        status = "white_checkmated";
    } else if (engine.is_checkmate(false)) {
        status = "black_checkmated";
    } else {
        status = "ongoing";
    }

    redis.hset("game:" + std::to_string(game_id), "status", status);
}

void Database::update_checks(int game_id) {
    auto redis = Redis(VAR);
    
    bool is_white_in_check = engine.is_under_attack(engine.board.get_king_position(true), true);
    bool is_black_in_check = engine.is_under_attack(engine.board.get_king_position(false), false);
    
    redis.hset("game:" + std::to_string(game_id), "is_white_in_check", is_white_in_check ? "1" : "0");
    redis.hset("game:" + std::to_string(game_id), "is_black_in_check", is_black_in_check ? "1" : "0");
}

void Database::update_checkmates(int game_id) {
    auto redis = Redis(VAR);

    bool is_white_in_checkmate = engine.is_checkmate(true);
    bool is_black_in_checkmate = engine.is_checkmate(false);
    
    redis.hset("game:" + std::to_string(game_id), "is_white_in_checkmate", is_white_in_checkmate ? "1" : "0");
    redis.hset("game:" + std::to_string(game_id), "is_black_in_checkmate", is_black_in_checkmate ? "1" : "0");
}

Database::GameData* Database::get_game(int game_id) {
    auto redis = Redis(VAR);

    
    auto game_data = redis.hgetall<std::string>("game:" + std::to_string(game_id));
    
    if (!game_data.empty()) {
        GameData* game = new GameData();
        game->game_id = game_id;
        game->white_player = game_data["white_player"];
        game->black_player = game_data["black_player"];
        game->board_state = game_data["board_state"];
        game->is_white_turn = game_data["is_white_turn"] == "1";
        game->status = game_data["status"];
        game->is_white_in_check = game_data["is_white_in_check"] == "1";
        game->is_black_in_check = game_data["is_black_in_check"] == "1";
        game->is_white_in_checkmate = game_data["is_white_in_checkmate"] == "1";
        game->is_black_in_checkmate = game_data["is_black_in_checkmate"] == "1";

    
        auto move_history = redis.lrange<std::string>("game:" + std::to_string(game_id) + ":moves", 0, -1);
        game->move_history.assign(move_history.begin(), move_history.end());
        
        return game;
    }

    return nullptr;
}
