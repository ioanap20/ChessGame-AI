#include "chess_board.h"
#include "algo.h"
#include <iostream>
#include <limits>
using namespace std;

//vector<shared_ptr<pair_t>> chess_board::next_move(std::string color){
    /*vector<shared_ptr<piece_t>> my_pieces;
    vector<shared_ptr<piece_t>> opponent_pieces;
    if (color=="white"){
        my_pieces = whitePieces;
        opponent_pieces = blackPieces;
    } else { my_pieces = blackPieces; opponent_pieces = whitePieces;}*/

    /*map<piece_t, vector<shared_ptr<pair_t>>> piece_to_move;
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
}*/
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
}
*/

// (------------- MIN-MAX ALGORITHM -----------------)
// Define piece values for evaluation
const int PAWN_VALUE = 100;
const int KNIGHT_VALUE = 320;
const int BISHOP_VALUE = 330;
const int ROOK_VALUE = 500;
const int QUEEN_VALUE = 900;
const int KING_VALUE = 20000; // Arbitrary high value

// Evaluation function
int evaluate_board(chess_board& board) {
    int score = 0;
    for (const auto& [position, piece] : board.board) {
        if (piece->color == board.color_ai) {
            if (piece->id == "pawn") score += PAWN_VALUE;
            else if (piece->id == "horse") score += KNIGHT_VALUE;
            else if (piece->id == "bishop") score += BISHOP_VALUE;
            else if (piece->id == "rook") score += ROOK_VALUE;
            else if (piece->id == "queen") score += QUEEN_VALUE;
            else if (piece->id == "king") score += KING_VALUE;
        } else {
            if (piece->id == "pawn") score -= PAWN_VALUE;
            else if (piece->id == "horse") score -= KNIGHT_VALUE;
            else if (piece->id == "bishop") score -= BISHOP_VALUE;
            else if (piece->id == "rook") score -= ROOK_VALUE;
            else if (piece->id == "queen") score -= QUEEN_VALUE;
            else if (piece->id == "king") score -= KING_VALUE;
        }
    }
    return score;
}

// Function to generate all possible moves for a given color
vector<Move> generate_all_possible_moves(chess_board& board, const string& color) {
    vector<Move> all_moves;
    vector<shared_ptr<piece_t>> pieces = (color == "white") ? board.whitePieces : board.blackPieces;

    for (const auto& piece : pieces) {
        if (!piece) continue; // Skip if the piece pointer is null

        // Generate moves using the existing 'moves' function from piece.cpp
        vector<shared_ptr<pair_t>> destination_ptrs = piece->correct_moves(board);


        for (const auto& dest : destination_ptrs) {

            //cout << "Piece: " << piece->id << " at " << piece->pos->x << piece->pos->y << " to " << dest->x << dest->y << endl;

            Move move(*piece->pos, *dest, piece, nullptr);

            // Check if destination has an opponent's piece (capture)
            auto it = board.board.find(*dest);
            if (it != board.board.end() && it->second->color != color) {
                move.captured_piece = it->second;
            }


            all_moves.push_back(move);
        }
    }

    /*for (const auto& move : all_moves) {
        cout << "Move: " << move.from.x << move.from.y << " to " << move.to.x << move.to.y << endl;
    }*/

    return all_moves;
}

// Minimax function with Alpha-Beta Pruning
int minimax(chess_board& board, int depth, bool is_maximizing_player, int alpha, int beta) {
    if (depth == 0 || board.is_game_over()) {
        return evaluate_board(board);
    }

    if (is_maximizing_player) {
        int max_eval = std::numeric_limits<int>::min();
        std::vector<Move> possible_moves = generate_all_possible_moves(board, board.color_ai);

        for (const auto& move : possible_moves) {

           // cout << "Move: " << move.from.x << move.from.y << " to " << move.to.x << move.to.y << endl;

            // Clone the board to simulate the move
            chess_board new_board = board.clone();

            //cout << "Move: " << move.from.x << move.from.y << " to " << move.to.x << move.to.y <<" On the new board" << endl;
            // we assume that all moves we can do are valid moves
            new_board.move(move.from, move.to);

            

            // Recursively evaluate the move
            int eval = minimax(new_board, depth - 1, false, alpha, beta);
            max_eval = std::max(max_eval, eval);
            alpha = std::max(alpha, eval);

            // Alpha-Beta Pruning
            if (beta <= alpha)
                break; // Beta cut-off
        }
        return max_eval;
    } else {
        int min_eval = std::numeric_limits<int>::max();
        std::string opponent_color = (board.color_ai == "white") ? "black" : "white";
        std::vector<Move> possible_moves = generate_all_possible_moves(board, opponent_color);

        for (const auto& move : possible_moves) {

            //cout << "Move: " << move.from.x << move.from.y << " to " << move.to.x << move.to.y << endl;

            // Clone the board to simulate the move
            chess_board new_board = board.clone();

            //cout << "Move: " << move.from.x << move.from.y << " to " << move.to.x << move.to.y <<" On the new board" << endl;

            new_board.move(move.from, move.to);

            // Recursively evaluate the move
            int eval = minimax(new_board, depth - 1, true, alpha, beta);
            min_eval = std::min(min_eval, eval);
            beta = std::min(beta, eval);

            // Alpha-Beta Pruning
            if (beta <= alpha)
                break; // Alpha cut-off
        }
        return min_eval;
    }
}

// Function to find the best move for the AI
Move find_best_move(chess_board& board, int depth) {



    int best_value = std::numeric_limits<int>::min();
    
    std::vector<Move> possible_moves = generate_all_possible_moves(board, board.color_ai);
    /*for(auto& m : possible_moves){
        cout << "Move: " << m.from.x << m.from.y << " to " << m.to.x << m.to.y << endl;
    }*/
    /*cout<<"Empty possible moves : "<<possible_moves.empty()<<endl;
    cout<<possible_moves[0].from.x<<possible_moves[0].from.y<<endl;
    cout<<endl;*/
    Move best_move = possible_moves[0]; // Initialize with default positions
    //cout <<best_move.from.x << best_move.from.y << " to " << best_move.to.x << best_move.to.y << endl;

    for (const auto& move : possible_moves) {
        // Clone the board to simulate the move
        chess_board new_board = board.clone();

        auto piece = new_board.board[move.from];

        //cout << "Move piece: " << *piece << " to " << move.to.x << move.to.y << "New board"<< endl;

        // Apply the move
        new_board.move(move.from, move.to);

        // Evaluate the move using Minimax
        int move_value = minimax(new_board, depth - 1, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

        // Select the move with the highest evaluation score
        if (move_value > best_value) {
            best_value = move_value;
            best_move = move;
        }

        //cout <<" Best move: " << best_move.from.x << best_move.from.y << " to " << best_move.to.x << best_move.to.y << endl;
    }

    //cout << "Best move: " << best_move.from.x << best_move.from.y << " to " << best_move.to.x << best_move.to.y << endl;

    return best_move;
}


