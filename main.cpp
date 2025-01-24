#include <iostream>
#include <fstream>
#include "chess_board.h"
#include "piece.h"
#include "reading.h"
#include "algo.h"
using namespace std;

int main(int argc, char* argv[]) {
    // initialize board (board.cpp): create vectors and map
    // need to link read to those vectors and map and update the board (reading.cpp)
    
    
    chess_board board;

    //cout << "Initial board:" << endl;

    board.display_chess_board();

    reading read(argc, argv, board);
   
    board.set_pieces(read.color_ai);
   
    //cout << "After reading:" << endl;

    

    //cout << "There are enemy pieces: " <<endl;
    /*for (auto& piece : board.enemy_pieces){
        cout<<*piece<<endl;
    }

    cout << "The board has positions: " <<endl;
    for (auto& piece : board.board){
        cout<<piece.first.x<<piece.first.y<<endl;
    }*/

    board.display_chess_board();
    
    //cout <<"****";

    //cout<<"All possible moves"<<endl;
    
    //cout <<"These are my pieces(white pieces): " <<endl;
    /*for (auto& piece : board.my_pieces){
        cout<<*piece<<endl;
        for(auto move:piece->moves(board)){
            cout<<*piece<<" to "<<*move<<endl;
        }
    }*/

    /*for (auto piece:board.my_pieces){

        for (auto correct_move:piece->correct_moves(board)){
            cout<<*piece<<" to "<<*correct_move<<endl;
        }
    }*/




    auto next_move = find_best_move(board, 5);
    

    //cout << "Best move: " << next_move.from.x << next_move.from.y << " to " << next_move.to.x << next_move.to.y << endl;

    board.move(next_move.from, next_move.to);
    
    

    //cout<<"Best move"<<next_move.from.x << next_move.from.y << " to " << next_move.to.x << next_move.to.y << endl;
    
    board.output_move(next_move, argv);
    //cout<<"***"<<endl;
    
    board.display_chess_board();
}
