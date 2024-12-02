#include <iostream>
#include <vector>
#include <memory>

#ifndef __PIECES__
#define __PIECES__

struct pair_t{
    // We model the position (x,y) on the board as x: letter and y: number
    std::string x;
    int y;
};

struct piece_t{
    std::vector<std::shared_ptr<pair_t>> pos;
    std::string color;
    bool taken;
    std::string id;

    piece_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color, std::string id)
        : pos(pos), color(color), taken(false), id(id) {};
};

struct rook_t : piece_t{
    rook_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "rook") {};
};

struct bishop_t : piece_t{
    bishop_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "bishop") {};
};

struct horse_t : piece_t{
    horse_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "horse") {};
};

struct king_t : piece_t{
    king_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "king") {};
};

struct queen_t : piece_t{
    queen_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "queen") {};
};

struct pawn_t : piece_t{
    pawn_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "pawn") {};
};

#endif


