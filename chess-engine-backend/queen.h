#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "Rook.h"
#include "Bishop.h"

class Queen : public ChessPiece {
public:
    Queen(bool color, Position position) : ChessPiece(color, position) {}

    bool is_move_valid(Position new_position, Board& board) override {

        Rook rook(color, position);
        Bishop bishop(color, position);

        return rook.is_move_valid(new_position, board) || bishop.is_move_valid(new_position, board);
    }

    std::vector<Position> calculate_valid_moves(Board& board) override {
        std::vector<Position> valid_moves;
        Rook rook(color, position);
        Bishop bishop(color, position);

        auto rook_moves = rook.calculate_valid_moves(board);
        auto bishop_moves = bishop.calculate_valid_moves(board);

        valid_moves.insert(valid_moves.end(), rook_moves.begin(), rook_moves.end());
        valid_moves.insert(valid_moves.end(), bishop_moves.begin(), bishop_moves.end());

        return valid_moves;
    }
};

#endif // QUEEN_H
