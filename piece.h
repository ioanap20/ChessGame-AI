#include <iostream>
#include <vector>
#include <memory>

#ifndef __PIECES__
#define __PIECES__

struct pair_t{
    // We model the position (x,y) on the board as x: letter and y: number
    char x;
    int y;

    pair_t(char x, int y) : x(x), y(y) {}

    bool operator==(const pair_t& other) const {
        return x==other.x && y==other.y;
    };
};

struct piece_t{
    std::shared_ptr<pair_t> pos;  // to get the actual position of the piece you need to call *p
    std::string color;
    bool taken;
    std::string id;

    piece_t(std::shared_ptr<pair_t> pos, std::string color, std::string id)
        : pos(pos), color(color), taken(false), id(id) {};
    
    //possible moves
    std::vector<std::shared_ptr<pair_t>> moves(std::vector<std::shared_ptr<piece_t>>& pieces);
    //only takes into account board limitations
    virtual std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const {return {};}

    virtual ~piece_t() = default; 

    // operator overloading 
};

struct king_t : piece_t{
    king_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "king") {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};

struct rook_t : piece_t{
    rook_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "rook") {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};

struct bishop_t : piece_t{
    bishop_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "bishop") {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};

struct horse_t : piece_t{
    horse_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "horse") {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};

struct queen_t : piece_t{
    queen_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "queen") {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};

struct pawn_t : piece_t{
    pawn_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "pawn") {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};


/*------------------------------------OS OPERATOR OVERLOADING------------------------------------------------------*/

std::ostream& operator << (std::ostream& os, const pair_t& pair){
    return os<<pair.x<<pair.y;
};

std::ostream& operator << (std::ostream& os, const piece_t& piece){
    return os<<piece.color<<" "<<piece.id<<" at "<< *piece.pos<< "  Status : "<<piece.taken;
};

std::ostream& operator << (std::ostream& os, const std::vector<std::shared_ptr<piece_t>> pieces){
    for (const auto& piece : pieces){
        os<<*piece<<std::endl;
    }
    return os;
}

#endif



