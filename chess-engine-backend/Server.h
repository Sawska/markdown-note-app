#ifndef SERVER_H
#define SERVER_H

#include "crow.h"
#include "ChessEngine.h"
#include "Board.h"
#include "DatabaseClass.h"
#include <cstdlib>
#include "Position.h"


class Server {
    public:
    int id = - 1;
    std::vector<ChessEngine> engines;
    crow::SimpleApp app;
    void set_up_routes();
    void run_server();
    ChessEngine engine;
    Database db;
};

#endif //SERVER_H