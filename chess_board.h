#include <iostream>
#include <vector>
#include <map>
#include "piece.h"
using namespace std;

#ifndef __CHESS_BOARD__H
#define __CHESS_BOARD__H

struct Move;

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
    void remove_piece(const shared_ptr<piece_t>& captured_piece);

    piece_t get_king(string color);

    chess_board clone();

    bool is_game_over();

    void output_move(Move next_move, char* argv[]);

    chess_board(); 
};

#endif