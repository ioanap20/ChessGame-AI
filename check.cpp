#include <map>
#include <vector>
#include "piece.h"
#include "chess_board.h"
#include <iostream>
#include <algorithm>

using namespace std;
/*
std::vector<int> find_pos_indexes(pair_t pos){
    auto it_x = std::find(letters.begin(), letters.end(), pos.x);
    auto it_y = std::find(numbers.begin(), numbers.end(), pos.y);
    auto index_x = (int)std::distance(letters.begin(), it_x);
    auto index_y = (int)std::distance(numbers.begin(), it_y);

    std::vector<int>  index_pos = {index_x, index_y};
    return index_pos;
}; */

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------BASICS : IS_CHECK MOSTLY----------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*
piece_t get_king(string color, chess_board chessboard){   // This function gets the piece of the king of a given color
    auto it = find_if((chessboard.allPieces).begin(), (chessboard.allPieces).end(), [color](const shared_ptr<piece_t>& piece){
                    return (*piece).id == "king" && (*piece).color==color;
                });
    return **it;
}
*/
/*
vector<shared_ptr<piece_t>> is_check(chess_board chessboard){  // This function checks if our king is in a check position, that is, it computes a vector of all pieces that are threatening the king and returns them, if the vector is empty (check using vector.empty() which gives true if it is and false otherwise), then the king is not in a check position
    vector<shared_ptr<piece_t>> endangering_pieces;
    auto color = chessboard.color_ai;
    cout<<"Color : "<<color<<endl;
    cout<<"Getting the king"<<endl;
    auto king = get_king(color, chessboard);
    cout<<"Got king "<< king<<endl;
    cout<<"Getting king position"<<endl;
    pair_t king_pos = *(king.pos);

    for (auto& piece : chessboard.enemy_pieces){
        auto moves = (*piece).moves(chessboard.board);
        auto it = find_if(moves.begin(), moves.end(), [king_pos](const shared_ptr<pair_t>& pos){
            return (*pos)==king_pos;
        });
        if (it!=moves.end()){
            cout<<"Found a piece"<<endl;
            endangering_pieces.push_back(piece);
        }
    }

    return endangering_pieces;
}
*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------PATH OF THREATENING PIECES-------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*
vector<shared_ptr<pair_t>> get_path_to_king(piece_t king, piece_t opp_piece){
    // gives back a vector of positiosn which are the paths from the piece to the king. If one of our pieces puts itself in any one of these positions then the king is not in a check position anymore. For the knight, since it can jump over pieces, only its position will be returned since it has to be eaten (or the king moves but this will be dealt with in another function)
    if (opp_piece.id=="horse"||opp_piece.id=="pawn"){ //deals with the knight and the pawn case
        vector<shared_ptr<pair_t>> res;
        res.push_back(opp_piece.pos);
        return res;
    }
} */
/*
vector<shared_ptr<pair_t>> path_to_king_rook(piece_t king, piece_t opp_piece){
    vector<shared_ptr<pair_t>> path;
    
    pair_t king_pos = *(king.pos);
    pair_t opp_pos = *(opp_piece.pos);
    if (king_pos.x==opp_pos.x){
        if (king_pos.y<opp_pos.y){
            for (int i = opp_pos.y; i==king_pos.y; i--){
                path.push_back(make_shared<pair_t>(king_pos.x, i));
            }
            return path;
        } else {
            for (int i = opp_pos.y; i==king_pos.y; i++){
                path.push_back(make_shared<pair_t>(king_pos.x, i));
            }
            return path;
        }
    } else {
        if (king_pos.x<opp_pos.x){
            auto king_pos_idx = find_pos_indexes(king_pos);
            auto opp_pos_idx = find_pos_indexes(opp_pos);
            for (int i = opp_pos_idx[0]; i==king_pos_idx[0]; i--){
                path.push_back(make_shared<pair_t>(letters[i], king_pos.y));
            }
        }
    }
}
*/





/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------TESTING------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*
int main(int argc, char* argv[]){
    //king_t king(std::make_shared<pair_t>('f', 2), "white");
    //vector<shared_ptr<piece_t>> pieces;
    chess_board chessboard;
    cout<<"Initial board"<<endl;
    chessboard.display_chess_board();

    for (auto& piece : chessboard.enemy_pieces){
        cout<< *piece<<endl;
    }
    pair_t posi('f',6);
    for (auto& piece : chessboard.enemy_pieces){
        cout<<(*piece).id<<endl;
        if ((*piece).id=="horse"){
            chessboard.move((*(*piece).pos), posi);
            cout<< "updated the knight"<<endl;
            break;
        }
    }
    chessboard.color_ai = "black";
    cout<<"After moving the knight"<<endl;
    chessboard.display_chess_board();
    auto king = get_king("black", chessboard);
    cout<<"My "<<king<<endl;
    chessboard.display_chess_board();
    cout<<"Trying check"<<endl;
    auto check_pieces = is_check(chessboard);
    cout<<"Check done"<<endl;
    cout<<"Check done"<<endl;
    if (check_pieces.empty()){
        cout<<"Not in a check position"<<endl;
    }
    for (auto& piece : check_pieces){
        cout<<"This piece : "<< (*piece) << " is endangering my king"<< endl;
    }

    return 0;
}
*/