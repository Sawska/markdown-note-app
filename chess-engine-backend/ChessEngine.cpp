#include "ChessEngine.h"


ChessEngine::ChessEngine() : current_turn(true) {
    initialize_board();
}


void ChessEngine::initialize_board() {
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board.set_piece_at(new NullPiece(i % 2 == 0, Position(i, j)), Position(i, j));
        }
    }

    
    for (int i = 0; i < 8; ++i) {
        board.set_piece_at(new Pawn(true, Position(i, 1)), Position(i, 1));  
        board.set_piece_at(new Pawn(false, Position(i, 6)), Position(i, 6)); 
    }

    
    board.set_piece_at(new Rook(true, Position(0, 0)), Position(0, 0));
    board.set_piece_at(new Rook(true, Position(7, 0)), Position(7, 0));
    board.set_piece_at(new Rook(false, Position(0, 7)), Position(0, 7));
    board.set_piece_at(new Rook(false, Position(7, 7)), Position(7, 7));

    
    board.set_piece_at(new Knight(false, Position(6, 7)), Position(6, 7));
    board.set_piece_at(new Knight(true, Position(6, 0)), Position(6, 0));

    
    board.set_piece_at(new Bishop(false, Position(5, 7)), Position(5, 7));
    board.set_piece_at(new Bishop(true, Position(5, 0)), Position(5, 0));


    board.set_piece_at(new Queen(true, Position(3, 0)), Position(3, 0));
    board.set_piece_at(new Queen(false, Position(3, 7)), Position(3, 7));
    board.set_piece_at(new King(true, Position(4, 0)), Position(4, 0));
    board.set_piece_at(new King(false, Position(4, 7)), Position(4, 7));
}



bool ChessEngine::make_move(Position from, Position to) {
    ChessPiece* piece = board.get_piece_at(from);
    if (piece && piece->get_color() == current_turn) {
        if (piece->is_move_valid(to, board)) {

            board.set_piece_at(piece, to);
            board.remove_piece_at(from); 
            switch_turn();
            return true;
        }
    }
    return false;
}


std::vector<Position> ChessEngine::get_valid_moves(Position from) {
    ChessPiece* piece = board.get_piece_at(from);
    if (piece) {
        return piece->calculate_valid_moves(board);
    }
    return {};
}


void ChessEngine::switch_turn() {
    current_turn = !current_turn;
}


#include "ChessEngine.h"


bool ChessEngine::is_under_attack(Position position, bool color) {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            ChessPiece* piece = board.get_piece_at(Position(x, y));
            if (piece != nullptr && !dynamic_cast<NullPiece*>(piece) && piece->get_color() != color) {
                
                auto valid_moves = piece->calculate_valid_moves(board);
                if (std::find(valid_moves.begin(), valid_moves.end(), position) != valid_moves.end()) {
                    return true;
                }
            }
        }
    }
    return false; 
}

bool ChessEngine::is_checkmate(bool color) {
    
    Position king_position;
    bool king_found = false;

    
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            ChessPiece* piece = board.get_piece_at(Position(x, y));
            if (piece != nullptr && dynamic_cast<King*>(piece) && piece->get_color() == color) {
                king_position = Position(x, y);
                king_found = true;
                break;
            }
        }
        if (king_found) break;
    }

    
    if (!king_found) {
        return false;
    }
    
    if (!is_under_attack(king_position, color)) {
        return false;
    }

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Position new_position(x, y);
            if (new_position != king_position) {
    
                if (new_position.is_within_bounds()) {
    
                    if (!is_under_attack(new_position, color)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
