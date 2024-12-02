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

bool is_position_in_grid(int index_x, int index_y){
    if (index_x>=0 && index_x<= 7 &&index_y>=0 && index_y<= 7){
        return true;
    }
    return false;
}
std::vector<std::shared_ptr<pair_t>> piece_t::moves_no_constraints() {
    // Default implementation (if needed)
    return {};
}

std::vector<std::shared_ptr<pair_t>> king_t::moves_no_constraints(){
    pair_t actual_pos = *pos; 
    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
    if (is_position_in_grid(index_pos[0]+1, index_pos[1])){
        possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]+1], numbers[index_pos[1]]));
    }
    if (is_position_in_grid(index_pos[0]-1, index_pos[1])){
        possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]-1], numbers[index_pos[1]]));
    }
    if (is_position_in_grid(index_pos[0], index_pos[1]+1)){
        possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]], numbers[index_pos[1]+1]));
    }
    if (is_position_in_grid(index_pos[0], index_pos[1]-1)){
        possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]], numbers[index_pos[1]-1]));
    }
    return possible_pos;
};
/*
std::vector<std::shared_ptr<pair_t>> king_t::moves(std::vector<std::shared_ptr<pair_t>> pieces){
    return pieces;

};
*/

void display_positions(std::vector<std::shared_ptr<pair_t>> positions){
    std::cout<<"Neighbours : ";
    for (size_t i=0; i<positions.size(); i++){
        std::cout<<positions[i]->x<<positions[i]->y<<" ";
    }
    std::cout<<std::endl;
}

int main(int argc, char* argv[]){
    // Example usage
    auto position = std::make_shared<pair_t>('d', 5);  // Correct initialization

    // Create a king
    king_t king(position, "white");

    // Output some values
    std::cout << "King color: " << king.color << std::endl;
    std::cout << "King position: " << king.pos->x << king.pos->y << std::endl;
    auto neigh = king.moves_no_constraints();
    display_positions(neigh);

    return 0;
}