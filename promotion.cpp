#include <iostream>
#include "piece.h"
#include "chess_board.h"
#include <map> 
#include <algorithm>
#include <vector>
using namespace std;


/* 
---------------- METHOD --------------------


1......function that generates a list of valid promotable pawns:


instead of checking single possible piece individually to see if it a pawn and it is on the promotion line

search through the map to find all pawns on the promotion line

return as a list of valid pieces

at most we will only ever have one pawn that can be promoted, so list will almost always be just one pawn





2......function to carry out the promotion?


when we obtain this list with a valid pawn, we add a new promoted piece to the map (default:queen, but we can code for other pieces later),
with the same position as the pawn vector <shared_ptr<piece_t>>

and then we delete the old pawn from the map



---------------------------------------------
*/



//copied from piece.cpp, agatha will move this to piece.h later but for now use it here for promotion.cpp
//global variable to store the possible positions
std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::vector<int> numbers = {1,2,3,4,5,6,7,8}; 


shared_ptr<piece_t> get_piece (chess_board board, const pair_t position) {
    auto it = board.board.find(position);
    if (it != board.board.end()) {
        return it -> second;
    }
    return nullptr;
}




shared_ptr<piece_t> can_we_promote (chess_board board, std::string& my_color){

    vector <shared_ptr<piece_t>> promotion_line; 
    int row;

    if (my_color == "white") {
        row = 8; 
        }
    else {
        row = 1;
    }


    for (char letter:letters){
        pair_t position (letter, row);//creates a position for row = 8
        if (board.board.find(position) != board.board.end() && board.board[position] != nullptr) {
            shared_ptr<piece_t> piece_to_get = get_piece (board, position);
            if (piece_to_get->id == "pawn") {
                return piece_to_get;
            }
        }
    }

    return nullptr;



}