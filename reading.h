#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "piece.h"
#include "chess_board.h"
using namespace std;

#ifndef __READING__H
#define __READING__H

// lets say the white vector is called whiteVector and the black vector is called blackVector
//Should read inherit from board?

struct reading {

    vector<string> moves;
    
    reading(int argc, char* argv[], chess_board& board);

    vector <string> readAllLines(int argc, char* argv[]);

            
    // here i put vector<string> for whiteVector but they should be of type piece i think
    //then should smth inherit from piece?

    void update_board(chess_board& board);

    string color_ai;

};

#endif