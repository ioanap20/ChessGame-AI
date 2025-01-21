#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include "chess_board.h"
#include "piece.h"

bool is_en_passant(
    const piece_t& cur,
    const pair_t& target_pos,
    const std::map<pair_t, std::shared_ptr<piece_t>>& board,
    const pair_t& last_move_from,
    const pair_t& last_move_to
) {
    // Find the last moved piece at 'last_move_to'
    auto last_piece_it = board.find(last_move_to);

    // Check if the last move was a pawn move by the opponent
    if (last_piece_it != board.end() &&
        last_piece_it->second->color != cur.color &&
        last_piece_it->second->id == "pawn") { // Use '==' for comparison

        // Determine the direction based on the current player's color
        int direction;
        if (cur.color == "black") {
            direction = -1;
        }
        else if (cur.color == "white") {
            direction = 1;
        }
        else {
            // Invalid color
            return false;
        }

        // Check if the last move was a double-step pawn move
        // Assuming pawns start at y=2 (white) and y=7 (black)
        if ((last_piece_it->second->color == "white" && last_move_from.y == 2 && last_move_to.y == 4) ||
            (last_piece_it->second->color == "black" && last_move_from.y == 7 && last_move_to.y == 5)) {

            // Check if the current piece is adjacent to the last moved pawn
            if (abs(static_cast<int>(cur.pos->x) - static_cast<int>(last_move_to.x)) == 1 &&
                cur.pos->y == last_move_to.y &&
                target_pos.x == last_move_to.x &&
                target_pos.y == cur.pos->y + direction) {
                return true;
            }
        }
    }

    return false;
}