#ifndef CHESS_ENGINE_H
#define CHESS_ENGINE_H

#include "Board.h"
#include "chessPiece.h"
#include <vector>
#include <memory>
#include "Pawn.h"
#include "bishop.h"
#include "King.h"
#include "knight.h"
#include "NullPiece.h"
#include "queen.h"
#include "Rook.h"
#include "NullPiece.h"

const int INF = 1000000;

#include <stack>

struct MoveHistory {
    Position from;
    Position to;
    ChessPiece* capturedPiece;

    MoveHistory(Position f, Position t, ChessPiece* captured)
        : from(f), to(t), capturedPiece(captured) {}
};


class ChessEngine {
private:
    Board board;
    bool current_turn;
    std::stack<MoveHistory> move_history;

public:
    ChessEngine();

    void initialize_board();
    bool make_move(Position from,Position to);
    std::vector<Position> get_valid_moves(Position from);
    void switch_turn();
    bool is_checkmate(bool color);
    bool is_under_attack(Position position, bool color);
    int minimax(Board board, int depth, bool maximizingPlayer, int alpha, int beta);
    Position best_move();
    int piece_value(const ChessPiece* piece);
    int evaluate_board(const Board& board);
    void undo_move();
};

#endif //CHESS_ENGINE_H