#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Position.h"
#include "ChessPiece.h"

class ChessPiece;

class Board {
private:
    std::vector<std::vector<ChessPiece*>> board;

public:
    Board() {
        
        board.resize(8, std::vector<ChessPiece*>(8, nullptr));
    }

    ~Board() {
        
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                delete board[i][j];  
            }
        }
    }

    ChessPiece* get_piece_at(Position pos) const {
        if (pos.is_within_bounds()) {
            return board[pos.x][pos.y];
        }
        return nullptr;
    }

    void set_piece_at(Position pos, ChessPiece* piece) {
        if (pos.is_within_bounds()) {
            board[pos.x][pos.y] = piece;
        }
    }

    void move_piece(Position from, Position to) {
        if (from.is_within_bounds() && to.is_within_bounds()) {
            ChessPiece* piece = board[from.x][from.y];
            board[to.x][to.y] = piece;
            board[from.x][from.y] = nullptr;
            if (piece) {
                piece->move_piece(to);
            }
        }
    }
    void set_piece_at(ChessPiece* piece, Position position) {
        board[position.y][position.x] = piece;
    }
    void remove_piece_at(Position position) {
        board[position.y][position.x] = nullptr;
    }
    ChessPiece* get_piece_at(Position position) {
        return board[position.y][position.x];
    }
    

};

#endif // BOARD_H
