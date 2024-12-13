#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "reading.h"
#include "chess_board.h"
using namespace std;


// Function to read all lines from the file
vector<string> reading::readAllLines(int argc, char *argv[])
{
    
    if (argc < 3) {
        std::cerr << "Error: Not enough arguments provided." << std::endl;
        return {}; // Return an empty vector
    }
    
    // Should we check if the number of arguments is correct?
    string historyFile = argv[2];
   // string outputFile = argv[4];

    ifstream infile(historyFile);
    //ofstream fout(outputFile);

     if (!infile.is_open()) {
        std::cerr << "Error: Unable to open input file: " << historyFile << std::endl;
        return {}; // Return an empty vector
    }



    string line;

    // Read all lines
    while (getline(infile, line)) {
        if (!line.empty()) {
            moves.push_back(line); // Add line to vector
        }
    }
    // if i put an '\n' after the input it doesn't work anymore
    
    if (moves.size() % 2 == 0) {
        color_ai = {"white"};
    } else {
        color_ai = {"black"};
    } 
    
    infile.close();
    return moves;
}


void reading::update_board(chess_board& board)
{
    // update board
    // go thorugh all the moves
    // update the boardMap with the moves
    /*pair_t initial, final;
    initial.x = move[0]
    boardMap.move(initial, final);*/

    

    for (size_t i = 0; i < moves.size(); ++i) {
        const string& move = moves[i];

        pair_t from(move[0], move[1] - '0'); // Convert char to int
        pair_t to(move[2], move[3] - '0');


        board.move(from, to);

        
    }

}

reading::reading(int argc, char* argv[], chess_board& board) {
    // Read all lines from the file
    readAllLines(argc, argv);

    // Process the moves
    update_board(board);
}

