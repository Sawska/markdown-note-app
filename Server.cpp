#include "Server.h"

void Server::set_up_routes() {
    
    CROW_ROUTE(app, "/create_game")([this]() {
        engine.initialize_board();  
        id += 1;  

        engines.push_back(ChessEngine);
        std::string player1;
        std::string player2;
        if (PRNG() > PRNG()) {
            player1 = "Player";
            player2 = "bot";
        } else {
            player1 = "bot";
            player2 = "Player";
        }

        
        db.initialize_game(id, player1, player2);

        return crow::json::wvalue{{"status", "success"}, {"game_id", id}, {"white", player1}, {"black", player2}};
    });

    
    CROW_ROUTE(app, "/make_move").methods(crow::HTTPMethod::Post)([this](const crow::request& req) {
        auto body = crow::json::load(req.body);
        int game_id = body["game_id"].i();
        std::string from = body["from"].s();
        std::string to = body["to"].s();
        ChessEngine engine = engines[game_id]; 
        
        
        Position fromPos = parse_position(from);
        Position toPos = parse_position(to);

        if (engine.make_move(fromPos, toPos)) {
            db.update_board(game_id);
            db.update_checkmates(id);
            db.update_checks(id);
            db.add_move(game_id, from + " to " + to);
            db.update_current_turn(game_id, engine.current_turn);  

            return crow::json::wvalue{{"status", "success"}, {"message", "Move processed"}};
        } else {
            return crow::json::wvalue{{"status", "error"}, {"message", "Invalid move"}};
        }
    });


    CROW_ROUTE(app, "/get_game/<int>")([this](int game_id) {
        auto game = db.get_game(game_id);
        if (game) {
            return crow::json::wvalue{
                {"game_id", game->game_id},
                {"players", {
                    {"white", {{"username", game->white_player}}},
                    {"black", {{"username", game->black_player}}}
                }},
                {"board_state", game->board_state},
                {"move_history", game->move_history},
                {"current_turn", game->is_white_turn ? "white" : "black"},
                {"status", game->status},
                {"is_white_in_check", game->is_white_in_check},
                {"is_black_in_check", game->is_black_in_check},
                {"is_white_in_checkmate", game->is_white_in_checkmate},
                {"is_black_in_checkmate", game->is_black_in_checkmate}
            };
        } else {
            return crow::json::wvalue{{"status", "error"}, {"message", "Game not found"}};
        }
    });
    
    CROW_ROUTE(app, "/add_move_history").methods(crow::HTTPMethod::Post)([this](const crow::request& req) {
    
    auto body = crow::json::load(req.body);

    
    int game_id = body["game_id"].i();
    std::string move = body["move"].s();  

    
    db.add_move_history(game_id, move);


    return crow::json::wvalue{{"status", "success"}, {"message", "Move history updated"}};
});


CROW_ROUTE(app, "/bot_move").methods(crow::HTTPMethod::Post)([this](const crow::request& req) {
    auto body = crow::json::load(req.body);
    int game_id = body["game_id"].i();

    
    auto game = db.get_game(game_id);
    if (!game) {
        return crow::response(400, "Invalid game ID");
    }


    if (game->current_turn != "bot") {
        return crow::response(400, "Not the bot's turn");
    }

    
    ChessEngine engine = engines[game_id]; 
    Position bot_move = engine.best_move();

    
    engine.make_move(bot_move.from, bot_move.to);

    
    db.update_board(game_id);  
    db.update_current_turn(game_id, false);


    return crow::json::wvalue{{"status", "success"}, {"bot_move", {{"from", bot_move.from}, {"to", bot_move.to}}}, {"board", engine.get_board_state()}};
});


    
}



void Server::run_server()  {
    set_up_routes();
    app.port(18080).multithreaded().run();
}