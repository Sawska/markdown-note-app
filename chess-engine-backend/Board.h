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
    std::string serialize() const {
        std::string serialized_board;

        for (const auto& row : board) {
            for (const auto& piece : row) {
                serialized_board += piece->serialize();
            }
            serialized_board += "\n"; 
        }

        return serialized_board;
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

    std::vector<std::vector<ChessPiece*>> get_board() {
        return board;
    }
    const std::vector<std::vector<ChessPiece*>>& get_board() const {
        return board;
    }
     std::vector<Move> get_valid_moves(bool color) {
    std::vector<Move> valid_moves;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            ChessPiece* piece = board[i][j];
            if (piece && piece->get_color() == color) {
                std::vector<Position> moves = piece->calculate_valid_moves(*this);
                for (const auto& move : moves) {
                    valid_moves.push_back(Move({i, j}, move));  
                }
            }
        }
    }

    return valid_moves;
}


};

#endif // BOARD_H
