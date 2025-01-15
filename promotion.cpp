#include <iostream>
#include "piece.h"
#include "chess_board.h"
#include <map> 
#include <algorithm>
#include <vector>
using namespace std;



//copied from piece.cpp, agatha will move this to piece.h later but for now use it here for promotion.cpp
//global variable to store the possible positions
std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::vector<int> numbers = {1,2,3,4,5,6,7,8}; 




shared_ptr<piece_t> get_piece (chess_board& board, const pair_t position) {
    auto it = board.board.find(position);
    if (it != board.board.end()) {
        return it -> second;
    }
    return nullptr;
}




shared_ptr<piece_t> can_we_promote (chess_board& board, string& my_color){

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


void do_promotion (chess_board& board, shared_ptr<piece_t> pawn, const char promote_to, const string& my_color) {
    shared_ptr<piece_t> new_piece;
    if (promote_to == 'q') {
        new_piece = make_shared<queen_t> (pawn->pos, pawn->color); //created a new queen
    }
    if (promote_to == 'r') {
        new_piece = make_shared<rook_t> (pawn->pos, pawn->color); //created a new rook
    }
    if (promote_to == 'b') {
        new_piece = make_shared<bishop_t> (pawn->pos, pawn->color); //created a new bishop
    }
    if (promote_to == 'h') {
        new_piece = make_shared<horse_t> (pawn->pos, pawn->color); //created a new knight
    }


    //add new (promoted) piece to board

    //remove the pawn and replace with the new piece
    board.remove_piece(pawn);


    //board.board.erase(*(pawn->pos));
    board.board[*(pawn->pos)] = new_piece;
    




    //add new_piece to the list of current colour pieces
    vector <shared_ptr<piece_t>>& pieces_list = (my_color == "white") ? board.whitePieces : board.blackPieces; //equivalent to an if statement
 
    pieces_list.push_back(new_piece);


    //add new_piece to the list of allPieces
    board.allPieces.push_back(new_piece);

    cout <<"After that promotion the black pieces are: " << endl;
    for (shared_ptr<piece_t> piece : board.blackPieces) {
        cout << *piece << endl;
    }


    cout << "The player has promoted the pawn to a " << promote_to << endl;
    cout << "Now we have " << *new_piece << endl;
    //cout <<"Now there are " <<board.blackPieces.size() << " black pieces" << endl;
    //cout <<"The black pieces are: " << endl;
    /*for (shared_ptr<piece_t> piece : board.blackPieces) {
        cout << *piece << endl;
    }*/

}
