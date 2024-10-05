#ifndef NULL_PIECE_H
#define NULL_PIECE_H

#include "ChessPiece.h"

class NullPiece : public ChessPiece {
public:
    NullPiece(bool color,Position pos) : ChessPiece(color,pos) {}  

    bool is_move_valid(Position, Board&) override {
        return false;  
    }

    void move_piece(Position) override {
        
    }

    std::vector<Position> calculate_valid_moves(Board&) override {
        return {};  
    }
};

#endif // NULL_PIECE_H
