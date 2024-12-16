#include <iostream>
#include <vector>
#include <fstream>
#include "chess_board.h"
#include "reading.h"
using namespace std;


chess_board::chess_board() {

    // white pieces (row 1)

    whitePieces.push_back(std::make_shared<rook_t>(std::make_shared<pair_t>('a', 1), "white"));
    whitePieces.push_back(std::make_shared<horse_t>(std::make_shared<pair_t>('b', 1), "white"));
    whitePieces.push_back(std::make_shared<bishop_t>(std::make_shared<pair_t>('c', 1), "white"));
    whitePieces.push_back(std::make_shared<queen_t>(std::make_shared<pair_t>('d', 1), "white"));
    whitePieces.push_back(std::make_shared<king_t>(std::make_shared<pair_t>('e', 1), "white"));
    whitePieces.push_back(std::make_shared<bishop_t>(std::make_shared<pair_t>('f', 1), "white"));
    whitePieces.push_back(std::make_shared<horse_t>(std::make_shared<pair_t>('g', 1), "white"));
    whitePieces.push_back(std::make_shared<rook_t>(std::make_shared<pair_t>('h', 1), "white"));

    // white pawns (row 2)
    for (char col = 'a'; col <= 'h'; ++col) {
        whitePieces.push_back(std::make_shared<pawn_t>(std::make_shared<pair_t>(col, 2), "white"));
    }

    // black pieces (row 8)
    blackPieces.push_back(std::make_shared<rook_t>(std::make_shared<pair_t>('a', 8), "black"));
    blackPieces.push_back(std::make_shared<horse_t>(std::make_shared<pair_t>('b', 8), "black"));
    blackPieces.push_back(std::make_shared<bishop_t>(std::make_shared<pair_t>('c', 8), "black"));
    blackPieces.push_back(std::make_shared<queen_t>(std::make_shared<pair_t>('d', 8), "black"));
    blackPieces.push_back(std::make_shared<king_t>(std::make_shared<pair_t>('e', 8), "black"));
    blackPieces.push_back(std::make_shared<bishop_t>(std::make_shared<pair_t>('f', 8), "black"));
    blackPieces.push_back(std::make_shared<horse_t>(std::make_shared<pair_t>('g', 8), "black"));
    blackPieces.push_back(std::make_shared<rook_t>(std::make_shared<pair_t>('h', 8), "black"));

    // black pawns (row 7)
    for (char col = 'a'; col <= 'h'; ++col) {
        blackPieces.push_back(std::make_shared<pawn_t>(std::make_shared<pair_t>(col, 7), "black"));
    }

    allPieces.reserve(whitePieces.size() + blackPieces.size());
    allPieces.insert(allPieces.end(), whitePieces.begin(), whitePieces.end());
    allPieces.insert(allPieces.end(), blackPieces.begin(), blackPieces.end());

    // Initialize white pieces
    for (const auto& piece : whitePieces) {
        board[*piece->pos] = piece;
        piece->is_moved = false;
    }

    // Initialize black pieces
    for (const auto& piece : blackPieces) {
        board[*piece->pos] = piece;
        piece->is_moved = false;
    } 
    
}

void chess_board :: set_pieces(string color){
    color_ai = color;
    if(color_ai == "white"){
        my_pieces = whitePieces;
        enemy_pieces = blackPieces;
    } else {
        my_pieces = blackPieces;
        enemy_pieces = whitePieces;
    }
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
    initial_piece->is_moved = true;
    
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

