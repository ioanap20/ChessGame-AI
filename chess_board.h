#include <iostream>
#include <vector>
#include <map>
#include "piece.h"
using namespace std;

#ifndef __CHESS_BOARD__H
#define __CHESS_BOARD__H

struct chess_board{

    string color_ai;
    vector<shared_ptr<piece_t>> my_pieces;
    vector<shared_ptr<piece_t>> enemy_pieces;
    vector<shared_ptr<piece_t>> whitePieces;
    vector<shared_ptr<piece_t>> blackPieces;
    vector<shared_ptr<piece_t>> allPieces;
    map<pair_t, shared_ptr<piece_t>> board;
    void move(pair_t from, pair_t to);
    void display_chess_board();
    void set_pieces(string color);
        
    vector<shared_ptr<pair_t>> next_move(std::string color);

    void output_move(vector<shared_ptr<pair_t>>next_move, char* argv[]);

    chess_board(); 
};

#endif