#include <iostream>
#include <vector>
#include "piece.h"
#include "chess_board.h"
#include <vector>
#include <memory>
#include <string>

#ifndef ALGO_H
#define ALGO_H

// Structure to represent a chess move
struct Move {
    pair_t from;                                 // Starting position (e.g., e2)
    pair_t to;                                   // Ending position (e.g., e4)
    std::shared_ptr<piece_t> moved_piece;        // The piece being moved
    std::shared_ptr<piece_t> captured_piece;     // The piece being captured (nullptr if no capture)
    bool is_castling = false;                    // Flag for castling
    bool is_en_passant = false;                  // Flag for en passant
    bool is_promotion = false;                   // Flag for pawn promotion
    std::string promotion_piece;                 // Type of piece to promote to (e.g., "queen")

    // Constructors
    Move() : from({'\0', 0}), to({'\0', 0}), moved_piece(nullptr), captured_piece(nullptr) {}
    Move(pair_t from_pos, pair_t to_pos, std::shared_ptr<piece_t> moved, std::shared_ptr<piece_t> captured = nullptr)
        : from(from_pos), to(to_pos), moved_piece(moved), captured_piece(captured) {}
};

// Function prototypes

// Evaluation function
int evaluate_board(chess_board& board);

// Minimax function with Alpha-Beta Pruning
int minimax(chess_board& board, int depth, bool is_maximizing_player, int alpha, int beta);

// Function to find the best move for the AI
Move find_best_move(chess_board& board, int depth);

// Function to generate all possible moves for a given color
vector<Move> generate_all_possible_moves(chess_board& board, const string& color);

#endif // ALGO_H