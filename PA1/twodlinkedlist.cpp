/**
 * @file twodlinkedlist.cpp
 * @author Carina Gu William Song
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
    TwoDNode *temp = nullptr;

    TwoDNode *current = northwest;
    TwoDNode *node = current;

    while (current != nullptr)
    {
        node = current;
        current = current->south;

        while (node != nullptr)
        {
            temp = node->east;
            delete node;
            node = temp;
        }
    }
    // COMPLETE YOUR IMPLEMENTATION BELOW
	
}

/**
 *  Copies the data and structure of otherlist into this list
 *
 *  @post this list is a physically separate copy of otherlist
 */
void TwoDLinkedList::Copy(const TwoDLinkedList& otherlist) {
    PNG img = otherlist.Render(1);
    Build(img, otherlist.GetBlockDimensionX(), otherlist.GetBlockDimensionY());
}

/**
 *  Default constructor creates an empty list
 */
TwoDLinkedList::TwoDLinkedList() {
    northwest = nullptr;
    southeast = nullptr;
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
    //Split img horizontaly

    unsigned int blockSizey = img.height() / blockdimy;
    unsigned int blockSizex = img.width() / blockdimx;

    unsigned int top = 0;
    TwoDNode *firstList = nullptr;
    TwoDNode *secondList = nullptr;
    TwoDNode *end = nullptr;

    northwest = HorizontalList(img, blockSizex, blockSizey, top);
    firstList = northwest;

    top += blockSizey;

    while(top <= img.height() - blockSizey) {
        secondList = HorizontalList(img, blockSizex, blockSizey, top);
        top += blockSizey;

        end = Combine(firstList, secondList);
        firstList = secondList;

        secondList = nullptr;
    }

    southeast = end;
    
}

// Returns the pointer of the start of a horizontalList of one row
TwoDNode *TwoDLinkedList::HorizontalList(PNG &img, unsigned int blockSizex, unsigned int blockSizey, unsigned int topPixle){
    unsigned int x = 0;
    Block block;
    TwoDNode *head = new TwoDNode();
    TwoDNode *current = head;
    TwoDNode *previous = nullptr;

    while ( x <= img.width() - blockSizex) {
        block.Build(blockSizex, blockSizey, topPixle, x, img);
        current->data = block;

        if (previous != nullptr) {
            previous->east = current;
            current->west = previous;
        }

        previous = current;
        current = new TwoDNode();
        x += blockSizex;
    }
    return head;
}

// Combines two Lists of TwoDNodes into one single list and returns the node at the bottom right corner of the list stacked on the bottom

TwoDNode *TwoDLinkedList::Combine(TwoDNode* firstHead, TwoDNode * secondHead)
{
    TwoDNode *top = firstHead;
    TwoDNode *bottom = secondHead;
    while (top != nullptr /*very unnecessary but it's just there*/ && bottom != nullptr)
    {
        top->south = bottom;
        bottom->north = top;

        top = top->east;

        if (top == nullptr) {
            return bottom;
        }

        bottom = bottom->east;
    }

    return nullptr;
}

/**
 *  Returns the horizontal dimension of this list (in blocks)
 */
unsigned int
TwoDLinkedList::GetBlockDimensionX() const
{
    int count = 0;
    TwoDNode *current = northwest;
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    while (current != nullptr) {
        count++;
        current = current->east;
    }
    return count;
}

/**
 *  Returns the vertical dimension of this list (in blocks)
 */
unsigned int TwoDLinkedList::GetBlockDimensionY() const {
    int count = 0;
    TwoDNode *current = northwest;
    while (current != nullptr)
    {
        count++;
        current = current->south;
    }
    return count;
}

/**
 *  Places this lists's color data into a PNG of appropriate dimensions
 *  @param scale - integer multiplier for dimensions. 0 = scale by 0.5.
 */
PNG TwoDLinkedList::Render(unsigned int scale) const {
    int width = northwest->data.GetWidth();
    int height = northwest->data.GetHeight();

    //scales width height:
    width *= (scale == 0) ? 0.5 : scale;
    height *= (scale == 0) ? 0.5 : scale;

    PNG img = PNG(width * GetBlockDimensionX(), height * GetBlockDimensionY());

    TwoDNode *current = northwest;
    TwoDNode *node = current;

    unsigned int upper = 0;
    unsigned int left = 0;

    while (current != nullptr)
    {
        
        while (node != nullptr)
        {
            node->data.Render(scale, upper*height, left*width, img);
            left++;
        }

        left = 0;
        upper++;
    }
    return img;
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
    TwoDNode *current = northwest;
    TwoDNode *node = current;
    TwoDNode *previousWest = nullptr; 

    while(current != nullptr) {
        node = current;
        current = current->south;
        while (node != nullptr) {
            node->data.FlipHorizontal();
            previousWest = node->west;
            node->west = node->east;

            if (node->north == nullptr && node->west == nullptr){
                northwest = node;
            }

            if (node->east == nullptr && node->south == nullptr) {
                southeast = node;
            }

            node = node->west;
        }

    }

}

