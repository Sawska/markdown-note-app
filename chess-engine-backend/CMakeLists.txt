cmake_minimum_required(VERSION 3.5.0)
project(chess-engine-backend VERSION 0.1.0 LANGUAGES C CXX)

find_package(hiredis REQUIRED)
target_link_libraries(chess-engine-backend hiredis)


add_executable(chess-engine-backend main.cpp
bishop.h
Board.h
ChessEngine.cpp
chessPiece.h
King.h
knight.h
NullPiece.h
Pawn.h
Position.h
queen.h
Rook.h
)

