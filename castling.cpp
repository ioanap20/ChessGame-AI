#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include "chess_board.h"
#include "piece.h"
using namespace std;


map<string, bool> is_castling(const chess_board& chess_board, const string& color_ai) {   
    
    map<std::string, bool> castling_status = {{"kingside", false}, {"queenside", false}};
    
    int row = (color_ai == "white") ? 1 : 8;
    shared_ptr<piece_t> king;
    shared_ptr<piece_t> kingside_rook;
    shared_ptr<piece_t> queenside_rook;

    // check if the king has moved
    pair_t king_pos('e', row);
    if (chess_board.board.find(king_pos) != chess_board.board.end()) {
        king = chess_board.board.at(king_pos);
        if (king->id == "king" || king->is_moved) {
            return castling_status;
        }
    }
    


    // helper function to check if the path is clear
    auto is_path_clear = [&](char start, char end) {
        for (char col = start; col <= end; ++col) {
            pair_t pos(col, row);
            if (chess_board.board.find(pos) != chess_board.board.end()) {
                return false; // A piece is blocking the path
            }
        }
        return true;
    };

// check if there are any pieces between the king and the rook for both kingside and queenside

// check if is_check for the king before and after castling

// check if there are any pieces between the king and the rook for both kingside and queenside

// check if is_check for the king before and after castling

// check if it can castle on kings_side

    pair_t kingside_rook_pos('h', row);
    if (chess_board.board.find(kingside_rook_pos) != chess_board.board.end()) {
        kingside_rook = chess_board.board.at(kingside_rook_pos);
        if (kingside_rook->id == "rook" && !kingside_rook->is_moved) {
            if (is_path_clear('e', 'h')) {
                castling_status["kingside"] = true;
            }
        }
    }

// check if it can castle on the queens_side
    



return castling_status;

}

// do a function castle(board, color, side) that moves the king and the rook to the right positions

std::pair<pair_t, pair_t> castle(chess_board& board, const std::string& color_ai, const std::string side) {
    int row = (color_ai == "white") ? 1 : 8; // Determine the row based on color
    pair_t king_from('e', row);
    pair_t rook_from('h', row);
    
    if (side == "kingside") {
        // Move the king from e1/e8 to g1/g8
        pair_t king_to('g', row);

        // Move the rook from h1/h8 to f1/f8
        pair_t rook_to('f', row);

        // Update the board
        board.move(king_from, king_to);
        board.move(rook_from, rook_to);
    } 

    // else if (side == "queenside") {



    return {king_from, rook_from};
}