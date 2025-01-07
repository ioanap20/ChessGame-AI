
#include <iostream>
#include "piece.h"
#include "chess_board.h"
#include <map> //keeps a record of the pieces currently occupying squares, does not store the empty spaces
#include <algorithm> //for the .find 
#include <vector>
using namespace std;

/* 

is_promotion_valid() --- checks if we are in a situation to promote
do_promotion() --- carry out the promotion

*/



/* --------------------USE MAPS AND VECTORS FOR IS_PROMOTION_VALID ---------------------*/
 

//copied from piece.cpp, agatha will move this to piece.h later but for now use it here for promotion.cpp
//global variable to store the possible positions
std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::vector<int> numbers = {1,2,3,4,5,6,7,8};



//piece needs to be a pawn
vector is_promotion_valid (piece_t piece, char* our_colour) { //"char*"" --> "string"?


    //the piece needs to be a pawn in order for promotion to be valid
    if (piece_t != pawn_t) {
        return false; 
    }//cannot do an else return treu because we still need to check the other conditions below


    //if black, pawn needs to be on row 1
    if (our_colour = black ) {
        if (*pos = {1, {1,8}}) { //*pos pointer for pos of pair_t ,,,, {1,8} refers to any column within 1-8.
            return true;
        }
        else {
            return false;
        }
    
    }

    //if white, pawn needs to be on row 8
    else {
        if (*pos = {8, {1,8}}) { //*pos pointer for pos of pair_t ,,,, {1,8} refers to any column within 1-8.
            return true;
        }
        else {
            return false;
        }
    }  
}



move do_promotion () {

    if (is_promotion_valid()) {

        /* 

        if is_promotion_valid() is true

        we need to receive a list of pawns that satisfy the condition.
        should we modify is_promotion_valid() to return the pieces for which it is true?


        for these pieces, we can output a new move with the current position and then q/r/b/k.
        we can for now always default to q because it is the most powerful piece on the board



        however, promotion is one output move, not two moves
        so we need the pawns to move to the correct position (the end of the board) and then also promote to a new piece.
        hmmmmmm
        
        */





    }

}

