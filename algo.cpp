#include "chess_board.h"

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
        piece_to_move[*piece] = (*piece).moves(board);
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