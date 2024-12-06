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

    board.display_chess_board();

<<<<<<< HEAD

    cout << endl;

=======
>>>>>>> fe595fa769eec27d5edfce170f3c58834a35906f
    reading read(argc, argv, board);

    board.display_chess_board();
}