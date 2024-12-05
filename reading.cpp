#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "reading.h"
using namespace std;


// Function to read all lines from the file
vector<string> reading::readAllLines(int argc, char *argv[])
{
        // Should we check if the number of arguments is correct?
    string historyFile = argv[2];
    string outputFile = argv[4];

    ifstream infile(historyFile);
    ofstream fout(outputFile);

    if (!infile.is_open() || !fout.is_open()) {
        cerr << "Error: Unable to open input or output file." << endl;
        return ;
    }
    
    vector<string> lines;
    string line;


    // Read all lines
    while (getline(infile, line)) {
        if (!line.empty()) {
            lines.push_back(line); // Add line to vector
        }
    }
    infile.close();
    return lines;
}

void reading::update_white(vector<string> &whiteVector, vector<string> &moves)
{
    // update white vector
    // go through all the moves and if the index is even, add the move to the white vector
    // should we have a piece that we make piece.color = white?
}

void reading::update_black(vector<string> &blackVector, vector<string> &moves)
{
    // update black vector
    // go through all the moves and if the index is odd, add the move to the black vector
    // should we have a piece that we make piece.color = black?
}

void reading::update_board(map<string, string> &boardMap)
{
    // update board
}


// maybe this can be done another way i just wanted to have as little as possible in main
void reading::actualize(map<string, string> &boardMap, vector<string> &whiteVector, vector<string> &blackVector, int argc, char* argv[])
{
    vector<string> allLines = readAllLines(argc, argv);
    update_white(whiteVector, allLines);
    update_black(blackVector, allLines);
    update_board(boardMap);
}
