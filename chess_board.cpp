#include <iostream>
#include <vector>
#include "chess_board.h"
using namespace std;


/*chess_board::chess_board() {

    whitePieces = {

    }

    /*return {
        'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', // Black
        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 
        '.', '.', '.', '.', '.', '.', '.', '.', 
        '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.',
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 
        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'  // White
    };*/

void chess_board::move(pair_t from, pair_t to) {
    // move piece from one position to another
    // update boardMap
}


void print_chess_board(const std::vector<char>& board) {
    std::cout << "-------------------------\n";
    for (int i = 0; i < 8; i++) { 
        std::cout << "| ";
        for (int j = 0; j < 8; j++) { // Loop through columns
            char piece = board[i * 8 + j]; 
            if (piece == '.') {
                std::cout << ". "; 
            } else {
                std::cout << piece << " "; 
            }
        }
        std::cout << "|\n"; 
    }
    std::cout << "-------------------------\n";
}

/*int main(){
    std::vector<char> chess_board = initialize_chess_board();
    print_chess_board(chess_board);
    return 0;
}*/

