#include "chess_board.h"
#include "algo.h"
#include <iostream>
#include <limits>
#include <algorithm>
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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------- AUX --------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/

bool has_neighboring_pawns(chess_board& board, pair_t pos, string color){
    //cout<<"In neighboring pawns"<<endl;
    int nb_neighbors = 0;
    for (int i=-1; i<=1; i++){
        for(int j=-1; j<=1; j++){
            if (i!=0 || j!=0){
                pair_t other_pos = pair_t((char)(pos.x+i), pos.y+j);
                auto it = board.board.find(other_pos);
                if (it!=board.board.end()){
                    auto other_piece = board.board[other_pos];
                    if  (other_piece->id=="pawn" && other_piece->color == color){
                        //cout<< "Out"<<endl;
                        return true;
                    }
                }
            }
        }
    }
    //cout<< "Out"<<endl;
    return false;
}

bool is_passed_pawn(chess_board& board, pair_t pos, string color){
    //cout<< "In is passed_pawn"<< endl;
    int direction = (color=="white") ? 1 : -1;
    for (int j=pos.y+direction; 1<=j && j<=8; j+=direction){
        pair_t other_pos = pair_t(pos.x, j);
        auto it = board.board.find(other_pos);
        if (it!=board.board.end()){
            auto other_piece = board.board[other_pos];
            if (other_piece->id=="pawn" && other_piece->color !=color){
                //cout<< "Out"<<endl;
                return false;
            }
        }
    }
    //cout<< "Out"<<endl;
    return true;
}

bool is_piece_attacked(chess_board board, pair_t to){
    //cout<<"In is piece_attacked"<<endl;
    //BE CAREFUL :: WE START FROM THE PRINCIPLE THAT THE BOARD IS REVERSED SO WE CHECK IF MY PIECES CAN EAT THE OPPONENT PIECE
    for (auto& piece : board.my_pieces){
        auto possible_moves = piece->correct_moves(board);
        for (auto& pos : possible_moves){
            if (*pos == to)  return true;
        }
    }
    //cout<< "Out"<<endl;
    return false;

}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------- EVALUATION FUNCTIONS ------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*
int calculate_mobility_bonus(piece_t& piece, chess_board& board) {
    //cout<<"In mobility"<<endl;
    const int MOBILITY_BONUS = 5; // Define a scaling factor for mobility
    int mobility_score = 0;

    // Get the valid moves for the piece
    auto moves = piece.correct_moves(board);

    // Add a bonus proportional to the number of valid moves
    if (moves.empty()){
        return 0;
    }
    mobility_score += moves.size() * MOBILITY_BONUS;

    return mobility_score;
} */


//Bonus for pieces that are in the center of the board since reach more positions and for their mobility so if it is easy to move them later on
int get_positional_bonus(piece_t& piece, chess_board& board){
    //cout<<"In posittional bonus"<<endl;
    int CENTER_BONUS = 10;
    int MOBILITY_BONUS = 5;

    int bonus=0;

    //positional bonus
    if (piece.pos->x == 'd' || piece.pos->x=='e'){
        if (piece.pos->y==4 || piece.pos->y==5){
            bonus +=CENTER_BONUS;
        }
    }

    //mobility bonus
    //cout<<"Getting mobility bonus"<<endl;
    /*
    if (!(&piece)) {
        cout << "Null piece encountered!" << endl;
        return 0; // Or handle this case appropriately
    }

    cout<<"Getting the correct moves"<<endl;
    auto moves = piece.correct_moves(board);
    for (const auto& move : moves) {
    if (!move) {
        cout << "Null move detected!" << endl;
    } else {
        cout << "Valid move to: " << move->x << ", " << move->y << endl;
    }
    }

    cout<<"Got my moves"<<endl;
    bonus += moves.size() * MOBILITY_BONUS;
    cout<< "Out"<<endl; */

    //bonus += calculate_mobility_bonus(piece, board);
    return bonus;
}

//King safety
int evaluate_king_safety(chess_board& chessboard){
    //cout<<"In evaluate_king_safety"<<endl;
    int penalty = 0;

    auto king = get_king(chessboard.color_ai, chessboard);

    //just check the pawn cover
    auto [king_x, king_y] = *(king.pos);
    int direction = (chessboard.color_ai=="white") ? 1 : -1;
    for (int i = -1; i<=1; i++){
        auto pawn_pos = pair_t((char)(king_x+i), king_y +direction);
        auto it = chessboard.board.find(pawn_pos);
        if (it==chessboard.board.end() || it->second->id != "pawn" || it->second->color != chessboard.color_ai){
            penalty +=50;
        }
    }
    //cout<< "Out"<<endl;
    return -penalty;
}

//Pawn structure : penalize doouble pawns(pawns in same line) and isolated pawns and favorize pawns in lanes with no enemy pawn
int evaluate_pawn_structure(chess_board& board){
    //cout<<"In Evaluate pawn_structure"<<endl;
    int score = 0;
    for (auto& [pos, piece] : board.board){
        if (piece->id == "pawn"){
            //Doubled pawns
            for (auto& [other_pos, other_piece] : board.board){
                if (other_piece->id == "pawn" && other_pos.x==pos.x){
                    score -=20;
                }
            }

            //Isolated pawns
            if (!has_neighboring_pawns(board, pos, piece->color)){
                score -=30;
            }

            //Pawn for promotion
            if (is_passed_pawn(board, pos, piece->color)){
                score += 50;
            }

        }
    }
    //cout<< "Out"<<endl;
    return score;
}

/*
//Bonuses for each piece depending on their position
int evaluate_piece(piece_t& piece, chess_board& board){
    int score = 0;
    if (piece.id=="bishop"){
        score += both_bishops(board, piece.color);
    } else if (piece.id == "queen"){
        
    }

}*/

// Evaluation function
int evaluate_board(chess_board& board) {
    //cout<<"In evaluate board"<<endl;
    int score = 0;
    for (auto& [position, piece] : board.board) {
        if (!piece) {
        //cout << "Null piece at position: " << position.x << ", " << position.y << endl;
        continue; // Skip null pieces
        }
        //cout<<"Loop"<<endl;
        int piece_value = 0;
        if (piece->color == board.color_ai) {
            if (piece->id == "pawn") piece_value = PAWN_VALUE;
            else if (piece->id == "horse") piece_value = KNIGHT_VALUE;
            else if (piece->id == "bishop") piece_value = BISHOP_VALUE;
            else if (piece->id == "rook") piece_value = ROOK_VALUE;
            else if (piece->id == "queen") piece_value = QUEEN_VALUE;
            else if (piece->id == "king") piece_value = KING_VALUE;
        } 

        int positional_bonus = get_positional_bonus(*piece, board); 
        //cout<<"Got positional Bonus"<<endl;
        if (piece->color == board.color_ai) {
            //cout<<"if color == board.color_ai"<<endl;
            score += piece_value + positional_bonus;
        } else {
            //cout<<"else"<<endl;
            score -= piece_value + positional_bonus;
        }
        //cout<<"Reaches the end of the loop"<<endl;
    
    }
    //cout<<"Out of loop"<<endl;
    //cout<<"pawn structure score trying"<<endl;
    //cout<<"Segmenatation fault comes from here"<<endl;
    //cout<<"No"<<endl;
    int pawn_structure_score = evaluate_pawn_structure(board);
    //cout<<"King safety score trying"<<endl;
    int king_safety_score = evaluate_king_safety(board);

    score += pawn_structure_score;
    score += king_safety_score;
    //cout<< "Out"<<endl;
    return score;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------- ALL MOVES  ---------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/


int move_value(Move& move, chess_board& board) {
    //cout<< "In move value"<< endl;
    const int CHECK_BONUS = 50;
    const int PROMOTION_BONUS = 900; // Promoting to queen
    const int POSITIVE_CAPTURE_BONUS = 1000;
    const int NEGATIVE_CAPTURE_PENALTY = -500;
    const int POSITIONAL_BONUS = 10;

    int value = 0;

    // 1. Capture Heuristic (MVV-LVA)
    //cout<<"Capture Heuristic"<<endl;
    if (move.captured_piece) {
        int victim_value = 0;
        int attacker_value = 0;

        if (move.captured_piece->id == "pawn") victim_value = PAWN_VALUE;
        else if (move.captured_piece->id == "horse") victim_value = KNIGHT_VALUE;
        else if (move.captured_piece->id == "bishop") victim_value = BISHOP_VALUE;
        else if (move.captured_piece->id == "rook") victim_value = ROOK_VALUE;
        else if (move.captured_piece->id == "queen") victim_value = QUEEN_VALUE;

        if (move.moved_piece->id == "pawn") attacker_value = PAWN_VALUE;
        else if (move.moved_piece->id == "horse") attacker_value = KNIGHT_VALUE;
        else if (move.moved_piece->id == "bishop") attacker_value = BISHOP_VALUE;
        else if (move.moved_piece->id == "rook") attacker_value = ROOK_VALUE;
        else if (move.moved_piece->id == "queen") attacker_value = QUEEN_VALUE;

        // MVV-LVA scoring: higher victim and lower attacker are better
        value += POSITIVE_CAPTURE_BONUS + (victim_value - attacker_value);
    }

    // 2. Promotion Bonus
    //cout<<"Promotion"<<endl;
    if (move.is_promotion) {
        value += PROMOTION_BONUS;
    }

    // 3. Check Bonus
    //cout<<"Check bonus"<<endl;
    chess_board new_board = board.clone_converse(); // Simulate the move
    new_board.move(move.from, move.to);
    if (is_check(new_board).empty()) {
        value += CHECK_BONUS;
    }

    // 4. Positional Bonus
    //cout<<"Positional Bonus"<<endl;
    value += get_positional_bonus(*move.moved_piece, board) * POSITIONAL_BONUS;

    // 5. Avoid moves that expose pieces to danger (optional, requires more computation)
    //cout<<"is piece attacked"<<endl;
    if (is_piece_attacked(new_board, move.to)) {
        value += NEGATIVE_CAPTURE_PENALTY;
    }
    //cout<<"Out of move value"<<endl;
    return value;
}

vector<Move> generate_all_possible_moves(chess_board& board, string& color) {
    vector<Move> all_moves;
    auto& pieces = (color == "white") ? board.my_pieces : board.enemy_pieces;

    for (const auto& piece : pieces) {
        if (!piece) continue;

        for (const auto& dest : piece->correct_moves(board)) {
            Move move(*piece->pos, *dest, piece, nullptr);

            // Check if capturing an opponent piece
            auto it = board.board.find(*dest);
            if (it != board.board.end() && it->second->color != color) {
                move.captured_piece = it->second;
            }

            all_moves.push_back(move);
            cout << "Move: " << piece->id << " from " << piece->pos->x << piece->pos->y
                 << " to " << dest->x << dest->y << endl;
        }
    }
    sort(all_moves.begin(), all_moves.end(), [&board](Move& a, Move& b){
            return move_value(a, board) > move_value(b, board);
    });
    return all_moves;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------- MINIMAX ALGO AND BEST MOVE ------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/


// Minimax function with Alpha-Beta Pruning
int minimax(chess_board& board, int depth, bool is_maximizing_player, int alpha, int beta) {
    //cout<<"In minimax"<<endl;
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
        //cout<< "Out"<<endl;
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
        //cout<< "Out"<<endl;
        return min_eval;
    }
}

// Function to find the best move for the AI
Move find_best_move(chess_board& board, int depth) {


    cout<<"In find bet move"<< endl;
    int best_value = std::numeric_limits<int>::min();
    
    std::vector<Move> possible_moves = generate_all_possible_moves(board, board.color_ai);
    for(auto& m : possible_moves){
        cout << "Move: " << m.from.x << m.from.y << " to " << m.to.x << m.to.y << endl;
    }
    cout<<"Empty possible moves : "<<possible_moves.empty()<<endl;
    cout<<possible_moves[0].from.x<<possible_moves[0].from.y<<endl;
    cout<<endl;
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

    cout << "Best move: " << best_move.from.x << best_move.from.y << " to " << best_move.to.x << best_move.to.y << endl;
    cout<< "Out"<<endl;
    return best_move;
}


