#include <iostream>
#include <vector>
#include <fstream>
#include "chess_board.h"
using namespace std;


chess_board::chess_board() {

    whitePieces = { make_shared<piece_t>(make_shared<pair_t>('a', 1), "white", "rook"),
        make_shared<piece_t>(make_shared<pair_t>('b', 1), "white", "knight"),
        make_shared<piece_t>(make_shared<pair_t>('c', 1), "white", "bishop"),
        make_shared<piece_t>(make_shared<pair_t>('d', 1), "white", "queen"),
        make_shared<piece_t>(make_shared<pair_t>('e', 1), "white", "king"),
        make_shared<piece_t>(make_shared<pair_t>('f', 1), "white", "bishop"),
        make_shared<piece_t>(make_shared<pair_t>('g', 1), "white", "knight"),
        make_shared<piece_t>(make_shared<pair_t>('h', 1), "white", "rook")
    };

    for (char col = 'a'; col <= 'h'; ++col) {
        whitePieces.push_back(make_shared<pawn_t>(make_shared<pair_t>(col, 2), "white"));
    }

    blackPieces = {
        make_shared<piece_t>(make_shared<pair_t>('a', 8), "black", "rook"),
        make_shared<piece_t>(make_shared<pair_t>('b', 8), "black", "knight"),
        make_shared<piece_t>(make_shared<pair_t>('c', 8), "black", "bishop"),
        make_shared<piece_t>(make_shared<pair_t>('d', 8), "black", "queen"),
        make_shared<piece_t>(make_shared<pair_t>('e', 8), "black", "king"),
        make_shared<piece_t>(make_shared<pair_t>('f', 8), "black", "bishop"),
        make_shared<piece_t>(make_shared<pair_t>('g', 8), "black", "knight"),
        make_shared<piece_t>(make_shared<pair_t>('h', 8), "black", "rook"),
    };
    
    for (char col = 'a'; col <= 'h'; ++col) {
        blackPieces.push_back(make_shared<pawn_t>(make_shared<pair_t>(col, 7), "black"));
    }
        

    allPieces.reserve(whitePieces.size() + blackPieces.size());
    allPieces.insert(allPieces.end(), whitePieces.begin(), whitePieces.end());
    allPieces.insert(allPieces.end(), blackPieces.begin(), blackPieces.end());

    // Initialize white pieces
    for (const auto& piece : whitePieces) {
        board[*piece->pos] = piece;
    }

    // Initialize black pieces
    for (const auto& piece : blackPieces) {
        board[*piece->pos] = piece;
    } 
    
    /*return {
        'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', // Black
        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 
        '.', '.', '.', '.', '.', '.', '.', '.', 
        '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.',
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 
        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'  // White
    };*/
}

void chess_board::move(pair_t from, pair_t to) {
    // move piece from one position to another
    // update boardMap

    // Find the piece at the 'from' position
    auto initial = board.find(from);

    // Check if the 'from' position exists
    if (initial == board.end() || !initial->second) {
        throw std::runtime_error("Invalid move: No piece found at the 'from' position.");
    }

    auto initial_piece = initial->second; // Pointer to the piece_t
    initial_piece->pos = make_shared<pair_t>(to); // Update the position of the piece

    // Erase the old position
    board.erase(from);

    // Move the piece to the new position
    board[to] = initial_piece;
    
}


void chess_board :: display_chess_board() {
    cout << "--------------------\n";
    for (int i = 8; i >= 1; i--) { 
        cout << i << "| ";
        for (char j = 'a'; j <= 'h'; j++) { // Loop through columns
            pair_t pos(j, i);
            auto piece = board.find(pos);
            if (piece == board.end()) {
                    // If no piece is found, display an empty space
                    cout << ". ";
                } else {
                    // If a piece is found, determine its symbol
                    char piece_char = piece->second->id[0];
                    if (piece->second->id == "knight"){
                        if (piece->second->color == "white"){
                            piece_char = 'N';
                        } else {
                            piece_char = 'n';
                        }
                    } 
                    else if (piece->second->color == "white") {
                        piece_char = toupper(piece_char);
                    }
                    
                    cout << piece_char << " ";
                }
        }
        cout << "|\n"; 
    }
    cout << "--------------------\n";
    cout << "   a b c d e f g h\n";
}

void chess_board::output_move(vector<shared_ptr<pair_t>> next_move, char* argv[]) {
    string output_file = argv[4];
    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "Error: Unable to open output file: output.txt" << endl;
        return;
    }

    outfile << *next_move[0] << *next_move[1] << endl;
    
}

/*int main(){
    std::vector<char> chess_board = initialize_chess_board();
    print_chess_board(chess_board);
    return 0;
}*/

