
#include <iostream>
#include "piece.h"
#include "chess_board.h"

/* 

is_promotion_valid() --- checks if we are in a situation to promote
do_promotion() --- carry out the promotion

*/


 

//piece needs to be a pawn
bool is_promotion_valid (piece_t piece, char* our_colour) { //"char*"" --> "string"?


    //the piece needs to be a pawn in order for promotion to be valid
    if (piece_t != pawn_t) {
        return false; 
    }//cannot do an else return treu because we still need to check the other conditions below


    //if black, pawn needs to be on row 1
    if (our_colour = black ) {
        if (*p = {1, {1,8}}) { //*p pointer for pos of pair_t ,,,, {1,8} refers to any column within 1-8.
            return true;
        }
        else {
            return false;
        }
    
    }

    //if white, pawn needs to be on row 8
    else {
        if (*p = {8, {1,8}}) { //*p pointer for pos of pair_t ,,,, {1,8} refers to any column within 1-8.
            return true;
        }
        else {
            return false;
        }
    }  
}



move do_promotion () {

}

