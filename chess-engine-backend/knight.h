#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
public:
    Knight(bool color, Position position) : ChessPiece(color, position) {}

    bool is_move_valid(Position new_position, Board& board) override {
        
        int dx = abs(new_position.x - position.x);
        int dy = abs(new_position.y - position.y);
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }

    std::vector<Position> calculate_valid_moves(Board& board) override {
        std::vector<Position> valid_moves;
        int knight_moves[8][2] = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };

        for (auto &move : knight_moves) {
            Position new_position = Position(position.x + move[0], position.y + move[1]);
            if (new_position.is_within_bounds()) {
                valid_moves.push_back(new_position);
            }
        }
        return valid_moves;
    }
};

#endif // KNIGHT_H
