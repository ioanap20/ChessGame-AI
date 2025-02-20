#include <iostream>
#include "piece.h"
#include "chess_board.h"
#include <map>
#include <algorithm>


/*----------------------AUXILIARY FUNCTIONS FOR MOVE IMPLEMENTATION---------------------------------------*/
// find the indices in the corresponding list (letters and numbers) given a position
std::vector<char> lett = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::vector<int> numb = {1,2,3,4,5,6,7,8};

std::vector<int> find_pos_indexes(pair_t pos){
    auto it_x = std::find(lett.begin(), lett.end(), pos.x);
    auto it_y = std::find(numb.begin(), numb.end(), pos.y);
    auto index_x = (int)std::distance(lett.begin(), it_x);
    auto index_y = (int)std::distance(numb.begin(), it_y);

    std::vector<int>  index_pos = {index_x, index_y};
    return index_pos;
};

// check if a position is inside the boundaries of the grid
bool is_position_in_grid(int index_x, int index_y){
    return index_x>=0 && index_x<= 7 &&index_y>=0 && index_y<= 7;
}

//given a vector containing positions, and a board containing (position, piece) and a piece itself, outputs a vector containing only positions where no friendly piece is
std::vector<std::shared_ptr<pair_t>> remove_friendly_pos(piece_t cur, std::vector<std::shared_ptr<pair_t>>& positions, const chess_board& board){
    std::vector<std::shared_ptr<pair_t>> ok_pos;
    for (auto& pos : positions){
        auto it = board.board.find(*pos);  // we extract an iterator to the (key,value) pair of map and check if the key we are looking for is inside map
        if (it!=board.board.end()){  // if the key is indeed inside the map we check the color of the pieces and add if its a different color
            if (it->second->color != cur.color){
                ok_pos.push_back(pos);
            }
        } else {
            ok_pos.push_back(pos);  // if the key isn't inside the map then there are no pieces at this position so all is good
        }
    }
    return ok_pos;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------CORRECT MOVES-------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/

std::vector<std::shared_ptr<pair_t>> piece_t::correct_moves(chess_board& chessboard){
    if (!is_check(chessboard).empty()){
        return check_moves(chessboard);
    }

    vector<shared_ptr<pair_t>> possible_moves = moves(chessboard);
    std::vector<std::shared_ptr<pair_t>> correct_moves;
    pair_t position = *pos;
    for (auto& move : possible_moves){
        if ((chessboard.board).find(*move)!=(chessboard.board).end()){
            //run the simulation
            auto tmp_piece_ptr = chessboard.board[*move]; 
            (chessboard.board).erase(*((*tmp_piece_ptr).pos));
            auto it = remove(chessboard.allPieces.begin(), chessboard.allPieces.end(), tmp_piece_ptr);
            chessboard.allPieces.erase(it, chessboard.allPieces.end());
            it = remove(chessboard.enemy_pieces.begin(), chessboard.enemy_pieces.end(), tmp_piece_ptr); 
            chessboard.enemy_pieces.erase(it, chessboard.enemy_pieces.end());

            chessboard.move(position, *move);
            if(is_check(chessboard).empty()){
                correct_moves.push_back(move);
            }
            chessboard.move(*move, position);

            chessboard.board[*move] = tmp_piece_ptr;
            chessboard.allPieces.push_back(tmp_piece_ptr);
            chessboard.enemy_pieces.push_back(tmp_piece_ptr);
        } else {
            chessboard.move(position, *move);
            if (is_check(chessboard).empty()){
                correct_moves.push_back(move);
            }
            chessboard.move(*move, position);
        }
    }

    return correct_moves;
}


/*--------------------------------------------------------------------------------------------------------*/
/*---------------------------------------MOVES------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------*/

//pawn
std::vector<std::shared_ptr<pair_t>> pawn_moves(piece_t& cur, std::vector<std::shared_ptr<pair_t>> pos_positions, const chess_board& board){
    std::vector<std::shared_ptr<pair_t>> vertical_pos;
    std::vector<std::shared_ptr<pair_t>> diag_pos;
    for (auto& pos : pos_positions){
        ((*pos).x == (*(cur.pos)).x ? vertical_pos : diag_pos).push_back(pos);
    }
    std::vector<std::shared_ptr<pair_t>> ok_positions;

    //sifting vertical positions -- we stop when we encounter the first piece (we cannot eat any white or black pieces moving forward)
    bool cond = true; // cond is a boolean to indicate if we continue the loop or not (if we have encountered a piece)
    for (auto& pos : vertical_pos){
        if (!cond){ break;}
        auto it = board.board.find(*pos);
        if (it!=board.board.end()){
            cond = false;
        }
        if (cond){
            ok_positions.push_back(pos);
        }
    }

    //sifting diagonal positions -- only can go where opponent piece
    for (auto& pos: diag_pos){
        auto it = board.board.find(*pos);
        if (it!=board.board.end()){
            if (it->second->color != cur.color){
                ok_positions.push_back(pos);
            }
        }
    }
    return ok_positions;
}

//rook
std::vector<std::shared_ptr<pair_t>> rook_moves(piece_t& cur, std::vector<std::shared_ptr<pair_t>> pos_positions, const chess_board& board){
    std::vector<std::shared_ptr<pair_t>> vert_pos;
    std::vector<std::shared_ptr<pair_t>> hor_pos;
    for (auto& pos : pos_positions){ ((*pos).x == (*(cur.pos)).x ? vert_pos : hor_pos).push_back(pos);}
    std::vector<std::shared_ptr<pair_t>> vert_pos_above, vert_pos_below; // all vert pos on top of the rook or below
    std::vector<std::shared_ptr<pair_t>> hor_pos_above, hor_pos_below;  // same for hor

    for (auto& pos : vert_pos){ ((*pos).y > (*(cur.pos)).y ? vert_pos_above : vert_pos_below).push_back(pos);}
    for (auto& pos : hor_pos){ ((*pos).x > (*(cur.pos)).x ? hor_pos_above : hor_pos_below).push_back(pos);}

    // sort the vectors in ascending order for the above categories and in descending for below one
    std::sort(vert_pos_above.begin(), vert_pos_above.end(), [](const std::shared_ptr<pair_t>& a, const std::shared_ptr<pair_t>& b){
        return a->y<b->y;
    });
    std::sort(hor_pos_above.begin(), hor_pos_above.end(), [](const std::shared_ptr<pair_t>& a, const std::shared_ptr<pair_t>& b){
        return a->x<b->x;
    });
    std::sort(vert_pos_below.begin(), vert_pos_below.end(), [](const std::shared_ptr<pair_t>& a, const std::shared_ptr<pair_t>& b){
        return a->y>b->y;
    });
    std::sort(hor_pos_below.begin(), hor_pos_below.end(), [](const std::shared_ptr<pair_t>& a, const std::shared_ptr<pair_t>& b){
        return a->x>b->x;
    });

    std::vector<std::shared_ptr<pair_t>> ok_positions;
    //sifting positions
    bool cond = true;
    for (auto& pos : vert_pos_above){
        if (!cond){ break;}
        auto it = board.board.find(*pos);
        if (it!=board.board.end()){
            if (it->second->color != cur.color){
                ok_positions.push_back(pos);
            }
            cond = false;
        }
        if (cond){
            ok_positions.push_back(pos);
        }
    }
    cond = true;
    for (auto& pos : vert_pos_below){
        if (!cond){ break;}
        auto it = board.board.find(*pos);
        if (it!=board.board.end()){
            if (it->second->color != cur.color){
                ok_positions.push_back(pos);
            }
            cond = false;
        }
        if (cond){
            ok_positions.push_back(pos);
        }
    }
    cond = true;
    for (auto& pos : hor_pos_above){
        if (!cond){ break;}
        auto it = board.board.find(*pos);
        if (it!=board.board.end()){
            if (it->second->color != cur.color){
                ok_positions.push_back(pos);
            }
            cond = false;
        }
        if (cond){
            ok_positions.push_back(pos);
        }
    }
    cond = true;
    for (auto& pos : hor_pos_below){
        if (!cond){ break;}
        auto it = board.board.find(*pos);
        if (it!=board.board.end()){
            if (it->second->color != cur.color){
                ok_positions.push_back(pos);
            }
            cond = false;
        }
        if (cond){
            ok_positions.push_back(pos);
        }
    }
    return ok_positions;
}

//bishop
std::vector<std::shared_ptr<pair_t>> bishop_moves(piece_t& cur, std::vector<std::shared_ptr<pair_t>> pos_positions, const chess_board& board){
    std::vector<std::shared_ptr<pair_t>> maindiag_pos; // /
    std::vector<std::shared_ptr<pair_t>> antidiag_pos; // // "\"
    for (auto& pos : pos_positions){ ((pos->x - pos->y)== ((*(cur.pos)).x - (*(cur.pos)).y) ? maindiag_pos : antidiag_pos).push_back(pos);}
    std::vector<std::shared_ptr<pair_t>> maindiag_above, maindiag_below; 
    std::vector<std::shared_ptr<pair_t>> antidiag_above, antidiag_below; 

    for (auto& pos : maindiag_pos){ ((*pos).y > (*(cur.pos)).y ? maindiag_above : maindiag_below).push_back(pos);}
    for (auto& pos : antidiag_pos){ ((*pos).y < (*(cur.pos)).y ? antidiag_above : antidiag_below).push_back(pos);} 

    std::sort(maindiag_above.begin(), maindiag_above.end(), [](const std::shared_ptr<pair_t>& a, const std::shared_ptr<pair_t>& b){
        return a->x < b->x;
    });
    std::sort(antidiag_above.begin(), antidiag_above.end(), [](const std::shared_ptr<pair_t>& a, const std::shared_ptr<pair_t>& b){
        return a->x < b->x;
    });
    std::sort(maindiag_below.begin(), maindiag_below.end(), [](const std::shared_ptr<pair_t>& a, const std::shared_ptr<pair_t>& b){
        return a->x > b->x;
    });
    std::sort(antidiag_below.begin(), antidiag_below.end(), [](const std::shared_ptr<pair_t>& a, const std::shared_ptr<pair_t>& b){
        return a->x > b->x;
    });
    std::vector<std::shared_ptr<pair_t>> ok_positions;
    //sifting positions
    bool cond = true;
    for (auto& pos : maindiag_above){
        if (!cond){ break;}
        auto it = board.board.find(*pos);
        if (it!=board.board.end()){
            if (it->second->color != cur.color){
                ok_positions.push_back(pos);
            }
            cond = false;
        }
        if (cond){
            ok_positions.push_back(pos);
        }
    }
    cond = true;
    for (auto& pos : maindiag_below){
        if (!cond){ break;}
        auto it = board.board.find(*pos);
        if (it!=board.board.end()){
            if (it->second->color != cur.color){
                ok_positions.push_back(pos);
            }
            cond = false;
        }
        if (cond){
            ok_positions.push_back(pos);
        }
    }
    cond = true;
    for (auto& pos : antidiag_above){
        if (!cond){ break;}
        auto it = board.board.find(*pos);
        if (it!=board.board.end()){
            if (it->second->color != cur.color){
                ok_positions.push_back(pos);
            }
            cond = false;
        }
        if (cond){
            ok_positions.push_back(pos);
        }
    }
    cond = true;
    for (auto& pos : antidiag_below){
        if (!cond){ break;}
        auto it = board.board.find(*pos);
        if (it!=board.board.end()){
            if (it->second->color != cur.color){
                ok_positions.push_back(pos);
            }
            cond = false;
        }
        if (cond){
            ok_positions.push_back(pos);
        }
    }
    return ok_positions;
}

//queen moves
std::vector<std::shared_ptr<pair_t>> queen_moves(piece_t& cur, std::vector<std::shared_ptr<pair_t>> pos_positions, const chess_board& board){
    std::vector<std::shared_ptr<pair_t>> vert_hor_pos;
    std::vector<std::shared_ptr<pair_t>> diag_pos;
    for (auto& pos : pos_positions){(((pos->x==(*(cur.pos)).x)||(pos->y==(*(cur.pos)).y)) ? vert_hor_pos : diag_pos).push_back(pos);}
    std::vector<std::shared_ptr<pair_t>> verthor_ok_pos = rook_moves(cur, vert_hor_pos, board);
    std::vector<std::shared_ptr<pair_t>> diag_ok_pos = bishop_moves(cur, diag_pos, board);
    verthor_ok_pos.insert(verthor_ok_pos.end(), diag_ok_pos.begin(), diag_ok_pos.end());
    return verthor_ok_pos;
}


//global = works for knight and king on its own otherwise it calls the other functions
std::vector<std::shared_ptr<pair_t>> piece_t::moves(chess_board& board){
    //cout<<"In M"<<endl;
    auto neighbors = moves_no_constraints(board);
    if (id=="pawn"){
        return pawn_moves(*this, neighbors, board);
    }
    if (id=="rook"){
        return rook_moves(*this, neighbors, board);
    }
    if (id=="bishop"){
        return bishop_moves(*this, neighbors, board);
    }
    if (id=="queen"){
        return queen_moves(*this, neighbors, board);
    }
    auto ok_neighbors = remove_friendly_pos(*this, neighbors, board);

    //cout << "ok_neighbors: " << ok_neighbors.size() << endl;

    return ok_neighbors;
};

/*------------------------------------//MOVES NO CONSTRAINSTS//-----------------------------------------*/
/*---------------------------------------KING-----------------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> king_t::moves_no_constraints(chess_board& board) const {
    pair_t actual_pos = *pos; 
    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
    if (is_position_in_grid(index_pos[0]+1, index_pos[1])){
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]+1], numb[index_pos[1]]));
    }
    if (is_position_in_grid(index_pos[0]-1, index_pos[1])){
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]-1], numb[index_pos[1]]));
    }
    if (is_position_in_grid(index_pos[0], index_pos[1]+1)){
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]], numb[index_pos[1]+1]));
    }
    if (is_position_in_grid(index_pos[0], index_pos[1]-1)){
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]], numb[index_pos[1]-1]));
    }
    if (is_position_in_grid(index_pos[0]+1, index_pos[1]+1)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]+1], numb[index_pos[1]+1]));
    }
    if (is_position_in_grid(index_pos[0]-1, index_pos[1]+1)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]-1], numb[index_pos[1]+1]));
    }
    if (is_position_in_grid(index_pos[0]+1, index_pos[1]-1)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]+1], numb[index_pos[1]-1]));
    }
    if (is_position_in_grid(index_pos[0]-1, index_pos[1]-1)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]-1], numb[index_pos[1]-1]));
    }
    

    chess_board temp_board;
    temp_board = board.clone();

    auto castling_info = can_castle(temp_board, this->color);

    if (!castling_info["kingside"].empty()) {
        possible_pos.push_back(castling_info["kingside"][0]);
    }
    
    return possible_pos;
}

/*------------------------------------------PAWN---------------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> pawn_t::moves_no_constraints(chess_board& board) const{
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
    
    /*shared_ptr<piece_t> piece_to_promote = can_we_promote(board, board.color_ai);

     if(piece_to_promote){
        cout << "Promote your pawn to a queen, rook, or bishop" << endl;
        do_promotion(board, piece_to_promote, 'q', board.color_ai);
    }*/


    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
    
    //straight positions
    if (is_position_in_grid(index_pos[0], index_pos[1]+direction)){
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]], numb[index_pos[1]+direction]));
    }
    if (init_move&&is_position_in_grid(index_pos[0],index_pos[1]+2*direction)){
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]], numb[index_pos[1]+2*direction]));
    }

    //diagonal positions
    if (is_position_in_grid(index_pos[0]+1, index_pos[1]+direction)){
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]+1], numb[index_pos[1]+direction]));
    }
    if (is_position_in_grid(index_pos[0]-1, index_pos[1]+direction)){
        possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]-1], numb[index_pos[1]+direction]));
    }
    return possible_pos;

    
};

/*--------------------------------------------KNIGHT-------------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> horse_t::moves_no_constraints(chess_board& board) const{
    //cout<<"In MnC"<<endl;
    pair_t actual_pos = *pos;
    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
    int id_x = index_pos[0];
    int id_y = index_pos[1];
    
    if (is_position_in_grid(id_x+2, id_y+1)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[id_x+2], numb[id_y+1]));
    }
    if (is_position_in_grid(id_x+2, id_y-1)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[id_x+2], numb[id_y-1]));
    }
    if (is_position_in_grid(id_x-2, id_y+1)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[id_x-2], numb[id_y+1]));
    }
    if (is_position_in_grid(id_x-2, id_y-1)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[id_x-2], numb[id_y-1]));
    }
    if (is_position_in_grid(id_x+1, id_y+2)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[id_x+1], numb[id_y+2]));
    }
    if (is_position_in_grid(id_x-1, id_y+2)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[id_x-1], numb[id_y+2]));
    }
    if (is_position_in_grid(id_x+1, id_y-2)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[id_x+1], numb[id_y-2]));
    }
    if (is_position_in_grid(id_x-1, id_y-2)) {
        possible_pos.push_back(std::make_shared<pair_t>(lett[id_x-1], numb[id_y-2]));
    }
    
    //cout<<"Possible pos is empty"<<possible_pos.empty()<<endl;
    //if (!possible_pos.empty()){
    //    for (auto& m : possible_pos){
    //        cout<< *m <<" ";
    //    }
    //}
    //cout<<endl;
    return possible_pos;
}

/*-----------------------------------------------BISHOP---------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> bishop_t::moves_no_constraints(chess_board& board) const{
    pair_t actual_pos = *pos; 
    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
    
	// toward top right
	for (int n = 1; n < 8; n++) {
		if (is_position_in_grid(index_pos[0]+n, index_pos[1]+n)){
		    possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]+n], numb[index_pos[1]+n]));
		}
		else {
			break;
		}
	}
		
    // toward top left
	for (int n = 1; n < 8; n++) {
		if (is_position_in_grid(index_pos[0]-n, index_pos[1]+n)){
		    possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]-n], numb[index_pos[1]+n]));
		} else {
			break;
		}  
	}
		    
	// toward bottom right
	for (int n = 1; n < 8; n++) {
		if (is_position_in_grid(index_pos[0]+n, index_pos[1]-n)){
		    possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]+n], numb[index_pos[1]-n]));
		} else {
			break;
		}
	}
		
	// toward bottom left
	for (int n = 1; n < 8; n++) {
		if (is_position_in_grid(index_pos[0]-n, index_pos[1]-n)){
		    possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]-n], numb[index_pos[1]-n]));
		}
		else {
			break;
		}
	}
    return possible_pos;
};

/*-----------------------------------------------ROOK-----------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> rook_t::moves_no_constraints(chess_board& board) const{
    pair_t actual_pos = *pos; 
    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
	for (int n = 1; n < 8; n++) {   // vert up
		if (is_position_in_grid(index_pos[0], index_pos[1]+n)){
		    possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]], numb[index_pos[1]+n]));
		}
		else {
			break;
		}
	}	
	for (int n = 1; n < 8; n++) {   // vert down
		if (is_position_in_grid(index_pos[0], index_pos[1]-n)){
		    possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]], numb[index_pos[1]-n]));
		}
		else {
			break;
		}
	}
	for (int n = 1; n < 8; n++) {	// hor right
		if (is_position_in_grid(index_pos[0]+n, index_pos[1])){
		    possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]+n], numb[index_pos[1]]));
		}
		else {
			break;
		}
	}
	for (int n = 1; n < 8; n++) {   // hor left
		if (is_position_in_grid(index_pos[0]-n, index_pos[1])){
		    possible_pos.push_back(std::make_shared<pair_t>(lett[index_pos[0]-n], numb[index_pos[1]]));
		}
		else {
			break;
		}
	}	
	return possible_pos;
};

/*-----------------------------------------------QUEEN----------------------------------------------------*/
std::vector<std::shared_ptr<pair_t>> queen_t::moves_no_constraints(chess_board& board) const{
    pair_t actual_pos = *pos; 
    std::vector<int> index_pos = find_pos_indexes(actual_pos);
    std::vector<std::shared_ptr<pair_t>> possible_pos;
	
    bishop_t bishop(std::make_shared<pair_t>(actual_pos.x, actual_pos.y), color);
    std::vector<std::shared_ptr<pair_t>> bishop_pos = bishop.moves_no_constraints(board);
    
    rook_t rook(std::make_shared<pair_t>(actual_pos.x, actual_pos.y), color);
    std::vector<std::shared_ptr<pair_t>> rook_pos = rook.moves_no_constraints(board);

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

std::ostream& operator<<(std::ostream& os, const pair_t& pair) {
    return os << pair.x << pair.y;
}

std::ostream& operator<<(std::ostream& os, const piece_t& piece) {
    return os << piece.color << " " << piece.id << " at " << *piece.pos;
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::shared_ptr<piece_t>>& pieces) {
    for (const auto& piece : pieces) {
        os << *piece << std::endl;
    }
    return os;
}

piece_t piece_t :: clone(){
    piece_t new_piece;
    new_piece.id = id;
    new_piece.color = color;
    new_piece.pos = pos;
    return new_piece;
}


//(-------------    CASTLING MOVES   -----------------)

/*std::vector<std::shared_ptr<pair_t>>piece_t:: castle_moves(chess_board& board, const std::string& color_ai) {
    std::vector<std::shared_ptr<pair_t>> possible_castling_moves;

    // Use the is_castling function to determine castling availability
    auto castling_status = is_castling(board, color_ai);

    // If castling is not possible, return an empty vector
    if (!castling_status["kingside"] && !castling_status["queenside"]) {
        return possible_castling_moves;
    }

    // Use castle_moves to get the actual moves
    if (castling_status["kingside"]) {
        auto kingside_moves = castling(board, color_ai, "kingside", true);
        if (!kingside_moves.empty()) {
            possible_castling_moves.push_back(kingside_moves[1]); // Add the king's move (e.g., e1 -> g1)
        }
    }

    if (castling_status["queenside"]) {
        auto queenside_moves = castling(board, color_ai, "queenside", true);
        if (!queenside_moves.empty()) {
            possible_castling_moves.push_back(queenside_moves[1]); // Add the king's move (e.g., e1 -> c1)
        }
    }

    return possible_castling_moves;
}
*/
/*--------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------LOCAL TESTING-----------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------*/

/*
int main(int argc, char* argv[]){
    // Example usage 
    std::vector<std::shared_ptr<piece_t>> pieces;

    rook_t rook(std::make_shared<pair_t>('g', 5), "white");
    pawn_t wpawn(std::make_shared<pair_t>('g', 6), "white");
    pawn_t bpawn(std::make_shared<pair_t>('c', 7), "black");
    bishop_t bishop(std::make_shared<pair_t>('g',3), "white");
    king_t king(std::make_shared<pair_t>('f', 2), "white");
    queen_t queen(std::make_shared<pair_t>('d', 6), "white");
    horse_t knight(std::make_shared<pair_t>('c',6), "white");

    pieces.push_back(std::make_shared<king_t>(king));
    pieces.push_back(std::make_shared<rook_t>(rook));
    pieces.push_back(std::make_shared<pawn_t>(wpawn));
    pieces.push_back(std::make_shared<pawn_t>(bpawn));
    pieces.push_back(std::make_shared<bishop_t>(bishop));
    pieces.push_back(std::make_shared<queen_t>(queen));
    pieces.push_back(std::make_shared<piece_t>(knight));

    std::cout<<"Pieces on the board"<<std::endl;
    std::cout<<pieces<<std::endl;

    std::map<pair_t, std::shared_ptr<piece_t>> board;
    for (auto& piece : pieces){
        board[*((*piece).pos)] = piece;
    }


    // Output some values
    //std::cout<<king<<std::endl;
    //std::cout<<wpawn<<std::endl;
    //std::cout<<bpawn<<std::endl;
    auto neigh = king.moves(board);
    auto neigh1 = wpawn.moves(board);
    auto neigh2 = bpawn.moves(board);
    auto rook_moves = rook.moves(board);
    auto bishop_moves = bishop.moves(board);
    auto queen_moves = queen.moves(board);
    auto knight_moves = knight.moves(board);
    //std::cout<<"King's possible moves"<<std::endl;
    //display_positions(neigh);
    std::cout<<"White Pawn's possible moves"<<std::endl;
    display_positions(neigh1);
    std::cout<<"Black Pawn's possible moves"<<std::endl;
    display_positions(neigh2);
    std::cout<<"Rook's Possible moves"<<std::endl;
    display_positions(rook_moves);
    std::cout<<"Bishop's possible moves"<<std::endl;
    display_positions(bishop_moves);
    std::cout<<"Queen's possible moves"<<std::endl;
    display_positions(queen_moves);
    std::cout<<"Knight's possible moves"<<std::endl;
    display_positions(knight_moves);
    return 0;
} */
