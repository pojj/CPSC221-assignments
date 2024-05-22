/**
 *  @file        twodlinkedlist-private.h
 *  @description Student-defined functions of TwoDLinkedList class, for CPSC 221 PA1
 *
 *  THIS FILE WILL BE SUBMITTED.
 *  YOU MAY ADD YOUR OWN PRIVATE MEMBER FUNCTION DECLARATIONS HERE.
 *  IF YOU DO NOT HAVE FUNCTIONS TO ADD, LEAVE THIS BLANK
 */

/**************************************/
/* ADD YOUR PRIVATE DECLARATIONS HERE */
/**************************************/
//Returns a horizontalList
TwoDNode *HorizontalList(PNG &img, unsigned int blockdimx, unsigned int blockSizex, unsigned int blockSizey, unsigned int topPixle);

// Combines two Lists of TwoDNodes into one single list and returns the head pointer of the list stacked on the bottom
TwoDNode *Combine(TwoDNode *fisrtHead, TwoDNode *secondHead);