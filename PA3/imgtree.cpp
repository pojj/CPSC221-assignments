/**
 *  @file imgtree.cpp
 *  @description implementation of a binary tree class storing image data for CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN
 */

#include "imgtree.h"
// not necessary to include imgtree-private.h since it is already included in imgtree.h

/**
 *  Default constructor creates an empty tree
 */
ImgTree::ImgTree() {
    root = nullptr;
    imgwidth = 0;
    imgheight = 0;
}

/**
 *  Parameterized constructor creates a tree from an input image.
 *  Every leaf in the tree corresponds to a single pixel in the PNG.
 *  Every non-leaf node corresponds to a rectangle of pixels defined
 *  by upper, left, lower, and right image coordinates. A node will
 *  also store the average color over its defined rectangle. Note that
 *  this average MUST be freshly computed from the individual pixels in
 *  the image and NOT by computing a weighted average from the colors
 *  of its direct children, as this would lead to an accumulation of
 *  rounding errors due to the integer nature of RGB color channels.
 *
 *  A non-leaf node's children correspond to a partition of the node's
 *  rectangle into two smaller rectangles, either by a horizontal line
 *  creating an upper rectangle and a lower rectangle, or a vertical line
 *  creating a left rectangle and a right rectangle.
 *
 *  The split is determined as follows:
 *  1. If the current node's rectangle width is the same or larger than its height,
 *     then a vertical line will divide the rectangle into left and right rectangles.
 *     If the current node's rectangle width is smaller than its height,
 *     then a horizontal line will divide the rectangle into upper and lower rectangles.
 *  2. The coordinate of the dividing line is chosen such that combined sum squared
 *     deviations from the mean color in the left/upper and right/lower rectangles is minimal
 *     among all other potential dividing lines of the same orientation.
 *     e.g. for a region (0,0) to (3,2), the candidates are the vertical lines dividing the region into:
 *     - (0,0) to (0,2) and (1,0) to (3,2)
 *     - (0,0) to (1,2) and (2,0) to (3,2)
 *     - (0,0) to (2,2) and (3,2) to (3,2)
 *     The line which produces the minimal combined sum squared scores on the left
 *     and right will be used for the split.
 *  3. In the unlikely event that multiple candidates produce the same score, the one which
 *     most evenly splits the rectangular area will be chosen.
 *  4. In the even more unlikely even that two candidates produce the same score and produce
 *     the same minimal area difference, the one with the smaller coordinate will be chosen.
 */
ImgTree::ImgTree(const PNG& img) {
    imgwidth = img.width();
    imgheight = img.height();

    Stats s(img);

    root = BuildNode(s, 0, 0, imgheight-1, imgwidth-1);
}

/**
 *  Releases all heap memory associated with this tree, restoring it to an "empty tree" state.
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::Clear() {
    rClear(root);
}

void ImgTree::rClear(ImgTreeNode* node) {
    if (node->A != nullptr) {
        rClear(node->A);
        rClear(node->B);
    }
    delete node;
}

/**
 *  Copies the supplied parameter tree into this tree. Does not free any memory.
 *  Called by the copy constructor and operator=.
 *  Will be useful to define a recursive helper function for this.
 *  HINT: the helper should allocate a new node, and return a pointer to the allocated node.
 *        See the documention for BuildNode - this should work similarly.
 */
void ImgTree::Copy(const ImgTree& other) {
    imgwidth = other.imgwidth;
    imgheight = other.imgheight;
    root = rCopy(other.root);
}

ImgTreeNode* ImgTree::rCopy(const ImgTreeNode* other) {
    if (other == nullptr)
        return nullptr;
    
    ImgTreeNode* node = new ImgTreeNode(other->upper, other->left, other->lower, other->right, other->avg); 
    
    node->A = rCopy(other->A);
    node->B = rCopy(other->B);
    return node;
}

/**
 *  Recursive helper function for initial construction of the tree. Constructs a single
 *  node according to supplied Stats and the requirements specified by the constructor
 *  documentation, and returns a pointer to the completed node.
 *  @param s - populated Stats object for computing this node's attributes
 *  @param upr - y-coordinate of the upper edge of the node's rectangular region
 *  @param lft - x-coordinate of the left side of the node's rectangular region
 *  @param lwr - y-coordinate of the lower edge of the node's rectangular region
 *  @param rt - x-coordinate of the right side of the node's rectangular region
 *  @return - pointer to a (completed) newly-allocated node for the specified parameters.
 */
ImgTreeNode* ImgTree::BuildNode(Stats& s, unsigned int upr, unsigned int lft, unsigned int lwr, unsigned int rt) {
    unsigned int width = rt - lft + 1;
    unsigned int height = lwr - upr + 1;

    ImgTreeNode* node = new ImgTreeNode(upr, lft, lwr, rt, s.GetAvg(upr, lft, lwr, rt));

    if (width == 1 && height == 1) {
        // no children
    } else if (width >= height) {
        SplitInfo best;
        best.sumsqscore = __DBL_MAX__;
        best.coordinate = 0;
        unsigned int center = lft + width/2 - 1;

        for (unsigned int i = lft; i < rt; i++) {
            double score = s.GetSumSqDev(upr, lft, lwr, i) + s.GetSumSqDev(upr, i+1, lwr, rt);

            if (score < best.sumsqscore) {
                best.sumsqscore = score;
                best.coordinate = i;
            } else if (score == best.sumsqscore) {
                if (abs((int)i-(int)center) < abs((int)best.coordinate-(int)center)) {
                    best.sumsqscore = score;
                    best.coordinate = i;
                }
            }
        }
        node->A = BuildNode(s, upr, lft, lwr, best.coordinate);
        node->B = BuildNode(s, upr, best.coordinate+1, lwr, rt);
    } else {
        SplitInfo best;
        best.sumsqscore = __DBL_MAX__;
        best.coordinate = 0;
        unsigned int center = lft + height/2 - 1;

        for (unsigned int i = upr; i < lwr; i++) {
            double score = s.GetSumSqDev(upr, lft, i, rt) + s.GetSumSqDev(i+1, lft, lwr, rt);

            if (score < best.sumsqscore) {
                best.sumsqscore = score;
                best.coordinate = i;
            } else if (score == best.sumsqscore) {
                if (abs((int)i-(int)center) < abs((int)best.coordinate-(int)center)) {
                    best.sumsqscore = score;
                    best.coordinate = i;
                }
            }
        }
        node->A = BuildNode(s, upr, lft, best.coordinate, rt);
        node->B = BuildNode(s, best.coordinate+1, lft, lwr, rt);
    }

    return node;
}

/**
 *  Produces a PNG of appropriate dimensions and paints every leaf node's rectangle
 *  into the appropriate area of the PNG.
 *  May be called on pruned trees.
 *  @param scaling factor for how large to render the image. Assume this is >= 1.
 *  @return fully-colored PNG, painted from the tree's leaf node data
 */
PNG ImgTree::Render(unsigned int scale) const {
    PNG img = PNG(imgwidth*scale, imgheight*scale);

    rRender(img, scale, root);

    return img;
}

void ImgTree::rRender(PNG& img, unsigned int& scale, ImgTreeNode* node) const {
    if (node->A == nullptr) {
        for (int i = node->upper*scale; i <= node->lower*scale; i++) {
            for (int j = node->left*scale; j <= node->left*scale; j++) {
                *img.getPixel(j, i) = node->avg;
            }
        }
    } else {
        rRender(img, scale, node->A);
        rRender(img, scale, node->B);
    }

}

/**
 *  Rearranges a tree's internal pointers and node content so that its image data
 *  appears flipped horizontally when rendered.
 *  Beware that the tree may or may not have been pruned!
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::FlipHorizontal() {
    rFlipHorizontal(root);
}
void ImgTree::rFlipHorizontal(ImgTreeNode* node) {
    node->left = imgwidth - node->left - 1;
    node->right = imgwidth - node->right - 1;
    if (node->A != nullptr) {
        rFlipHorizontal(node->A);
        rFlipHorizontal(node->B);
    }
}

/**
 *  Trims subtrees as high as possible in the tree.
 *  A subtree is pruned (all decendants deallocated and child links set to null)
 *  if at least pct (out of 100) of its leaves are within tol of the average
 *  color in the subtree's root.
 *  Assume that this will only be called on trees which have not previously been pruned.
 *  Will be useful to define AT LEAST one recursive helper function for this.
 *  @pre pct is a valid value between 0 and 100
 *  @param pct percentage (out of 100) of leaf node descendants must be within the tolerance threshold
 *             of color difference in order to be pruned
 *  @param tol threshold color difference to qualify for pruning
 */
void ImgTree::Prune(double pct, double tol) {
    rPrune(root, pct, tol);
    // complete your implementation below
}

//bool ImgTree::canClear(RGBAPixel color, double pct, double tol)
//{
//}

void rPrune(ImgTreeNode *node, double pct, double tol) {
    if (node == nullptr) {
        return;
    }
    RGBAPixel color = node->avg;

    unsigned int total = rCountLeaves(node);

    int number = findNumberInTol(color, node, tol);

    double precent = (double)number / (double)total;

    if (precent >= pct) {
        rClear(node);
        return;
    }

    rPrune(node->A, pct, tol);

    rPrune(node->B, pct, tol);
}

int ImgTree::findNumberInTol(RGBAPixel color, ImgTreeNode *node, double tol)
{
    
    ImgTreeNode* left = node->A;
    ImgTreeNode* right = node->B;

    if (left == nullptr && right == nullptr)
    {
        double dist = color.dist(node->avg);
        return (dist <= tol) ? 1 : 0;
    }

    return findNumberInTol(color, left, tol) + findNumberInTol(color, right, tol);
}

// use RGBAPixel::dist(const RGBAPixel& other)
// use rClear(ImgTreeNode* node)

/**
 *  Counts the number of leaf nodes in the tree.
 *  Will be useful to define a recursive helper function for this.
 */
unsigned int ImgTree::CountLeaves() const {
    // complete your implementation below
    return rCountLeaves(root);
}

unsigned int ImgTree::rCountLeaves(ImgTreeNode* node) const {
    if (node->A == nullptr) {
        return 1;
    }
    return rCountLeaves(node->A) + rCountLeaves(node->B);
}
 