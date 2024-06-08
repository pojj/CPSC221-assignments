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
    create_board();
    start_coord.first = 0;
    start_coord.second = 0;
    end_coord.first = 0;
    end_coord.second = 0;
}

// Frees all dynamically allocated memory associated with the board.
HexBoard::~HexBoard() {
    for (auto& kv : cells) {
        delete kv.second;   
    }
}

/**
 * Creates all neccessary HexCells up to the given radius and insert them into this->cells.
 */
void HexBoard::create_board() {
    for (int q = -radius; q <= radius; q++) {
        int r1 = std::max(-radius, -radius - q);
        int r2 = std::min(radius, radius - q);
        for (int r = r1; r <= r2; r++) {
            cells[{q, r}] = new HexCell({q, r});
        }
    }
}

/**
 * Gets the coordinates of the six neighbours of coord, in the sides order specified in HexCell.h.
 * @param coord The input coordinate.
 */
vector<pair<int, int>> HexBoard::get_neigh_coords(const pair<int, int>& coord) const {
    vector<pair<int, int>> neighbors;

    for (int i = 0; i < 6; i++) {
        int x = coord.first + directions[i][0];
        int y = coord.second + directions[i][1];
        neighbors.push_back({x, y});
    }

    return neighbors;
}

/**
 * Link two cells at the given coordinates by setting each cell's wall to false in the other cell's direction.
 * @param coord1 A coordinate of a HexCell to be linked.
 * @param coord2 A coordinate of a HexCell to be linked.
 * @note remember to link both directions!
 * REQUIRE: the two coords are neighbours
 */
void HexBoard::link(const pair<int, int>& coord1, const pair<int, int>& coord2) const {
    HexCell* c1 = cells.find(coord1)->second;
    HexCell* c2 = cells.find(coord2)->second;
    
    c1->walls[c1->get_neighbour_side(c2)] = false;
    c2->walls[c2->get_neighbour_side(c1)] = false;
}

/**
 * @param coord1 A coordinate of a HexCell
 * @param coord2 A coordinate of a HexCell
 * @return The cell distance (ignoring walls) between coord1 and coord2.
 */
int HexBoard::distance(const pair<int, int>& coord1, const pair<int, int>& coord2) const {
    int q1 = coord1.first;
    int r1 = coord1.second;
    int s1 = -q1 - r1;

    int q2 = coord2.first;
    int r2 = coord2.second;
    int s2 = -q2 - r2;

    return (abs(q1 - q2) + abs(r1 - r2) + abs(s1 - s2)) / 2;
}

/**
 * @return true if coord is at the edge of the board, false otherwise.
 */
bool HexBoard::is_edge(const pair<int, int>& coord) const {
    int q = coord.first;
    int r = coord.second;
    int s = -q - r;

    return abs(q) == radius || abs(r) == radius || abs(s) == radius;
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
    start_coord = start;
    rng.seed(seed);

    Stack<pair<int, int>> s;
    set<pair<int, int>> v;

    s.push(start);
    v.insert(start);

    while (!s.is_empty()) {
        pair<int, int> curr_coord = s.peek();
        int dist = cells[curr_coord]->path_dist_from_start;

        HexCell* neigh_cell = choose_neighbour(curr_coord, v, branch_prob);
        if (neigh_cell != nullptr) {
            link(curr_coord, neigh_cell->qr);

            s.push(neigh_cell->qr);
            v.insert(neigh_cell->qr);

            neigh_cell->path_dist_from_start = dist + 1;
            if (dist + 1 > longest_path_dist) {
                longest_path_dist = dist + 1;
                end_coord = neigh_cell->qr;
            }
        } else {
            s.pop();
        }
    }
}

/**
 * Populate (member variable) solution as a list of coordinates from start_coord to end_coord, represented as {q, r} pairs.

 * REQUIRE: generate_maze must be called already
 */
void HexBoard::solve_maze() {
    Stack<pair<int, int>> s;
    set<pair<int, int>> v;
    Stack<vector<pair<int, int>>> p;

    s.push(start_coord);
    v.insert(start_coord);
    p.push({start_coord});

    while (!s.is_empty()) {
        pair<int, int> curr = s.pop();
        vector<pair<int, int>> path = p.pop();

        if (curr == end_coord) {
            solution = path;
        }

        for (pair<int, int> neighbor: get_neigh_coords(curr)) {
            if (v.find(neighbor) == v.end()) {
                vector<pair<int, int>> newPath = path;
                newPath.push_back(neighbor);
                s.push(neighbor);
                v.insert(neighbor);
                p.push({newPath});
            }
        }
    }
}