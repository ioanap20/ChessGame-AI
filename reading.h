#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "piece.h"
using namespace std;

// lets say the white vector is called whiteVector and the black vector is called blackVector

struct board;

//Should read inherit from board?

struct reading {
    vector <string> readAllLines(int argc, char* argv[]);
    // here i put vector<string> for whiteVector but they should be of type piece i think
    //then should smth inherit from piece?
    void update_white(vector<piece_t>& whiteVector, vector<string>& moves); 
    void update_black(vector<piece_t>& blackVector, vector<string>& moves); 
    
    void update_board(map<pair_t, piece_t>& boardMap, vector<string>& moves);

    //calls the three functions above
    void actualize(map<pair_t, piece_t>& boardMap, vector<piece_t>& whiteVector, vector<piece_t>& blackVector, int argc, char* argv[]);
};