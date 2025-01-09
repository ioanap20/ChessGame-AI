#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include "chess_board.h"
#include "piece.cpp"


bool is_en_passant(
    const piece_t& cur,
    const pair_t& target_pos,
    const std::map<pair_t, std::shared_ptr<piece_t>>& board,
    const pair_t& last_move_from,
    const pair_t& last_move_to
) {
    auto last_piece = board.find(last_move_to);
    if(last_piece->second->color != cur.color && last_piece->second->id="pawn" && 
       last_piece !=board.end()){
        //diferent directions
        int direction;
        if (cur.color == "black"){
            direction= -1;
        }else if (cur.color == "white"){
            direction= 1;
        }else{
            return false;
        }
        if(last_move_from.y== 2*direction+ last_move_to.y &&
            cur.pos->y=last_move_to.y && (cur.pos->x= 1+ last_move_to.x ||
            cur.pos->x= -1+ last_move_to->x )&&
            target_pos.x == last_move_to.x && target_pos.y == cur.pos->y + direction) {
            return true;
        }
    }

    return false;
}