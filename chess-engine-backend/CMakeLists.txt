cmake_minimum_required(VERSION 3.5.0)
project(chess-engine-backend VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(PkgConfig REQUIRED)
pkg_check_modules(HIREDIS REQUIRED hiredis)

include_directories(${HIREDIS_INCLUDE_DIRS})
include_directories(/opt/homebrew/include)


include_directories("/Users/alexanderkorzh/vcpkg/downloads/Crow-1.2.0/include")
include_directories("/usr/local/include")  

link_directories("/opt/homebrew/Cellar/hiredis/1.2.0/lib")

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
    Server.cpp
)

target_link_libraries(chess-engine-backend PRIVATE ${HIREDIS_LIBRARIES})
