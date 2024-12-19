#include <iostream>
#include <vector>
#include <memory>
#include <map>

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
    bool operator<(const pair_t& other) const {
    if (x == other.x) {
        return y < other.y; 
    } else {
        return x < other.x; 
    }
}
};

struct piece_t{
    std::shared_ptr<pair_t> pos;  // to get the actual position of the piece you need to call *p
    std::string color;
    std::string id;
    bool is_moved = false;

    piece_t(std::shared_ptr<pair_t> pos, std::string color, std::string id, bool is_moved)
        : pos(pos), color(color), id(id), is_moved(false) {};
    
    //possible moves
    std::vector<std::shared_ptr<pair_t>> moves(std::map<pair_t, std::shared_ptr<piece_t>> board );
    //only takes into account board limitations
    virtual std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const {return {};}

    virtual ~piece_t() = default; 

    bool operator<(const piece_t& other) const {
        // Compare by color first (e.g., "black" < "white")
        if (color != other.color)
            return color < other.color;

        // If colors are the same, compare by piece ID
        if (id != other.id)
            return id < other.id;

        // If both color and ID are the same, compare by position
        if (pos->x != other.pos->x)
            return pos->x < other.pos->x;

        return pos->y < other.pos->y;  // Compare y-coordinate as a final criterion
    }

    // operator overloading 
};

struct king_t : piece_t{
    king_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "king", false) {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};

struct rook_t : piece_t{
    rook_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "rook", false) {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};

struct bishop_t : piece_t{
    bishop_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "bishop", false) {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};

struct horse_t : piece_t{
    horse_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "horse", false) {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};

struct queen_t : piece_t{
    queen_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "queen", false) {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};

struct pawn_t : piece_t{
    pawn_t(std::shared_ptr<pair_t> pos, std::string color) 
        : piece_t(pos, color, "pawn", false) {};
    std::vector<std::shared_ptr<pair_t>> moves_no_constraints() const;
};


/*------------------------------------OS OPERATOR OVERLOADING------------------------------------------------------*/

std::ostream& operator<<(std::ostream& os, const pair_t& pair);
std::ostream& operator<<(std::ostream& os, const piece_t& piece);
std::ostream& operator<<(std::ostream& os, const std::vector<std::shared_ptr<piece_t>>& pieces);

/*-----------------------------------------global variables----------------------------------------------------------*/

std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::vector<int> numbers = {1,2,3,4,5,6,7,8};


#endif



