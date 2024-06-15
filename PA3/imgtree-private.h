/**
 *  @file imgtree-private.h
 *  @description student-defined functions for binary tree class storing image data for CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN, EVEN IF YOU DO NOT ADD ANYTHING TO IT
 * 
 *  Usage: As this file is included entirely into imgtree.h by the #include statement on line 214
 *  you only need to write the function signature,
 *  e.g.
 *  void MyOwnSpecialFunction(int fave_num, ImgTreeNode* nd);
 * 
 *  and add/complete your implementation in imgtree.cpp
 */

void rClear(ImgTreeNode* node);

ImgTreeNode* rCopy(const ImgTreeNode* node);

unsigned int rCountLeaves(ImgTreeNode* node) const;

void rRender(PNG& img, unsigned int& scale, ImgTreeNode* node) const;

void rFlipHorizontal(ImgTreeNode* node);

//bool canClear(RGBAPixel color, double pct, double tol);
void rPrune(ImgTreeNode *node, double pct, double tol);

int findNumberInTol(RGBAPixel color, ImgTreeNode *node, double tol);
