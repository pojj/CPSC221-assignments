#include "hexcell.h"

/**
 * HexCell constructor. Initializes all walls to be true and path_dist_from_start to 0.
 * @param QR Axial coordinates of the hex cell
 */
HexCell::HexCell(std::pair<int, int> QR) {
    qr = QR;
    path_dist_from_start = 0;
    for (bool& direction : walls)
        direction = true;
}

/**
 * Gets the side of a neighbour. Each side is represented with an int in [0,5].
 * See above for the definition of the sides
 * @param cell A neighbouring HexCell
 * @return The side of cell
 * REQUIRE: cell is a neighbour of this cell
 */
int HexCell::get_neighbour_side(const HexCell* cell) const {
    int q = qr.first - cell->qr.first;
    int r = qr.second - cell->qr.second;
    
    if (q == 0) {
        if (r == 1) 
            return N;
        else
            return S;
    } else if (q == 1) {
        if (r == 0)
            return NW;
        else
            return SW;
    } else {
        if (r == 0)
            return SW;
        else
            return NW;
    }
}