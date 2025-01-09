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
with the same position as the pawn 

and then we delete the old pawn from the map



---------------------------------------------
*/



//copied from piece.cpp, agatha will move this to piece.h later but for now use it here for promotion.cpp
//global variable to store the possible positions
std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::vector<int> numbers = {1,2,3,4,5,6,7,8}; 


void promote_pawn (pair_t pos, const string& color_ai){

    //

}