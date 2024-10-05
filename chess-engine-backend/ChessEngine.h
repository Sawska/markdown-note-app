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

class ChessEngine {
private:
    Board board;
    bool current_turn;

public:
    ChessEngine();

    void initialize_board();
    bool make_move(Position from,Position to);
    std::vector<Position> get_valid_moves(Position from);
    void switch_turn();
    bool is_checkmate(bool color);
    bool is_under_attack(Position position, bool color);
};

#endif //CHESS_ENGINE_H