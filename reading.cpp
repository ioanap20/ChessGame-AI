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
    
<<<<<<< HEAD
    vector<string> moves;
=======
    vector<string> lines;
>>>>>>> 625a5f93aab906beb6c9d993849b88ca3c48ae51
    string line;


    // Read all lines
    while (getline(infile, line)) {
        if (!line.empty()) {
<<<<<<< HEAD
            moves.push_back(line); // Add line to vector
        }
    }
    infile.close();
    return moves;
}

void reading::update_white(vector<piece_t> &whiteVector, vector<string> &moves)
=======
            lines.push_back(line); // Add line to vector
        }
    }
    infile.close();
    return lines;
}

void reading::update_white(vector<string> &whiteVector, vector<string> &moves)
>>>>>>> 625a5f93aab906beb6c9d993849b88ca3c48ae51
{
    // update white vector
    // go through all the moves and if the index is even, add the move to the white vector
    // should we have a piece that we make piece.color = white?
}

<<<<<<< HEAD
void reading::update_black(vector<piece_t> &blackVector, vector<string> &moves)
=======
void reading::update_black(vector<string> &blackVector, vector<string> &moves)
>>>>>>> 625a5f93aab906beb6c9d993849b88ca3c48ae51
{
    // update black vector
    // go through all the moves and if the index is odd, add the move to the black vector
    // should we have a piece that we make piece.color = black?
}

<<<<<<< HEAD
void reading::update_board(map<pair_t, piece_t> &boardMap, vector<string> &moves)
{
    // update board
    // go thorugh all the moves
    // update the boardMap with the moves
    /*pair_t initial, final;
    initial.x = move[0]
    boardMap.move(initial, final);*/
=======
void reading::update_board(map<string, string> &boardMap)
{
    // update board
>>>>>>> 625a5f93aab906beb6c9d993849b88ca3c48ae51
}


// maybe this can be done another way i just wanted to have as little as possible in main
<<<<<<< HEAD
void reading::actualize(map<pair_t, piece_t> &boardMap, vector<piece_t> &whiteVector, vector<piece_t> &blackVector, int argc, char** argv)
=======
void reading::actualize(map<string, string> &boardMap, vector<string> &whiteVector, vector<string> &blackVector, int argc, char* argv[])
>>>>>>> 625a5f93aab906beb6c9d993849b88ca3c48ae51
{
    vector<string> allLines = readAllLines(argc, argv);
    update_white(whiteVector, allLines);
    update_black(blackVector, allLines);
<<<<<<< HEAD
    update_board(boardMap, allLines);
=======
    update_board(boardMap);
>>>>>>> 625a5f93aab906beb6c9d993849b88ca3c48ae51
}
