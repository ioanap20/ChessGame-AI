#include <map>
#include <vector>
#include "piece.h"
#include "chess_board.h"
#include <iostream>
#include <algorithm>

using namespace std;

piece_t get_my_king(string my_color, chess_board chessboard){   
    vector<shared_ptr<piece_t>> my_pieces = chessboard.my_pieces;
    /*
    //vector<shared_ptr<piece_t>> opponent_pieces;
    if (my_color =="white"){
        my_pieces = chessboard.whitePieces;
        //opponent_pieces = chessboard.blackPieces;
    } else {
        my_pieces = chessboard.blackPieces;
        //opponent_pieces = chessboard.whitePieces;
    } */

    auto it = find_if(my_pieces.begin(), my_pieces.end(), [](const shared_ptr<piece_t>& piece){
                    return (*piece).id == "king";
                });
    
    return **it;
}

/*
int main(int argc, char* argv[]){
    king_t king(std::make_shared<pair_t>('f', 2), "white");
    vector<shared_ptr<piece_t>> pieces;
    return 0;
}
*/