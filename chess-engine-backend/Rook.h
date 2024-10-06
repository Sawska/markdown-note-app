#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook : public ChessPiece {
public:
    Rook(bool color, Position position) : ChessPiece(color, position) {}

    bool is_move_valid(Position new_position, Board& board) override {
        Position current_position = this->get_position();
        if (new_position == current_position) return false;

        int dx = new_position.x - current_position.x;
        int dy = new_position.y - current_position.y;


        if ((dx != 0 && dy == 0) || (dx == 0 && dy != 0)) {

            return !is_path_blocked(current_position, new_position, board);
        }

        return false;
    }

    std::vector<Position> calculate_valid_moves(const Board& board) override {
        std::vector<Position> moves;
        Position current_position = this->get_position();

        
        for (int i = 1; i < 8; ++i) {
            Position up(current_position.x - i, current_position.y);
            if (up.is_within_bounds() && !is_path_blocked(current_position, up, board)) {
                moves.push_back(up);
                if (board.get_piece_at(up) != nullptr) break;
            } else break;
        }


        return moves;
    }

private:
    bool is_path_blocked(Position from, Position to, const Board& board) {
        int dx = to.x - from.x;
        int dy = to.y - from.y;

        int step_x = (dx != 0) ? dx / abs(dx) : 0;
        int step_y = (dy != 0) ? dy / abs(dy) : 0;

        Position current = from;
        current.x += step_x;
        current.y += step_y;

        while (current != to) {
            if (board.get_piece_at(current) != nullptr) return true;
            current.x += step_x;
            current.y += step_y;
        }

        return false;
    }
    std::string serialize() const override {
        return color ? "R" : "r";
    }
};

#endif // ROOK_H
