#include <map>
#include <vector>
#include "piece.h"
#include "chess_board.h"
#include <iostream>
#include <algorithm>

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



/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------TESTING------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*int main(int argc, char* argv[]){
    //king_t king(std::make_shared<pair_t>('f', 2), "white");
    //vector<shared_ptr<piece_t>> pieces;
    chess_board chessboard;
    chessboard.color_ai = "black";
    cout<<"Initial board"<<endl;
    chessboard.display_chess_board();

    cout<<"Printing all pieces"<<endl;
    for (auto& piece : chessboard.allPieces){
        cout<< *piece<<endl;
    }
    chessboard.set_pieces("black");

    pair_t posi('f',6);

    chessboard.move(pair_t('e', 7), pair_t('h', 5));
    //chessboard.move(pair_t('h', 1), pair_t('e', 5));
    chessboard.move(pair_t('e', 8), pair_t('f', 6));
    //chessboard.move(pair_t('f', 1), pair_t('f', 5));
    chessboard.move(pair_t('d', 1), pair_t('e', 5));


    cout<<"After moving the knight"<<endl;
    chessboard.display_chess_board();
    auto king = get_king("black", chessboard);
    cout<<"My "<<king<<endl;
    chessboard.display_chess_board();
    cout<<"Trying check"<<endl;
    auto check_pieces = is_check(chessboard);
    cout<<"Check done"<<endl;
    if (check_pieces.empty()){
        cout<<"Not in a check position"<<endl;
    }
    for (auto& piece : check_pieces){
        cout<<"This piece : "<< (*piece) << " is endangering my king"<< endl;
        auto path = get_path_to_king(king, *piece);
        cout<<"This is the path : ";
        for (auto pos : path){
            cout<< *pos<<" ";
        }
        cout<<endl;
    }

    return 0;
} */
