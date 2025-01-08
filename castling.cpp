#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include "chess_board.h"
#include "piece.h"
using namespace std;

std::shared_ptr<piece_t> get_piece(const chess_board& board, const pair_t& position) {
    auto it = board.board.find(position); // Search for the position in the board map
    if (it != board.board.end()) {
        return it->second; // Return the piece if found
    }
    return nullptr; // Return nullptr if no piece is found
}


map<string, bool> is_castling(chess_board& chess_board, const string& color_ai) {   
    
    map<std::string, bool> castling_status = {{"kingside", false}, {"queenside", false}};
    // if it can castle --> we initialize status to no
    
    int row = (color_ai == "white") ? 1 : 8;

 //(------------check if the king has moved----------------)
    pair_t king_pos('e', row);

    // Check if the king is in its starting position and hasn't moved
    auto king = std::dynamic_pointer_cast<king_t>(get_piece(chess_board, king_pos));
    if (!king || king->is_moved) {
        return castling_status; // No king or king has already moved
    }

//(----------- helper function to check if the path is clear ----------------)
    // gretl: i edited this to handle descending ranges as well (queenside)
    auto is_path_clear = [&](char start, char end) {
        char lower = std::min(start, end);
        char upper = std::max(start, end);
        for (char col = lower + 1; col < upper; ++col) {
            pair_t pos(col, row);
            if (chess_board.board.find(pos) != chess_board.board.end()) {
                return false; // A piece is blocking the path
            }
        }
        return true;
    };

//(-------------- helper function is_check if the king is in check ----------------)
    // agatha has is_check() (to be finished) --> for now, using this impl
    auto is_check = [&]() {
        for (const auto& [pos, piece] : chess_board.board) {    
            if (piece->color != color_ai) {  // Opponent's piece
                auto potential_moves = piece->moves_no_constraints();
                for (auto& move : potential_moves) {
                    if (*move == king_pos) {
                        return true;  // King is in check
                    }
                }
            }
        }
        return false;  // King is not in check
    };
    
    //(----------- check if is_check for the king before and after castling 
    if (is_check()){
        castling_status["kingside"] = false;
        castling_status["queenside"] = false;
        // if in check, you cannot castle on either side
        return castling_status;
    }


//(------------ check if it can castle on kings_side ----------------)
    // gretl: i edited this to handle descending ranges as well (queenside)
    // check if it can castle on kings_side
    if (is_path_clear('e', 'h')) {
        pair_t kingside_rook_pos('h', row);
        auto rook = std::dynamic_pointer_cast<rook_t>(get_piece(chess_board, kingside_rook_pos));
        if (rook && !rook->is_moved) {
            // Simulate the castling move
            castle(chess_board, color_ai, "kingside", true);

            // Check if the king is in check after castling
            if (!is_check()) {
                castling_status["kingside"] = true;
            }

            // Revert the move
            chess_board.move(pair_t('g', row), king_pos); // Move king back
            chess_board.move(pair_t('f', row), kingside_rook_pos); // Move rook back
        }
    }

//(------------ check if it can castle on the queens_side ----------------)
if (is_path_clear('e', 'a')) {
        pair_t queenside_rook_pos('a', row);
        auto rook = std::dynamic_pointer_cast<rook_t>(get_piece(chess_board, queenside_rook_pos));
        if (rook && !rook->is_moved) {
            // Simulate the castling move
            castle(chess_board, color_ai, "queenside", true);

            // Check if the king is in check after castling
            if (!is_check()) {
                castling_status["queenside"] = true;
            }

            // Revert the move
            chess_board.move(pair_t('c', row), king_pos); // Move king back
            chess_board.move(pair_t('d', row), queenside_rook_pos); // Move rook back
        }
    }

return castling_status;

}

void castle(chess_board& board, const std::string& color_ai, const std::string& side, bool simulate = false) {
    int row = (color_ai == "white") ? 1 : 8; // Determine the row based on color
    pair_t king_from('e', row); // starting pos of king

    if (side == "kingside") {
        pair_t rook_from('h', row);

        // Move the king from e1/e8 to g1/g8
        pair_t king_to('g', row);

        // Move the rook from h1/h8 to f1/f8
        pair_t rook_to('f', row);

        // Update the board
        auto king = get_piece(board, king_from);
        auto rook = get_piece(board, rook_from);

        board.move(king_from, king_to);
        board.move(rook_from, rook_to);

        if (!simulate) {
            // Update is_moved only if this is not a simulation
            king->is_moved = true;
            rook->is_moved = true;
        }
        // need to change is_moved to true
    } 

    else if (side == "queenside") {
        pair_t rook_from('a', row);

        // Move king from e1/8 to c1/8
        pair_t king_to('c', row);
        // Move rook from a1/8 to d1/8
        pair_t rook_to('d', row);

        auto king = get_piece(board, king_from);
        auto rook = get_piece(board, rook_from);

        board.move(king_from, king_to);
        board.move(rook_from, rook_to);

        if (!simulate) {
            // Update is_moved only if this is not a simulation
            king->is_moved = true;
            rook->is_moved = true;
        }

    }
}
