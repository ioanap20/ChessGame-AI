#include <iostream>
#include <vector>
#include <map>
#include "piece.h"
using namespace std;

struct chess_board{

    vector<piece_t> whitePieces;
    vector<piece_t> blackPieces;
    vector<piece_t> allPieces;
    map<pair_t, piece_t> boardMap;
    void move(pair_t from, pair_t to);

    chess_board();
};