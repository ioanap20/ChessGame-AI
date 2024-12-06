#include <iostream>
#include <vector>
#include <map>
#include "piece.h"
using namespace std;

#ifndef __CHESS_BOARD__H
#define __CHESS_BOARD__H

struct chess_board{

    vector<shared_ptr<piece_t>> whitePieces;
    vector<shared_ptr<piece_t>> blackPieces;
    vector<shared_ptr<piece_t>> allPieces;
    map<pair_t, std::shared_ptr<piece_t>> board;
    void move(pair_t from, pair_t to);
    void display_chess_board();
        
    vector<shared_ptr<pair_t>> next_move(std::string color);

    void output_move(vector<shared_ptr<pair_t>>next_move);

    chess_board();
};

#endif