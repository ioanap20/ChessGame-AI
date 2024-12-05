#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "reading.h"
#include "chess_board.h" //do we need this for struct chess_board??
#include "chess_board.cpp"//for the print_chess_board functiion?
#include "piece.h" //do we need this for struct pair_t?? yes I think so for update_board
//#include "input.txt"
#include <sstream>
using namespace std;


// Function to read all lines from the file
vector<string> reading::readAllLines(int argc, char *argv[])
{
        // Should we check if the number of arguments is correct?
    string historyFile = argv[2];
    string outputFile = argv[4];

    ifstream infile(historyFile);
    ofstream fout(outputFile); //ofstream writes to output file, probably for the next move we generate

    if (!infile.is_open() || !fout.is_open()) {
        cerr << "Error: Unable to open input or output file." << endl;
        return ;//here we could return an empty string vector to match the type of "reading"??
    }
    
    vector<string> moves;//vector "moves" which stores all lines read from the historyFile
    string line;//temporary variable to hold each line as it is being read


    // Read all lines
    while (getline(infile, line)) {
        if (!line.empty()) {
            moves.push_back(line); // Add line to vector
        }
    }
    infile.close();
    return moves;
}

void reading::update_white(vector<piece_t> &whiteVector, vector<string> &moves)
{
    // update white vector
    // go through all the moves and if the index is even, add the move to the white vector
    // should we have a piece that we make piece.color = white?
}

void reading::update_black(vector<piece_t> &blackVector, vector<string> &moves)
{
    // update black vector
    // go through all the moves and if the index is odd, add the move to the black vector
    // should we have a piece that we make piece.color = black?
}

void reading::update_board(map<pair_t, piece_t> &boardMap, vector<string> &moves)
{
    // update board
    // go thorugh all the moves
    // update the boardMap with the moves
    /*pair_t initial, final;
    initial.x = move[0]
    boardMap.move(initial, final);
    
    how to update a chess board using a history of moves from a text file input.txt, with each line specifying a move in the form (initial_row, initial_column, final_row, final_column)


    g5 - pair_t
    g5g7 - move in moves
    move[0] = g -> pair_t.x
    move[1] = 5 -> pair_t.y
    initial_pos - g5 - string -> pair_t
    last_pos - g7

    .move() will move from the pair_t g5 to the pair_t g7

    */

   //invoke readAllLines to get a working copy of the history file
   vector<string> list_of_moves = readAllLines (input.txt, output.txt);//what are the other 3 parameters, assuming that I am meant to have 5??

   print_chess_board ();//prints out the initial config of board, need some arguments here tho?


   //attempt to loop through the lines one by one until the end of the file?
   while (getline(infile, line)) {
    
        //stringstream ss(line);//prepare to extract before (from) and after (to) moves from a single line
        pair_t from, to;
    
        from.x = line[0];//attempt to parse the line to separate moves. here is the x element of pair_t for the current line?
        from.y = line[1];//same for y

        //pair_t to;

        to.x = line[2];
        to.y = line[3];





   }




}


// maybe this can be done another way i just wanted to have as little as possible in main
void reading::actualize(map<pair_t, piece_t> &boardMap, vector<piece_t> &whiteVector, vector<piece_t> &blackVector, int argc, char** argv)
{
    vector<string> allLines = readAllLines(argc, argv);
    update_white(whiteVector, allLines);
    update_black(blackVector, allLines);
    update_board(boardMap, allLines);
}
