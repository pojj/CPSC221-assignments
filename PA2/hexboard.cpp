#include "hexboard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

/**
 * Constructor. Creates a board with given radius, creating new HexCells and inserting them into this->cells by calling createBoard(). The default start_coord and end_coord are (0, 0).
 * @note There is no maze yet! The board is just a beehive for now.
 * @param rad The radius of the board
 */
HexBoard::HexBoard(int rad) {
    /**
     * @todo Your code here!
     */
}

// Frees all dynamically allocated memory associated with the board.
HexBoard::~HexBoard() {
    /**
     * @todo Your code here!
     */
}

/**
 * Creates all neccessary HexCells up to the given radius and insert them into this->cells.
 */
void HexBoard::create_board() {
    /**
     * @todo Your code here!
     */
}

/**
 * Gets the coordinates of the six neighbours of coord, in the sides order specified in HexCell.h.
 * @param coord The input coordinate.
 */
vector<pair<int, int>> HexBoard::get_neigh_coords(const pair<int, int>& coord) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return {};
}

/**
 * Link two cells at the given coordinates by setting each cell's wall to false in the other cell's direction.
 * @param coord1 A coordinate of a HexCell to be linked.
 * @param coord2 A coordinate of a HexCell to be linked.
 * @note remember to link both directions!
 * REQUIRE: the two coords are neighbours
 */
void HexBoard::link(const pair<int, int>& coord1, const pair<int, int>& coord2) const {
    /**
     * @todo Your code here!
     */
}

/**
 * @param coord1 A coordinate of a HexCell
 * @param coord2 A coordinate of a HexCell
 * @return The cell distance (ignoring walls) between coord1 and coord2.
 */
int HexBoard::distance(const pair<int, int>& coord1, const pair<int, int>& coord2) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return -1;
}

/**
 * @return true if coord is at the edge of the board, false otherwise.
 */
bool HexBoard::is_edge(const pair<int, int>& coord) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return false;
}

/**
 * Traverses the board via dfs to generate the maze, updating and keeping track of:
 * A. The largest path distance from start to an edge cell so far (this is not longest_path_dist!)

 * The algorithm goes as follows:
 * 0. Set the start_coord member variable
 * 1. Seed this->rng with seed
 * 2. Add the start_coord to a stack, and mark it as visited
 * 3. While the stack is not empty:

 *   a. Peek the top of the stack (call it curr_coord)
 *   b. Use choose_neighbour to choose the neighbour to visit
 *   c. If the neighbour exists, for that neighbour (call it neigh_cell) do:

 *     i. Link curr_coord with neigh_coord
 *     ii. Push neigh_coord into the stack, and mark it as visited
 *     iii. Update the neigh_cell's path distance to start
 *     iv. If necessary, update length of longest path so far (longest_path_dist)
 *     v. Update the end coordinate only if its path distance to start is strictly greater than the largest path distance from start to an edge cell so far.

 *   d. Otherwise (if choose_neighbour returns nullptr), pop the stack.

 * @param start The {q, r} coordinate of the start of the maze.
 * @param branch_prob Specifies how often it should "branch out" when choosing neighbours.
 *                    A small branch_prob means neighbours of the same dist from the start_coord are preferred
 *                    A large branch_prob means neighbours of a different dist from the start_coord are preferred
 * @param seed The seed used for the rng
 * REQUIRE: create_board() is already called
 */
void HexBoard::generate_maze(pair<int, int> start, double branch_prob, int seed) {
    /**
     * @todo Your code here!
     */
}

/**
 * Populate (member variable) solution as a list of coordinates from start_coord to end_coord, represented as {q, r} pairs.

 * REQUIRE: generate_maze must be called already
 */
void HexBoard::solve_maze() {
    /**
     * @todo Your code here!
     */
}