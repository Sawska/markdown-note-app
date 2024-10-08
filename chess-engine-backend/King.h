#ifndef KING_H
#define KING_H

#include "chessPiece.h"

class King : public ChessPiece {
public:
    King(bool color, Position position) : ChessPiece(color, position) {}

    bool is_move_valid(Position new_position, Board& board) override {

        int dx = abs(new_position.x - position.x);
        int dy = abs(new_position.y - position.y);
        return (dx <= 1 && dy <= 1);
    }

    std::vector<Position> calculate_valid_moves(const Board& board) override {
        std::vector<Position> valid_moves;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                Position new_position = Position(position.x + dx, position.y + dy);
                if (new_position.is_within_bounds() && !(dx == 0 && dy == 0)) {
                    valid_moves.push_back(new_position);
                }
            }
        }
        return valid_moves;
    }
    std::string serialize() const override {
        return color ? "K" : "k";  
    }
};

#endif // KING_H
