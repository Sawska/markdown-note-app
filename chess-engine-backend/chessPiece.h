#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <vector>
#include "Board.h"
class Board;

class Move {
public:
    Position from;
    Position to;

    Move(Position f, Position t) : from(f), to(t) {}
};


class ChessPiece {
protected:
    Position position; 

public:
    bool color;  
    ChessPiece(bool color, Position position) : color(color), position(position) {}

    virtual ~ChessPiece() {}

    
    virtual bool is_move_valid(Position new_position, Board& board) = 0;

    virtual void move_piece(Position new_position) {
        position = new_position;  
    }

    virtual std::vector<Position> calculate_valid_moves(const Board& board) = 0;

    bool get_color() const { return color; }  

    Position get_position() const { return position; }  
    virtual std::string serialize() const = 0;
};

#endif //CHESS_PIECE_H
