#include "chess_board.h"
#include <iostream>
#include <limits>
using namespace std;

vector<shared_ptr<pair_t>> chess_board::next_move(std::string color){
    /*vector<shared_ptr<piece_t>> my_pieces;
    vector<shared_ptr<piece_t>> opponent_pieces;
    if (color=="white"){
        my_pieces = whitePieces;
        opponent_pieces = blackPieces;
    } else { my_pieces = blackPieces; opponent_pieces = whitePieces;}*/

    map<piece_t, vector<shared_ptr<pair_t>>> piece_to_move;
    for (auto& piece : my_pieces){
        //piece_to_move[*piece] = (*piece).moves(allPieces);
        piece_to_move[*piece] = (*piece).moves(*this);
        for (auto& move : piece_to_move[*piece]){
            if (board.find(*move)!=board.end()){
                if ((*piece).color != (*board[(*move)]).color){
                    vector<shared_ptr<pair_t>> result;
                    result.push_back((*piece).pos);
                    result.push_back(move);
                    return result;
                }
            }
        }
    }
    srand(time(0)); // seed the random generator
    vector<shared_ptr<pair_t>> random_output;
    vector<piece_t> keys;
    for (const auto& pair : piece_to_move){
        keys.push_back(pair.first);
    }
    int random_index = rand() % keys.size();

    auto random_piece = keys[random_index];
    auto rand_moves_vec = piece_to_move[random_piece];

    while (rand_moves_vec.empty()){
        random_index = rand() % keys.size();
        random_piece = keys[random_index];
        rand_moves_vec = piece_to_move[random_piece];
    }

    int rand_move_index = rand() % rand_moves_vec.size();
    vector<shared_ptr<pair_t>> result;
    result.push_back(random_piece.pos);
    result.push_back(rand_moves_vec[rand_move_index]);
    return result;
}
    // Build piece_to_move for all pieces

    /*string position_from, position_to;
    cout << "Enter the position of the piece (e.g., 'e2'): ";
    cin >> position_from;

    pair_t from(position_from[0], position_from[1] - '0');

    auto it = board.find(from);
    
    auto piece = it->second;

    auto moves = piece->moves(*this);

    if (moves.empty()) {

        if(can_we_promote(*this, color)){
            cout << "Promote your pawn to a queen, rook, bishop, or knight." << endl;
        }
        else {
        cout << "No valid moves available for the piece at " << from.x << from.y << "." << endl;
        return {};
    }
    }

    cout << "Valid moves for " << piece->id << " at " << from.x << from.y << ":" << endl;
    for (size_t i = 0; i < moves.size(); ++i) {
        cout << i << ": " << moves[i]->x << moves[i]->y << endl;
    }

    cin >> position_to;
    pair_t to(position_to[0], position_to[1] - '0');
    vector<shared_ptr<pair_t>> result;
    result.push_back(make_shared<pair_t>(from));
    result.push_back(make_shared<pair_t>(to));

    if (piece->id == "king" && abs(to.x - from.x) == 2){
        if (to.x == 'g'){
            move(pair_t('h', from.y), pair_t('f', from.y));
        } else {
            move(pair_t('a', from.y), pair_t('d', from.y));
        }
    }

    return result;
}*/
