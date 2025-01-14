#include <map>
#include <vector>
#include "piece.h"
#include "chess_board.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>

std::vector<char> let = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::vector<int> num = {1,2,3,4,5,6,7,8};

std::vector<int> find_pos_index(pair_t pos){
    auto it_x = std::find(let.begin(), let.end(), pos.x);
    auto it_y = std::find(num.begin(), num.end(), pos.y);
    auto index_x = (int)std::distance(let.begin(), it_x);
    auto index_y = (int)std::distance(num.begin(), it_y);

    vector<int>  index_pos = {index_x, index_y};
    return index_pos;
};  



using namespace std;


/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------BASICS : IS_CHECK MOSTLY----------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/

piece_t get_king(string color, chess_board chessboard){   // This function gets the piece of the king of a given color
            
    
    auto it = find_if((chessboard.allPieces).begin(), (chessboard.allPieces).end(), [color](const shared_ptr<piece_t>& piece){
                    return (*piece).id == "king" && (*piece).color==color;
                });
    return **it;
}

vector<shared_ptr<piece_t>> is_check(chess_board chessboard){  // This function checks if our king is in a check position, that is, it computes a vector of all pieces that are threatening the king and returns them, if the vector is empty (check using vector.empty() which gives true if it is and false otherwise), then the king is not in a check position
    vector<shared_ptr<piece_t>> endangering_pieces = {};
    auto color = chessboard.color_ai;
    //cout<<"Color : "<<color<<endl;
    //cout<<"Getting the king"<<endl;
    auto king = get_king(color, chessboard);
    //cout<<"Got king "<< king<<endl;
    //cout<<"Getting king position"<<endl;
    pair_t king_pos = *(king.pos);


    for (auto& piece : chessboard.enemy_pieces){
        if (piece->id=="king"){
            continue;
        }
        auto moves = (*piece).moves(chessboard);

        //cout << "Moves computed for " << *piece << endl;

        auto it = find_if(moves.begin(), moves.end(), [king_pos](const shared_ptr<pair_t>& pos){    
            return (*pos)==king_pos;
        });

        if (it!=moves.end()){
            //cout<<"Found a piece"<<endl;
            endangering_pieces.push_back(piece);
        }
    }


    return endangering_pieces;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------PATH OF THREATENING PIECES-------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/

vector<shared_ptr<pair_t>> path_to_king_rook(piece_t king, piece_t opp_piece){  // path for a rook
    vector<shared_ptr<pair_t>> res;
    pair_t king_pos = *(king.pos);
    pair_t opp_pos = *(opp_piece.pos);
    auto ind_opp = find_pos_index(opp_pos);
    auto ind_king = find_pos_index(king_pos);

    if (king_pos.x==opp_pos.x){
            if (king_pos.y >= opp_pos.y){
                for (int i=opp_pos.y; i<king_pos.y; i++){
                    res.push_back(make_shared<pair_t>(king_pos.x, i));
                }
            } else {
                for (int i=opp_pos.y; i>king_pos.y; i--){
                    res.push_back(make_shared<pair_t>(king_pos.x, i));
                }
            }
        } else {
            if (king_pos.x<= opp_pos.x){
                for (int i=ind_opp[0]; i>ind_king[0]; i--){
                    res.push_back(make_shared<pair_t>(let[i], opp_pos.y));
                }
            } else {
                for (int i=ind_opp[0]; i<ind_king[0]; i++){
                    res.push_back(make_shared<pair_t>(let[i], opp_pos.y));
                }
            }
        }
    return res;
}

vector<shared_ptr<pair_t>> path_to_king_bishop(piece_t king, piece_t opp_piece){  // path for bishop
    vector<shared_ptr<pair_t>> res;
    pair_t king_pos = *(king.pos);
    pair_t opp_pos = *(opp_piece.pos);
    auto ind_opp = find_pos_index(opp_pos);
    auto ind_king = find_pos_index(king_pos);

    int n=0;
    if (king_pos.y>= opp_pos.y){
        if (king_pos.x<=opp_pos.x){
            //cout<<"Case 1"<<endl;
            //cout<<((ind_opp[0]-n>ind_king[0]) && (ind_opp[1]+n<ind_king[1]))<<endl;
            while (ind_opp[0]-n>ind_king[0] && ind_opp[1]+n<ind_king[1]){  //top-left diag <-> increase y and decrease x
                res.push_back(make_shared<pair_t>(let[ind_opp[0]-n], num[ind_opp[1]+n]));
                n++;
            }
        } else {
            while (ind_opp[0]+n<ind_king[0] && ind_opp[1]+n<ind_king[1]){  //top-right diag <-> increase y and increase x
                res.push_back(make_shared<pair_t>(let[ind_opp[0]+n], num[ind_opp[1]+n]));
                n++;
            }
        }
    } else {
        if (king_pos.x<=opp_pos.x){
            while (ind_opp[0]-n>ind_king[0] && ind_opp[1]-n>ind_king[1]){  //bot-left diag <-> decrease y and decrease x
                res.push_back(make_shared<pair_t>(let[ind_opp[0]-n], num[ind_opp[1]-n]));
                n++;
            }
        } else {
            while (ind_opp[0]+n<ind_king[0] && ind_opp[1]-n>ind_king[1]){  //bot_right diag <-> decrease y and increase x
                res.push_back(make_shared<pair_t>(let[ind_opp[0]+n], num[ind_opp[1]-n]));
                n++;
            }
        }
    }
    return res;
}

vector<shared_ptr<pair_t>> get_path_to_king(piece_t king, piece_t opp_piece){
    // gives back a vector of positions which are the paths from the piece to the king. If one of our pieces puts itself in any one of these positions then the king is not in a check position anymore. For the knight, since it can jump over pieces, only its position will be returned since it has to be eaten (or the king moves but this will be dealt with in another function)
    pair_t king_pos = *(king.pos) ;
    pair_t opp_pos = *(opp_piece.pos);
    vector<shared_ptr<pair_t>> res;
    auto ind_opp = find_pos_index(opp_pos);
    auto ind_king = find_pos_index(king_pos);

    if (opp_piece.id=="horse"||opp_piece.id=="pawn"){ //deals with the knight and the pawn case
        res.push_back(opp_piece.pos);
        return res;
    } else if (opp_piece.id=="rook"){
        res = path_to_king_rook(king, opp_piece);
    } else if (opp_piece.id=="bishop"){
        res = path_to_king_bishop(king, opp_piece);
    } else if (opp_piece.id=="queen"){
        res = ((king_pos.x==opp_pos.x)||(king_pos.y==opp_pos.y)) ? path_to_king_rook(king, opp_piece) : path_to_king_bishop(king, opp_piece);
    }
    return res;
    }

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------POSSIBLE MOVES IF CHECK--------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/

// creating a custom hash function to be able to use std::unordered_set since it needs it to directly access elements in the vectors

namespace std {  // we put the namespace to override the standard hashing
    template<> // 
    struct hash<pair_t>{ // these two lines create a specialization for the hash function to pair_t types
        size_t operator()(const pair_t& p) const {  // define teh function call to the operator
            return hash<char>()(p.x) ^ hash<int>()(p.y);  // precise we use the hash of characters to hash the first entry and then integer hashing (both are standard) to hash the second entry. Then the "^" corresponds to an XOR which permits to seperate the binary conversion of both hasing to avoid having equal hashing if x and y and reversed
        } 
    };
};

vector<shared_ptr<pair_t>> intersection(vector<shared_ptr<pair_t>>& vec1, vector<shared_ptr<pair_t>>& vec2){
    unordered_set<pair_t> set1;
    for (const auto& elem : vec1){
        set1.insert(*elem);
    }

    vector<shared_ptr<pair_t>> intersection;
    for (const auto& elem : vec2){
        if (set1.count(*elem)){
            intersection.push_back(elem);
        }
    }

    return intersection;
}

vector<shared_ptr<pair_t>> piece_t::check_moves(chess_board& chessboard){
    //cout<<"This is the piece we are looking at : "<< *piece << endl;
    //PART 1 : getting the paths of all the pieces that are endangering our king
    auto endangering_pieces = is_check(chessboard);
    auto king = get_king(chessboard.color_ai, chessboard);

    vector<shared_ptr<pair_t>> paths;
    vector<shared_ptr<pair_t>> vec;
    for(auto& opp : endangering_pieces){
        vec = get_path_to_king(king, *opp);
        paths.insert(paths.end(), vec.begin(), vec.end());
    }
    //cout<<"Paths : "<<endl;
    //for(auto& p : paths){
    //    cout<< *p <<" ";
    //}
    //cout<<endl;

    //PART 2 : get the intersection between me pieces' possibe moves and the ones in the path 
    //chessboard.display_chess_board();
    //CHANGE
    //auto my_moves = piece->moves(chessboard);
    auto my_moves = moves(chessboard);
    //cout<< "These are my possible moves : ";
    //for (auto& mo : piece->moves(chessboard)){
    //    cout<< *mo<<" ";
    //}
    //cout<<endl;

    vector<shared_ptr<pair_t>> correct_moves; // store pieces that get us out of check position
    auto intersect = intersection(my_moves, paths);
    //cout<<"These are the intersection points : ";
    //for (auto& points : intersect){
    //    cout<<*points;
    //}
    //cout<<endl;

    //CHANGE
    //pair_t tmp = *(piece->pos);  // keep in memory the initial position to be able to move the piece back
    pair_t tmp = *pos;
    //cout<<"The piece we are looking at is at position "<< tmp<<endl;

    //Account for if we're looking at the king that only needs to get out of the chess position
    vector<shared_ptr<pair_t>> to_go_through;
    //CHANGE
    //if (piece->id == "king"){
    if(id=="king"){
        to_go_through = my_moves;
    } else {
        to_go_through = intersect;
    }

    for(auto& posi : to_go_through){
        //cout<<"We are at position "<< *posi<<endl;
        if ((chessboard.board).find(*posi) != (chessboard.board).end()){ // This will correspond to eating the piece endangering our king
            //cout<<"The position we are looking at contains the enemy piece"<< endl;
            //first keep the piece in memory, then delete it 
            auto tmp_piece_ptr = chessboard.board[*posi]; //stores the pointer to the piece so that it isn't erased when the other pointers to it are erased
            (chessboard.board).erase(*((*tmp_piece_ptr).pos)); // erase from board
            auto it = remove(chessboard.allPieces.begin(), chessboard.allPieces.end(), tmp_piece_ptr); // erase from allPieces
            chessboard.allPieces.erase(it, chessboard.allPieces.end());
            it = remove(chessboard.enemy_pieces.begin(), chessboard.enemy_pieces.end(), tmp_piece_ptr); // erase from enemy_pieces
            chessboard.enemy_pieces.erase(it, chessboard.enemy_pieces.end());
            
            chessboard.move(tmp, *posi); //move our piece to the position of the piece
            //cout<<"This is the state of the board after removing the enemy piece and moving our piece"<<endl;
            //chessboard.display_chess_board();
            if (is_check(chessboard).empty()){
                //cout<<"We add it to correct moves"<<endl;
                correct_moves.push_back(posi);
            }
            chessboard.move(*posi, tmp); //move our piece back to its initial position
            //chessboard.display_chess_board();

            //add the erased piece back to the map and the vectors
            chessboard.board[*posi] = tmp_piece_ptr;
            chessboard.allPieces.push_back(tmp_piece_ptr);
            chessboard.enemy_pieces.push_back(tmp_piece_ptr);
            //chessboard.display_chess_board();
        } else {
            //cout<<"We are not on the position of an endagering piece"<<endl;
            chessboard.move(tmp, *posi); //move our piece to the position of the piece
            //cout<<"This is the state of the board after moving our piece"<<endl;
            //chessboard.display_chess_board();
            if (is_check(chessboard).empty()){
                correct_moves.push_back(posi);
            }
            chessboard.move(*posi, tmp); //move our piece back to its initial position
            //cout<<"Back to init"<<endl;
            //chessboard.display_chess_board();
        }
    }

    return correct_moves;
};

/*
vector<shared_ptr<pair_t>> check_moves(shared_ptr<piece_t> piece, chess_board chessboard){
    //cout<<"This is the piece we are looking at : "<< *piece << endl;
    //PART 1 : getting the paths of all the pieces that are endangering our king
    auto endangering_pieces = is_check(chessboard);
    auto king = get_king(chessboard.color_ai, chessboard);

    vector<shared_ptr<pair_t>> paths;
    vector<shared_ptr<pair_t>> vec;
    for(auto& opp : endangering_pieces){
        vec = get_path_to_king(king, *opp);
        paths.insert(paths.end(), vec.begin(), vec.end());
    }
    //cout<<"Paths : "<<endl;
    //for(auto& p : paths){
    //    cout<< *p <<" ";
    //}
    //cout<<endl;

    //PART 2 : get the intersection between me pieces' possibe moves and the ones in the path 
    //chessboard.display_chess_board();
    auto my_moves = piece->moves(chessboard);
    //cout<< "These are my possible moves : ";
    //for (auto& mo : piece->moves(chessboard)){
    //    cout<< *mo<<" ";
    //}
    //cout<<endl;

    vector<shared_ptr<pair_t>> correct_moves; // store pieces that get us out of check position
    auto intersect = intersection(my_moves, paths);
    //cout<<"These are the intersection points : ";
    //for (auto& points : intersect){
    //    cout<<*points;
    //}
    //cout<<endl;

    pair_t tmp = *(piece->pos);  // keep in memory the initial position to be able to move the piece back
    //cout<<"The piece we are looking at is at position "<< tmp<<endl;

    //Account for if we're looking at the king that only needs to get out of the chess position
    vector<shared_ptr<pair_t>> to_go_through;
    if (piece->id == "king"){
        to_go_through = my_moves;
    } else {
        to_go_through = intersect;
    }

    for(auto& posi : to_go_through){
        //cout<<"We are at position "<< *posi<<endl;
        if ((chessboard.board).find(*posi) != (chessboard.board).end()){ // This will correspond to eating the piece endangering our king
            //cout<<"The position we are looking at contains the enemy piece"<< endl;
            //first keep the piece in memory, then delete it 
            auto tmp_piece_ptr = chessboard.board[*posi]; //stores the pointer to the piece so that it isn't erased when the other pointers to it are erased
            (chessboard.board).erase(*((*tmp_piece_ptr).pos)); // erase from board
            auto it = remove(chessboard.allPieces.begin(), chessboard.allPieces.end(), tmp_piece_ptr); // erase from allPieces
            chessboard.allPieces.erase(it, chessboard.allPieces.end());
            it = remove(chessboard.enemy_pieces.begin(), chessboard.enemy_pieces.end(), tmp_piece_ptr); // erase from enemy_pieces
            chessboard.enemy_pieces.erase(it, chessboard.enemy_pieces.end());
            
            chessboard.move(tmp, *posi); //move our piece to the position of the piece
            //cout<<"This is the state of the board after removing the enemy piece and moving our piece"<<endl;
            //chessboard.display_chess_board();
            if (is_check(chessboard).empty()){
                //cout<<"We add it to correct moves"<<endl;
                correct_moves.push_back(posi);
            }
            chessboard.move(*posi, tmp); //move our piece back to its initial position
            //chessboard.display_chess_board();

            //add the erased piece back to the map and the vectors
            chessboard.board[*posi] = tmp_piece_ptr;
            chessboard.allPieces.push_back(tmp_piece_ptr);
            chessboard.enemy_pieces.push_back(tmp_piece_ptr);
            //chessboard.display_chess_board();
        } else {
            //cout<<"We are not on the position of an endagering piece"<<endl;
            chessboard.move(tmp, *posi); //move our piece to the position of the piece
            //cout<<"This is the state of the board after moving our piece"<<endl;
            //chessboard.display_chess_board();
            if (is_check(chessboard).empty()){
                correct_moves.push_back(posi);
            }
            chessboard.move(*posi, tmp); //move our piece back to its initial position
            //cout<<"Back to init"<<endl;
            //chessboard.display_chess_board();
        }
    }

    return correct_moves;
};
*/

map<shared_ptr<piece_t>, vector<shared_ptr<pair_t>>> all_check_moves(chess_board chessboard){
    map<shared_ptr<piece_t>, vector<shared_ptr<pair_t>>> res;
    for (auto& piece : chessboard.my_pieces){
        //CHANGE
        //auto v = check_moves(piece, chessboard);
        auto v = (*piece).check_moves(chessboard);
        if(!v.empty()){res[piece] = v;}
    }
    return res;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------TESTING------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/


int main(int argc, char* argv[]){
   // Initialize the chessboard
    chess_board chessboard;

    chessboard.set_pieces("white");  // Assuming this sets up the pieces for both sides
    //chessboard.color_ai = "white";
    auto white_king = get_king("white", chessboard);
    //shared_ptr<piece_t> horse = chessboard.board[pair_t('g', 8)];
    chessboard.move(pair_t('b', 8), pair_t('d', 3));
    chessboard.move(pair_t('g', 8), pair_t('f', 3));
    chessboard.move(pair_t('e', 1), pair_t('b', 4));
    chessboard.display_chess_board();
    chessboard.display_chess_board();

    auto v = is_check(chessboard);
    if (v.empty()){
        cout<<"Not in a check position";
    } else {
        cout<<"In check position"<<endl;
        cout<<"These pieces are endangering the king : ";
        for (auto& piece : v){
            cout<<*piece;
        }
    }
    cout<<endl;

    //shared_ptr<piece_t>  pawn = chessboard.board[pair_t('g', 2)];
    //auto cmoves = check_moves(pawn, chessboard);
    auto check_moves_map = all_check_moves(chessboard);
    cout<< "Possible moves to get out of check position : ";
    for (auto& piece : check_moves_map){
        cout<< *(piece.first)<<" can move to ";
        for(auto& move : piece.second){
            cout<<*move<<" ";
        }
        cout<<"to get out of a check position"<<endl;
    }
    cout<<endl;
} 
