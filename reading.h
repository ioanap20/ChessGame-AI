#include <iostream>
#include <vector>
#include <fstream>
#include <map>
<<<<<<< HEAD
#include "piece.h"
=======
>>>>>>> 625a5f93aab906beb6c9d993849b88ca3c48ae51
using namespace std;

// lets say the white vector is called whiteVector and the black vector is called blackVector

struct board;

//Should read inherit from board?

struct reading {
    vector <string> readAllLines(int argc, char* argv[]);
    // here i put vector<string> for whiteVector but they should be of type piece i think
    //then should smth inherit from piece?
<<<<<<< HEAD
    void update_white(vector<piece_t>& whiteVector, vector<string>& moves); 
    void update_black(vector<piece_t>& blackVector, vector<string>& moves); 
    
    void update_board(map<pair_t, piece_t>& boardMap, vector<string>& moves);

    //calls the three functions above
    void actualize(map<pair_t, piece_t>& boardMap, vector<piece_t>& whiteVector, vector<piece_t>& blackVector, int argc, char* argv[]);
=======
    void update_white(vector<string>& whiteVector, vector<string>& moves);
    void update_black(vector<string>& blackVector, vector<string>& moves);
    void update_board(map<string, string>& boardMap);
    void actualize(map<string, string>& boardMap, vector<string>& whiteVector, vector<string>& blackVector, int argc, char* argv[]);
>>>>>>> 625a5f93aab906beb6c9d993849b88ca3c48ae51
};