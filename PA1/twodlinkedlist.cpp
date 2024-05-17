/**
 * @file twodlinkedlist.cpp
 * @author your name(s)
 *
 * Defines a two-dimensional null-terminated doubly-linked list containing rectangular image pieces
 *  for CPSC 221 PA1
 *
 * COMPLETE THE FUNCTION BODIES IN THIS FILE AND SUBMIT TO PRAIRIELEARN
 */

#include "twodlinkedlist.h"

/**
 *  Deallocates any associated dynamic memory and sets private attributes appropriately
 *
 *  @post this list is empty
 */
void TwoDLinkedList::Clear() {
    // COMPLETE YOUR IMPLEMENTATION BELOW
	
}

/**
 *  Copies the data and structure of otherlist into this list
 *
 *  @post this list is a physically separate copy of otherlist
 */
void TwoDLinkedList::Copy(const TwoDLinkedList& otherlist) {
    // COMPLETE YOUR IMPLEMENTATION BELOW
	
}

/**
 *  Default constructor creates an empty list
 */
TwoDLinkedList::TwoDLinkedList() {
    // COMPLETE YOUR IMPLEMENTATION BELOW
	
}

/**
 *  Builds the structure of this list from the provided parameters.
 *  The dimension of individual blocks will be an even division
 *  of the input PNG's dimensions by blockdimx or blockdimy.
 *  Assume that supplied PNG dimensions will be divisible by
 *  blockdimx and blockdimy.
 *
 *  @pre PNG horizontal dimension is divisible by blockdimx
 *  @pre PNG vertical dimension is divisible by blockdimy
 *
 *  Example: PNG dimensions 320x240
 *           blockdimx = 4
 *           blockdimy = 2
 *           The constructed list will have the following Block and node structure:
 *
 *                +-----------+     +-----------+     +-----------+     +-----------+
 *  northwest --> |           | --> |           | --> |           | --> |           |
 *                |  80 x 120 |     |  80 x 120 |     |  80 x 120 |     |  80 x 120 |
 *                |           | <-- |           | <-- |           | <-- |           |
 *                +-----------+     +-----------+     +-----------+     +-----------+
 *                   |     ^           |     ^           |     ^           |     ^
 *                   v     |           v     |           v     |           v     |
 *                +-----------+     +-----------+     +-----------+     +-----------+
 *                |           | --> |           | --> |           | --> |           |
 *                |  80 x 120 |     |  80 x 120 |     |  80 x 120 |     |  80 x 120 |
 *                |           | <-- |           | <-- |           | <-- |           | <-- southeast
 *                +-----------+     +-----------+     +-----------+     +-----------+
 */
void TwoDLinkedList::Build(PNG& img, unsigned int blockdimx, unsigned int blockdimy) {
    // COMPLETE YOUR IMPLEMENTATION BELOW
	
}

/**
 *  Returns the horizontal dimension of this list (in blocks)
 */
unsigned int TwoDLinkedList::GetBlockDimensionX() const {
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    return 0;
}

/**
 *  Returns the vertical dimension of this list (in blocks)
 */
unsigned int TwoDLinkedList::GetBlockDimensionY() const {
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    return 0;
}

/**
 *  Places this lists's color data into a PNG of appropriate dimensions
 *  @param scale - integer multiplier for dimensions. 0 = scale by 0.5.
 */
PNG TwoDLinkedList::Render(unsigned int scale) const {
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    return PNG();
}

/**
 *  Reorganizes the list and node contents so that a rendered image will be flipped horizontally.
 *  This must be achieved by pointer manipulation. Do not deallocate any existing nodes, and
 *  do not allocate any new nodes.
 *
 *  Ensure that the integrity of north/south/east/west pointers of all nodes is maintained.
 *
 *  You may use up to O(n) time and space complexity, where n is the total number of nodes in the list.
 *
 *  Example: A, B, C, D etc. are physical nodes (each at a particular address)
 *  before:
 *   northwest -> A <-> B <-> C <-> D
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                E <-> F <-> G <-> H
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                I <-> J <-> K <-> L  <- southeast
 *
 *  after:
 *   northwest -> D <-> C <-> B <-> A
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                H <-> G <-> F <-> E
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                L <-> K <-> J <-> I  <- southeast
 */
void TwoDLinkedList::FlipHorizontal() {
    // COMPLETE YOUR IMPLEMENTATION BELOW
	
}

