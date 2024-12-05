#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

// lets say the white vector is called whiteVector and the black vector is called blackVector

struct board;

//Should read inherit from board?

struct reading {
    vector <string> readAllLines(int argc, char* argv[]);
    // here i put vector<string> for whiteVector but they should be of type piece i think
    //then should smth inherit from piece?
    void update_white(vector<string>& whiteVector, vector<string>& moves);
    void update_black(vector<string>& blackVector, vector<string>& moves);
    void update_board(map<string, string>& boardMap);
    void actualize(map<string, string>& boardMap, vector<string>& whiteVector, vector<string>& blackVector, int argc, char* argv[]);
};