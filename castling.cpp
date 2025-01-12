#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include "chess_board.h"
#include "piece.h"
using namespace std;

std::shared_ptr<piece_t> get_piece(chess_board& board, const pair_t& position) {
    auto it = board.board.find(position); // Search for the position in the board map
    if (it != board.board.end()) {
        return it->second; // Return the piece if found
    }
    return nullptr; // Return nullptr if no piece is found
}


std::map<std::string, vector<shared_ptr<pair_t>>> can_castle(chess_board chess_board, const std::string& color_ai){
    std::map<std::string, vector<shared_ptr<pair_t>>> castling_moves = {{"kingside", {}}, {"queenside", {}}};
    
    int row = (color_ai == "white") ? 1 : 8;

 //(------------check if the king has moved----------------)
    pair_t king_pos('e', row);

    // Check if the king is in its starting position and hasn't moved
    auto king = std::dynamic_pointer_cast<king_t>(get_piece(chess_board, king_pos));
    if (!king || king->is_moved) {
        return castling_moves; // No king or king has already moved
    }
    
    // check if the queen has moved
    /*pair_t queen_pos('e', row);
    if (chess_board.board.find(queen_pos) != chess_board.board.end()) {
        auto queen = chess_board.board.at(queen_pos);
        if (queen->id == "queen" || queen->is_moved) {
            return castling_moves;
        }
    }*/


//(----------- helper function to check if the path is clear ----------------)
    // gretl: i edited this to handle descending ranges as well (queenside)
    auto is_path_clear_kingside = [&](string color) {
        if(chess_board.board.find(pair_t('f', row)) != chess_board.board.end() || 
           chess_board.board.find(pair_t('g', row)) != chess_board.board.end()) {
            return false;
        }
        return true;
    };
    
    auto is_path_clear_queenside = [&](string color) {
        if(chess_board.board.find(pair_t('b', row)) != chess_board.board.end() || 
           chess_board.board.find(pair_t('c', row)) != chess_board.board.end() || 
           chess_board.board.find(pair_t('d', row)) != chess_board.board.end()) {
            return false;
        }
        return true;
    };

//(-------------- helper function is_check if the king is in check ----------------)
    // agatha has is_check() (to be finished) --> for now, using this impl
   /* auto is_check = [&]() {
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
    };*/
    
    //(----------- check if is_check for the king before and after castling 
    
    auto endengering_pieces_before = is_check(chess_board);

    if (endengering_pieces_before.empty() == false) {
        // if in check, you cannot castle on either side
        return castling_moves;
    }


//(------------ check if it can castle on kings_side ----------------)
    // gretl: i edited this to handle descending ranges as well (queenside)
    // check if it can castle on kings_side
    if (is_path_clear_kingside(color_ai)) {
        
        pair_t kingside_rook_pos('h', row);
        auto rook = std::dynamic_pointer_cast<rook_t>(get_piece(chess_board, kingside_rook_pos));
        if (rook && !rook->is_moved) {
            // Simulate the castling move

            auto endengering_pieces_after = endengering_pieces_before;

            for (char i = 'f'; i <= 'g'; i++) {

                chess_board.move(king_pos, pair_t(i, row)); // Move king
                // Check if the king is in check after castling
                endengering_pieces_after = is_check(chess_board);
                
                if (endengering_pieces_after.empty() == false) {
                    //cout << "King is in check after castling" << endl;
                    castling_moves["kingside"] = {};
                    break;
                }            
                // Revert the move
                chess_board.move(pair_t(i, row), king_pos); // Move king back

            }
                if (endengering_pieces_after.empty() == true) {

                    castling_moves["kingside"] = {make_shared<pair_t>('g', row), make_shared<pair_t>('f', row)};
                }


            }
            

        }

//(------------ check if it can castle on the queens_side ----------------)
if (is_path_clear_queenside(color_ai)) {
        pair_t queenside_rook_pos('a', row);
        auto rook = std::dynamic_pointer_cast<rook_t>(get_piece(chess_board, queenside_rook_pos));
        if (rook && !rook->is_moved) {
            // Simulate the castling move

            auto endengering_pieces_after = endengering_pieces_before;


            for(char i = 'd'; i >= 'c'; i--) {


                chess_board.move(pair_t('e', row), pair_t(i, row)); // Move king
                // Check if the king is in check after castling
                endengering_pieces_after = is_check(chess_board);
                
                if (endengering_pieces_after.empty() == false) {
                    castling_moves["queenside"] = {};
                    break;
                }

                // Revert the move
                chess_board.move(pair_t(i, row), pair_t('e', row)); // Move king back
        }

        
        if (endengering_pieces_after.empty() == true) {

                    castling_moves["queenside"] = {make_shared<pair_t>('c', row), make_shared<pair_t>('d', row)};
                }
    }
}

return castling_moves;

}

 /*vector<shared_ptr<pair_t>> castling(chess_board& board, const std::string& color_ai, const std::string& side, bool simulate) {
    int row = (color_ai == "white") ? 1 : 8; // Determine the row based on color
    pair_t king_from('e', row); // starting pos of king
    pair_t rook_from('h', row); // starting pos of rook
    vector<shared_ptr<pair_t>> result;
    
    if (side == "kingside") {
        // Move the king from e1/e8 to g1/g8
        pair_t king_to('g', row);

        // Move the rook from h1/h8 to f1/f8
        pair_t rook_to('f', row);

        // Update the board
        auto king = get_piece(board, king_from);
        auto rook = get_piece(board, rook_from);


        if (!simulate) {
            // Update is_moved only if this is not a simulation
            king->is_moved = true;
            rook->is_moved = true;
        }
        // need to change is_moved to true
        result.push_back(make_shared<pair_t>(king_from));
        result.push_back(make_shared<pair_t>(king_to));
        result.push_back(make_shared<pair_t>(rook_from));
        result.push_back(make_shared<pair_t>(rook_to));
    } 

    else if (side == "queenside") {
        // Move the king from e1/e8 to c1/c8
        pair_t king_to('c', row);

        // Move the rook from a1/a8 to d1/d8
        rook_from = pair_t('a', row);
        pair_t rook_to('d', row);

        auto king = get_piece(board, king_from);
        auto rook = get_piece(board, rook_from);

        if (!simulate) {
            // Update is_moved only if this is not a simulation
            king->is_moved = true;
            rook->is_moved = true;
        }

        result.push_back(make_shared<pair_t>(king_from));
        result.push_back(make_shared<pair_t>(king_to));
        result.push_back(make_shared<pair_t>(rook_from));
        result.push_back(make_shared<pair_t>(rook_to));

    }
    return result;
}*/

