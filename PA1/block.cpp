/**
 * @file block.cpp
 * @author your name(s)
 *
 * Implements a rectangular image portion block for CPSC 221 PA1
 *
 * COMPLETE THE FUNCTION BODIES IN THIS FILE AND SUBMIT TO PRAIRIELEARN
 */

#include "block.h"

/**
 *  Sets the values in the data attribute, based on the w x h pixels rectangular region of sourceimg
 *  with the upper-left corner at (left, upper). The orientation of the pixels in the data vector
 *  must match with the orientation of the pixels in the PNG.
 *
 *  @param w - the width (in pixels) of the rectangular subimage region
 *  @param h - the height (in pixels) of the rectangular subimage region
 *  @param upper - the y-coordinate of the subimage region's upper-left corner
 *  @param left - the x-coordinate of the subimage regions's upper-left corner
 *  @param sourceimg - the input PNG image
 *
 *  @pre upper and left (and upper + h - 1, left + w - 1) are valid vector indices
 *  @post pixels contains sourceimg's pixel data starting from (left, upper)
 */
void Block::Build(unsigned int w, unsigned int h, unsigned int upper, unsigned int left, const PNG& sourceimg) {
    pixels.resize(h);
    for (unsigned i = 0; i < h; i++) {
        pixels[i].resize(w);
        for (unsigned j = 0; j < w; j++) {
            RGBAPixel* p = sourceimg.getPixel(left+j,upper+i);
            pixels[i][j] = *p;
        }
    }
}

/**
 *  Writes the pixel color data into the target PNG, starting from (left, upper)
 *
 *  @pre block's dimensions are even (multiples of 2)
 *  @pre upper, left are valid image indices
 *  @pre the rectangular region beginning at (left, upper) can completely receive all of the data attribute's color
 *  @post target PNG's subimage region has been filled with data attribute's pixel data
 *  @param scale - integer multiplier for dimensions. 0 = scale by 0.5.
 *                 For 0.5 scale, use an appropriate average color for each pixel.
 *                 For 1 and larger scale, scale each pixel using the original color with no blending.
 */
void Block::Render(unsigned int scale, unsigned int upper, unsigned int left, PNG& targetimg) const {
    // COMPLETE YOUR IMPLEMENTATION BELOW
	
}

/**
 *  Mirror this block's pixel data horizontally (along a vertical axis)
 *
 *  @post pixel data in this Block has been mirrored horizontally
 */
void Block::FlipHorizontal() {
    // COMPLETE YOUR IMPLEMENTATION BELOW
	
}

/**
 *  Returns the width (in pixels) of this Block
 *
 *  @return rectangular Block's width
 */
unsigned int Block::GetWidth() const {
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    return 0;
}

/**
 *  Returns the height (in pixels) of this Block
 *
 *  @return rectangular Block's height
 */
unsigned int Block::GetHeight() const {
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    return 0;
}