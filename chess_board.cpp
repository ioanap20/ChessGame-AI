#include <iostream>
#include <vector>
#include <fstream>
#include "chess_board.h"
#include <algorithm>
#include "reading.h"
#include "algo.h"
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

void chess_board :: remove_piece(const std::shared_ptr<piece_t>& captured_piece){

    //cout <<"This piece was captured: "<<*captured_piece<<endl;

    // Helper lambda to compare underlying objects
    auto cmp = [&](const std::shared_ptr<piece_t>& p) {
        return p.get() == captured_piece.get();
    };

    // Remove from whitePieces
    whitePieces.erase(
        std::remove_if(whitePieces.begin(), whitePieces.end(), cmp),
        whitePieces.end()
    );

    // Remove from blackPieces
    blackPieces.erase(
        std::remove_if(blackPieces.begin(), blackPieces.end(), cmp),
        blackPieces.end()
    );

    // Remove from allPieces
    allPieces.erase(
        std::remove_if(allPieces.begin(), allPieces.end(), cmp),
        allPieces.end()
    );

    // Remove from board
    board.erase(*captured_piece->pos);

}


void chess_board::move(pair_t from, pair_t to) {
    // move piece from one position to another
    // update boardMap

    // Find the piece at the 'from' position
    auto initial = board.find(from);

    // Check if the 'from' position exists
    if (initial == board.end() || !initial->second) {
        //cout << from << endl<<to<<endl;
        //throw std::runtime_error("Invalid move: No piece found at the 'from' position.");
        return;
    }

    auto destination = board.find(to);

    if (destination != board.end() && destination->second->color != initial->second->color) {
        // If the destination is occupied by an enemy piece, remove it
        remove_piece(destination->second);
        
    }

    if(initial->second->id == "king" && abs(from.x - to.x) == 2){
        // Castling
        if (to.x == 'g') {
            // Kingside castling
            move(pair_t('h', from.y), pair_t('f', from.y));
        } 
    }


    // ---------- If we can promote a pawn, do it here ----------
    if (initial->second->id == "pawn" and initial->second->color == color_ai) {
        if (initial->second->color == "white" && to.y == 8) {
            // White pawn reached the end of the board
            // Promote to a queen
            do_promotion(*this, initial->second, 'q', initial->second->color);

        } else if (initial->second->color == "black" && to.y == 1) {
            // Black pawn reached the end of the board
            // Promote to a queen
            do_promotion(*this, initial->second, 'q', initial->second->color);
        }
    }

    auto initial_piece = initial->second; // Pointer to the piece_t
    initial_piece->pos = make_shared<pair_t>(to); // Update the position of the piece

    // Erase the old position
    board.erase(from);

    // Move the piece to the new position
    board[to] = initial_piece;
    initial_piece->is_moved = true;

    //cout << "Moved " << initial_piece->id << " from " << from << " to " << to << endl;
    
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

void chess_board::output_move(Move next_move, char* argv[]) {
    string output_file = argv[4];
    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "Error: Unable to open output file: output.txt" << endl;
        return;
    }
    string add = "";
    auto piece = next_move.moved_piece;
    if (piece->id == "pawn"){
        if (color_ai=="white"){
            if ((next_move.to).y == 8){
                add = "q";
            }
        } else {
            if (color_ai=="black"){
                if ((next_move.to).y == 1){
                    add = "q";
                }
            } 
        } 
    } 

    outfile << next_move.from << next_move.to << endl;
    
}

vector<shared_ptr<pair_t>> get_all_possible_moves(chess_board board, string color){
        vector<shared_ptr<pair_t>> all_possible_moves = {};
        for (auto& piece : board.my_pieces){
            auto moves = (*piece).correct_moves(board);
            all_possible_moves.insert(all_possible_moves.end(), moves.begin(), moves.end());
        }
        return all_possible_moves;
    }

chess_board chess_board::clone(){
    chess_board new_board;
    new_board.color_ai = color_ai;

    // Clone white pieces
    for (const auto& piece : whitePieces) {
        if (!piece) continue;
        shared_ptr<piece_t> cloned_piece = std::make_shared<piece_t>(piece->clone());
        new_board.whitePieces.push_back(cloned_piece);
        new_board.allPieces.push_back(cloned_piece);
        new_board.board[*cloned_piece->pos] = cloned_piece;
    }

    // Clone black pieces
    for (const auto& piece : blackPieces) {
        if (!piece) continue;
        std::shared_ptr<piece_t> cloned_piece = std::make_shared<piece_t>(piece->clone());
        new_board.blackPieces.push_back(cloned_piece);
        new_board.allPieces.push_back(cloned_piece);
        new_board.board[*cloned_piece->pos] = cloned_piece;
    }

    return new_board;
}

chess_board chess_board::clone_converse(){
    chess_board new_board;
    new_board.color_ai = (color_ai=="white") ? "black" : "white";

    // Clone white pieces
    for (const auto& piece : whitePieces) {
        if (!piece) continue;
        shared_ptr<piece_t> cloned_piece = std::make_shared<piece_t>(piece->clone());
        new_board.whitePieces.push_back(cloned_piece);
        new_board.allPieces.push_back(cloned_piece);
        new_board.board[*cloned_piece->pos] = cloned_piece;
    }

    // Clone black pieces
    for (const auto& piece : blackPieces) {
        if (!piece) continue;
        std::shared_ptr<piece_t> cloned_piece = std::make_shared<piece_t>(piece->clone());
        new_board.blackPieces.push_back(cloned_piece);
        new_board.allPieces.push_back(cloned_piece);
        new_board.board[*cloned_piece->pos] = cloned_piece;
    }

    return new_board;
}

bool chess_board :: is_game_over(){
    for(auto piece : my_pieces){
        if (!piece->correct_moves(*this).empty()){
            return false;
        }
    }
    return true;
}

