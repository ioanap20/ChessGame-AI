#include <iostream>
#include "piece.h"
#include <algorithm>

//global variable to store the possible positions
std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::vector<int> numbers = {1,2,3,4,5,6,7,8};

std::vector<int> find_pos_indexes(pair_t pos){
    auto it_x = std::find(letters.begin(), letters.end(), pos.x);
    auto it_y = std::find(numbers.begin(), numbers.end(), pos.y);
    auto index_x = (int)std::distance(letters.begin(), it_x);
    auto index_y = (int)std::distance(numbers.begin(), it_y);

    std::vector<int>  index_pos = {index_x, index_y};
    return index_pos;
};

std::vector<std::shared_ptr<pair_t>> king_t::moves_no_constraints(std::vector<std::shared_ptr<pair_t>> pieces){

};

std::vector<std::shared_ptr<pair_t>> king_t::moves(std::vector<std::shared_ptr<pair_t>> pieces){

};

int main(int argc, char* argv[]){
    // Example usage
    auto position1 = std::make_shared<pair_t>(pair_t{"a", 1});
    auto position2 = std::make_shared<pair_t>(pair_t{"b", 1});
    
    // Create a rook with two positions
    std::vector<std::shared_ptr<pair_t>> positions = {position1, position2};
    rook_t rook(positions, "white");

    // Output some values
    std::cout << "Rook color: " << rook.color << std::endl;
    std::cout << "Position 1: " << rook.pos[0]->x << rook.pos[0]->y << std::endl;
    std::cout << "Position 2: " << rook.pos[1]->x << rook.pos[1]->y << std::endl;

    return 0;
}