#include <iostream>
#include "piece.h"
#include <algorithm>


/*----------------------AUXILIARY FUNCTIONS FOR MOVE IMPLEMENTATION---------------------------------------*/
//global variable to store the possible positions
std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::vector<int> numbers = {1,2,3,4,5,6,7,8};

// find the indices in the corresponding list (letters and numbers) given a position
std::vector<int> find_pos_indexes(pair_t pos){
    auto it_x = std::find(letters.begin(), letters.end(), pos.x);
    auto it_y = std::find(numbers.begin(), numbers.end(), pos.y);
    auto index_x = (int)std::distance(letters.begin(), it_x);
    auto index_y = (int)std::distance(numbers.begin(), it_y);

    std::vector<int>  index_pos = {index_x, index_y};
    return index_pos;
};

// check if a position is inside the boundaries of the grid
bool is_position_in_grid(int index_x, int index_y){
    if (index_x>=0 && index_x<= 7 &&index_y>=0 && index_y<= 7){
        return true;
    }
    return false;
}

//given a vector containing positions, and a vector containing pieces and a piece itself, outputs a 
//vector containing only positions where no friendly piece is
std::vector<std::shared_ptr<pair_t>> remove_friendly_pos(piece_t cur, std::vector<std::shared_ptr<pair_t>>& positions, std::vector<std::shared_ptr<piece_t>>& pieces){
    std::vector<std::shared_ptr<pair_t>> to_remove;
    for (auto& pos : positions){
        for (auto& piece : pieces){
            if (*pos == *((*piece).pos) ){
                if (cur.color == (*piece).color){
                    to_remove.push_back(pos);
                }
            }
        }
    }
    for (auto& pos : to_remove){
        std::cout<<"Trying to remove "<< *pos << std::endl;
        positions.erase(std::remove_if(positions.begin(), positions.end(),
                [&pos](const std::shared_ptr<pair_t>& p) {
                    // Compare the pointed-to pair_t objects
                    return *p == *pos;
                }), positions.end());
    }
    return positions;
}

/*--------------------------------------------------------------------------------------------------------*/
/*---------------------------------------MOVES------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> pawn_moves(piece_t& cur, std::vector<std::shared_ptr<pair_t>> pos_positions, std::vector<std::shared_ptr<piece_t>>& pieces){
    std::vector<std::shared_ptr<pair_t>> vertical_pos;
    std::vector<std::shared_ptr<pair_t>> diag_pos;
    for (auto& pos : pos_positions){
        ((*pos).x == (*(cur.pos)).x ? vertical_pos : diag_pos).push_back(pos);
    }
    std::vector<std::shared_ptr<pair_t>> ok_positions;

    //sifting vertical positions
    bool cond = true;
    for (auto& pos : vertical_pos){
        if (!cond){ break;}
        for (auto& piece : pieces){
            if (*pos == *((*piece).pos)){
                cond = false;
                break;
            }
        }
        if (cond){
            ok_positions.push_back(pos);
        }
    }

    //sifting diagonal positions -- only can go where opponent piece
    for (auto& pos: diag_pos){
        cond = true;
        for (auto& piece : pieces){
            if (*pos == *((*piece).pos)){
                if (cur.color!=(*piece).color){
                    cond = false;
                    break;
                }
            }
        }
        if (!cond){
            ok_positions.push_back(pos);
        }
    }
    return ok_positions;
}

std::vector<std::shared_ptr<pair_t>> piece_t::moves(std::vector<std::shared_ptr<piece_t>>& pieces){
    auto neighbors = moves_no_constraints();
    if (id=="pawn"){
        return pawn_moves(*this, neighbors, pieces);
    }
    auto ok_neighbors = remove_friendly_pos(*this, neighbors, pieces);
    return ok_neighbors;
};

/*---------------------------------------KING-----------------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> king_t::moves_no_constraints() const{
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

/*------------------------------------------PAWN---------------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> pawn_t::moves_no_constraints() const{
    pair_t actual_pos = *pos;
    
    // if pawn is black or white we say if it goes to towards the bottom or up + if pawn has not moved yet it can go two steps at once
    int direction ;
    bool init_move;
    if (color == "white"){
        direction = 1;
        init_move = (actual_pos.y==2);
    } else {
        direction = -1;
        init_move = (actual_pos.y==7);
    }

    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
    
    //straight positions
    if (is_position_in_grid(index_pos[0], index_pos[1]+direction)){
        possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]], numbers[index_pos[1]+direction]));
    }
    if (init_move&&is_position_in_grid(index_pos[0],index_pos[1]+2*direction)){
        possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]], numbers[index_pos[1]+2*direction]));
    }

    //diagonal positions
    if (is_position_in_grid(index_pos[0]+1, index_pos[1]+direction)){
        possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]+1], numbers[index_pos[1]+direction]));
    }
    if (is_position_in_grid(index_pos[0]-1, index_pos[1]+direction)){
        possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]-1], numbers[index_pos[1]+direction]));
    }
    return possible_pos;
};

/*--------------------------------------------KNIGHT-------------------------------------------------------*/

std::vector<std::shared_ptr<pair_t>> horse_t::moves_no_constraints() const{
    pair_t actual_pos = *pos;
    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
    int id_x = index_pos[0];
    int id_y = index_pos[1];
    if (is_position_in_grid(id_x+2, id_y+1)) {
        possible_pos.push_back(std::make_shared<pair_t>(letters[id_x+2], numbers[id_y+1]));
    }
    if (is_position_in_grid(id_x+2, id_y-1)) {
        possible_pos.push_back(std::make_shared<pair_t>(letters[id_x+2], numbers[id_y-1]));
    }
    if (is_position_in_grid(id_x-2, id_y+1)) {
        possible_pos.push_back(std::make_shared<pair_t>(letters[id_x-2], numbers[id_y+1]));
    }
    if (is_position_in_grid(id_x-2, id_y-1)) {
        possible_pos.push_back(std::make_shared<pair_t>(letters[id_x-2], numbers[id_y-1]));
    }
    if (is_position_in_grid(id_x+1, id_y+2)) {
        possible_pos.push_back(std::make_shared<pair_t>(letters[id_x+1], numbers[id_y+2]));
    }
    if (is_position_in_grid(id_x-1, id_y+2)) {
        possible_pos.push_back(std::make_shared<pair_t>(letters[id_x-1], numbers[id_y+2]));
    }
    if (is_position_in_grid(id_x+1, id_y-2)) {
        possible_pos.push_back(std::make_shared<pair_t>(letters[id_x+1], numbers[id_y-2]));
    }
    if (is_position_in_grid(id_x-1, id_y-2)) {
        possible_pos.push_back(std::make_shared<pair_t>(letters[id_x-1], numbers[id_y-2]));
    }

}

/*-----------------------------------------------BISHOP---------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> bishop_t::moves_no_constraints() const{
    pair_t actual_pos = *pos; 
    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
    
	// toward top right
	for (int n = 1; n < 8; n++) {
		if (is_position_in_grid(index_pos[0]+n, index_pos[1]+n)){
		    possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]+n], numbers[index_pos[1]+n]));
		}
		else {
			break;
		}
	}
		
    // toward top left
	for (int n = 1; n < 8; n++) {
		if (is_position_in_grid(index_pos[0]-n, index_pos[1]+n)){
		    possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]-n], numbers[index_pos[1]+n]));
		} else {
			break;
		}  
	}
		    
	// toward bottom right
	for (int n = 1; n < 8; n++) {
		if (is_position_in_grid(index_pos[0]+n, index_pos[1]-n)){
		    possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]+n], numbers[index_pos[1]-n]));
		} else {
			break;
		}
	}
		
	// toward bottom left
	for (int n = 1; n < 8; n++) {
		if (is_position_in_grid(index_pos[0]-n, index_pos[1]-n)){
		    possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]+n], numbers[index_pos[1]+n]));
		}
		else {
			break;
		}
	}
    return possible_pos;
};

/*-----------------------------------------------ROOK-----------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> rook_t::moves_no_constraints() const{
    pair_t actual_pos = *pos; 
    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
	for (int n = 1; n < 8; n++) {   // vert up
		if (is_position_in_grid(index_pos[0], index_pos[1]+n)){
		    possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]], numbers[index_pos[1]+n]));
		}
		else {
			break;
		}
	}	
	for (int n = 1; n < 8; n++) {   // vert down
		if (is_position_in_grid(index_pos[0], index_pos[1]-n)){
		    possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]], numbers[index_pos[1]-n]));
		}
		else {
			break;
		}
	}
	for (int n = 1; n < 8; n++) {	// hor right
		if (is_position_in_grid(index_pos[0]+n, index_pos[1])){
		    possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]+n], numbers[index_pos[1]]));
		}
		else {
			break;
		}
	}
	for (int n = 1; n < 8; n++) {   // hor left
		if (is_position_in_grid(index_pos[0]-n, index_pos[1])){
		    possible_pos.push_back(std::make_shared<pair_t>(letters[index_pos[0]-n], numbers[index_pos[1]]));
		}
		else {
			break;
		}
	}	
	return possible_pos;
};

/*-----------------------------------------------QUEEN----------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> queen_t::moves_no_constraints() const{
    pair_t actual_pos = *pos; 
    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
	
    bishop_t bishop(std::make_shared<pair_t>(actual_pos.x, actual_pos.y), color);
    std::vector<std::shared_ptr<pair_t>> bishop_pos = bishop.moves_no_constraints();
    
    rook_t rook(std::make_shared<pair_t>(actual_pos.x, actual_pos.y), color);
    std::vector<std::shared_ptr<pair_t>> rook_pos = rook.moves_no_constraints();

    possible_pos.insert(possible_pos.end(), bishop_pos.begin(), bishop_pos.end());	
	possible_pos.insert(possible_pos.end(), rook_pos.begin(), rook_pos.end());

	return possible_pos;
};



/*--------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------DISPLAYS--------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------*/
void display_positions(std::vector<std::shared_ptr<pair_t>>& positions){
    std::cout<<"Neighbours : ";
    for (auto& pos : positions){
        std::cout<<*pos<<" ";
    }
    std::cout<<std::endl;
}



/*--------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------GLOBAL TESTING-----------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------*/
int main(int argc, char* argv[]){
    // Example usage
    auto position = std::make_shared<pair_t>('e', 3);  
    auto position2 = std::make_shared<pair_t>('d', 6);
    auto pos3 = std::make_shared<pair_t>('e', 7);
    auto pos4= std::make_shared<pair_t>('e', 2);

    std::vector<std::shared_ptr<piece_t>> pieces;
    rook_t rook(position2, "white");
    pawn_t wpawn(pos4, "white");
    pawn_t bpawn(pos3, "black");

    king_t king(position, "white");
    pieces.push_back(std::make_shared<king_t>(king));
    pieces.push_back(std::make_shared<rook_t>(rook));
    pieces.push_back(std::make_shared<pawn_t>(wpawn));
    pieces.push_back(std::make_shared<pawn_t>(bpawn));

    std::cout<<"Pieces on the board"<<std::endl;
    std::cout<<pieces<<std::endl;

    // Output some values
    //std::cout<<king<<std::endl;
    //std::cout<<wpawn<<std::endl;
    //std::cout<<bpawn<<std::endl;
    auto neigh = king.moves(pieces);
    auto neigh1 = wpawn.moves(pieces);
    auto neigh2 = bpawn.moves(pieces);
    std::cout<<"King's possible moves"<<std::endl;
    display_positions(neigh);
    std::cout<<"White Pawn's possible moves"<<std::endl;
    display_positions(neigh1);
    std::cout<<"Black Pawn's possible moves"<<std::endl;
    display_positions(neigh2);
    return 0;
}