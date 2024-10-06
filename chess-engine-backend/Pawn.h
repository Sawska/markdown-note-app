#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
public:
    Pawn(bool color, Position position) : ChessPiece(color, position) {}

    bool is_move_valid(Position new_position, Board& board) override {
        int direction = (color == true) ? 1 : -1;

        Position current_position = this->get_position();
        if (new_position == current_position) return false;

        int dx = new_position.x - current_position.x;
        int dy = new_position.y - current_position.y;

        
        if (dx == direction && dy == 0 && board.get_piece_at(new_position) == nullptr) {
            return true;
        }

        
        if (dx == 2 * direction && dy == 0 && current_position.x == (color ? 1 : 6) && board.get_piece_at(new_position) == nullptr) {
            return true;
        }

        
        if (dx == direction && std::abs(dy) == 1 && board.get_piece_at(new_position) != nullptr) {
            return true;
        }

        return false;
    }

    std::vector<Position> calculate_valid_moves(const Board& board) override {
        std::vector<Position> moves;
        Position current_position = this->get_position();
        int direction = (color == true) ? 1 : -1;

        
        Position one_step_forward(current_position.x + direction, current_position.y);
        if (board.get_piece_at(one_step_forward) == nullptr && one_step_forward.is_within_bounds()) {
            moves.push_back(one_step_forward);
        }

        Position two_steps_forward(current_position.x + 2 * direction, current_position.y);
        if (board.get_piece_at(two_steps_forward) == nullptr && current_position.x == (color ? 1 : 6) && two_steps_forward.is_within_bounds()) {
            moves.push_back(two_steps_forward);
        }

        
        Position capture_left(current_position.x + direction, current_position.y - 1);
        Position capture_right(current_position.x + direction, current_position.y + 1);

        if (capture_left.is_within_bounds() && board.get_piece_at(capture_left) != nullptr && board.get_piece_at(capture_left)->get_color() != color) {
            moves.push_back(capture_left);
        }
        if (capture_right.is_within_bounds() && board.get_piece_at(capture_right) != nullptr && board.get_piece_at(capture_right)->get_color() != color) {
            moves.push_back(capture_right);
        }

        return moves;
    }
    std::string serialize() const override {
        return color ? "P" : "p"; 
    }
};

#endif // PAWN_H
