#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include "chess_board.h"
#include "piece.h"
using namespace std;

map<string, bool> is_castling(const chess_board& board, const string& color) {   
     // get the king and rook in my_pieces and see if they have moved
    
    map<std::string, bool> castling_status = {{"kingside", false}, {"queenside", false}};

    for(const auto& piece : board.my_pieces){
        if (piece->id == "king" or piece->id == "rook"){
            if (piece->is_moved){
                return castling_status;
            }
        }
    }

// check if there are any pieces between the king and the rook for both kingside and queenside

// check if is_check for the king before and after castling

// check if it can castle on kings_side





// check if it can castle on the queens_side
    



// we need to find a way to return like a dictionary with the keys being the sides and the values being the boolean values
    

}

// do a function castle(board, color, kingside) that moves the king and the rook to the right positions

// do a function castle(board, color, queenside) that moves the king and the rook to the right positions