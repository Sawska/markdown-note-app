#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece {
public:
    Bishop(bool color, Position position) : ChessPiece(color, position) {}

    bool is_move_valid(Position new_position, Board& board) override {

        if (abs(new_position.x - position.x) != abs(new_position.y - position.y)) {
            return false;
        }

        return true;
    }

    std::vector<Position> calculate_valid_moves(Board& board) override {
        std::vector<Position> valid_moves;
        
        for (int i = 1; i < 8; ++i) {
            if (position.x + i < 8 && position.y + i < 8) valid_moves.push_back(Position(position.x + i, position.y + i)); 
            if (position.x - i >= 0 && position.y - i >= 0) valid_moves.push_back(Position(position.x - i, position.y - i)); 
            if (position.x + i < 8 && position.y - i >= 0) valid_moves.push_back(Position(position.x + i, position.y - i)); 
            if (position.x - i >= 0 && position.y + i < 8) valid_moves.push_back(Position(position.x - i, position.y + i)); 
        }
        return valid_moves;
    }
};

#endif // BISHOP_H
