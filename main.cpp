#include <iostream>
#include <fstream>
#include "chess_board.h"
#include "piece.h"
#include "reading.h"
using namespace std;

int main(int argc, char* argv[]) {
    // initialize board (board.cpp): create vectors and map
    // need to link read to those vectors and map and update the board (reading.cpp)
    
    
    chess_board board;

    cout << "Initial board:" << endl;

    board.display_chess_board();

    reading read(argc, argv, board);

    cout << "After reading:" << endl;
    
    board.display_chess_board();

    auto next_move = board.next_move(read.color_ai);
    
    board.move(*next_move[0], *next_move[1]);
    
    board.output_move(next_move, argv);
    
    cout << read.color_ai << " moved and the output is:" << endl;

    board.display_chess_board();
}