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

    cout << "Initial board:" << endl;

    board.display_chess_board();

    reading read(argc, argv, board);
   
    board.set_pieces(read.color_ai);
   
    cout << "After reading:" << endl;

    cout <<"These are my pieces(white pieces): " <<endl;
    for (auto& piece : board.my_pieces){
        cout<<*piece<<endl;
    }

    cout << "There are enemy pieces: " <<endl;
    for (auto& piece : board.enemy_pieces){
        cout<<*piece<<endl;
    }

    board.display_chess_board();

    auto next_move = find_best_move(board, 1);
    
    board.move(next_move.from, next_move.to);
    
    board.output_move(next_move, argv);
    
    board.display_chess_board();
}
