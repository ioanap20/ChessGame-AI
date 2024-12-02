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
    
    //possible moves
    virtual std::vector<std::shared_ptr<pair_t>> moves(std::vector<std::shared_ptr<pair_t>> pieces);
    //only takes into account board limitations
    virtual std::vector<std::shared_ptr<pair_t>> moves_no_constraints(std::vector<std::shared_ptr<pair_t>> pieces);
};

struct rook_t : piece_t{
    rook_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "rook") {};
    
    std::vector<std::shared_ptr<pair_t>> moves(std::vector<std::shared_ptr<pair_t>> pieces);
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints(std::vector<std::shared_ptr<pair_t>> pieces);
};

struct bishop_t : piece_t{
    bishop_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "bishop") {};
    
    std::vector<std::shared_ptr<pair_t>> moves(std::vector<std::shared_ptr<pair_t>> pieces);
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints(std::vector<std::shared_ptr<pair_t>> pieces);
};

struct horse_t : piece_t{
    horse_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "horse") {};
    
    std::vector<std::shared_ptr<pair_t>> moves(std::vector<std::shared_ptr<pair_t>> pieces);
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints(std::vector<std::shared_ptr<pair_t>> pieces);
};

struct king_t : piece_t{
    king_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "king") {};
    
    std::vector<std::shared_ptr<pair_t>> moves(std::vector<std::shared_ptr<pair_t>> pieces);
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints(std::vector<std::shared_ptr<pair_t>> pieces);
};

struct queen_t : piece_t{
    queen_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "queen") {};
    
    std::vector<std::shared_ptr<pair_t>> moves(std::vector<std::shared_ptr<pair_t>> pieces);
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints(std::vector<std::shared_ptr<pair_t>> pieces);
};

struct pawn_t : piece_t{
    pawn_t(std::vector<std::shared_ptr<pair_t>> pos, std::string color) 
        : piece_t(pos, color, "pawn") {};
    
    std::vector<std::shared_ptr<pair_t>> moves(std::vector<std::shared_ptr<pair_t>> pieces);
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints(std::vector<std::shared_ptr<pair_t>> pieces);
};

#endif


