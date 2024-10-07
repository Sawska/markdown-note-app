cmake_minimum_required(VERSION 3.5.0)
project(chess-engine-backend VERSION 0.1.0 LANGUAGES C CXX)


find_package(PkgConfig REQUIRED)


pkg_check_modules(HIREDIS REQUIRED hiredis)


include_directories(${HIREDIS_INCLUDE_DIRS})


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
    DatabaseClass.cpp
)


target_link_libraries(chess-engine-backend PRIVATE ${HIREDIS_LIBRARIES})
