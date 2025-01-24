# Project Log -- Agatha Beffy

## Part 1: Implementation of the piece structures --(Three weeks)

### First two weeks: 
- Implemented the core piece structures (`piece_t`) and position structure (`pair_t`)
    - `piece_t` serves as the main structure for all chess pieces with inheritance use to distinguish the specific types (queen, pawn, bishop, rook, knight, king)
    - `pair_t` represents the position of a piece on the board using the imposed rules that is a letter and a number
- Developed the `moves_no_constraints` method
    - Handled for each piece their basic unrestricted movement logic
    - Implemented the logic for pawns, king, knight and queen and a helper function to check if a position is in the board while my teammate Gretl did those of the rook and the bishop
    - This method only accounted for the limits of the board but not the pieces at play

### Third week:
- Enhanced the `moves` method to build on `moves_no_constraints`:
    - Considered the positions of other pieces:
        - Prevented movements to squares with friendly pieces
        - Prevented non-knight pieces to "jump" over other pieces
        - Handled the specific pawn logic and the diagonal attack
- Added significant operator overloading and display functions to improve testing and code readability:
    - Removed unused functions after testing
- Transitioned from vectors to maps in `moves_no_constraints` and `moves` for improved efficiency
- Implemented the first algorithm to produce an output:
    - A greedy algorithm that captures the first opponent piece it can

## Part 2: Check and working on the main algorithm --(Four weeks)

### First thee weeks:
- Focused on coding the logic related to check positions, all implemented in the `check.cpp` file
    1. **Detecting Check**:
        - Determined if the king is in check.
    2. **Threat Analysis**:
        - Identified which pieces were threatening the king.
        - Calculated the paths those pieces take to endanger the king.
    3. **Handling Check**:
        - Found intersection paths between threatening pieces and potential moves.
        - Simulated possible moves to evaluate if they could remove the king from check.
            - This step involved a lot of debugging, since persistent errors arose from the simulations and the map and vector types.
- Created the `correct_moves` method:
    - Extended `moves` to filter out invalid moves 
    - Ensured they did not place the king in a check position or fail to take it out of a check position if it was already existing.

### Last week:
- Debugged issues causing crashes in specific game scenarios:
    - Traced the problem to castling, identified via log analysis
    - Fixed how promotion moves were outputed in the `move.csv` file
- Improved the algorithm's performance:
    - Enhanced the evaluation function of the minimax algorithm:
        - Prioritize king safety, pawn structure, and center control to increase piece mobility
        - Added penalities for moves that left pieces vulnerable to attacks
    - These changes stopped our algorithm from losing to the random AI but did not make it highly competitive