#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include "chess_board.h"
#include "piece.h"
using namespace std;

tuple<bool, bool> is_castling(const chess_board& board, const std::string& color){    
// get the king and rook in my_pieces and see if they have moved
    
    for(const auto& piece : board.my_pieces){
        if (piece->id == "king" or piece->id == "rook"){
            if (piece->is_moved){
                return {false, false};
            }
        }
    }

// check if it can castle on kings_side





// check if it can castle on the queens_side
    



// we need to find a way to return like a dictionary with the keys being the sides and the values being the boolean values
    

}

// do a function castle(board, color, kingside) that moves the king and the rook to the right positions

// do a function castle(board, color, queenside) that moves the king and the rook to the right positions