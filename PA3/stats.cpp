/**
 *  @file stats.cpp
 *  @description implementation of a stats class for rapid calculation of color averages
 *   and total color differences in CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN
 */

#include "stats.h"

 /**
  *  Computes/retrieves the sum of a single color channel in a defined rectangular region
  *  @pre channel is a valid channel identifier
  *  @pre upper, left, lower, and right are valid image coordinates
  *  @param channel - one of 'r', 'g', or 'b'
  *  @param upper - y-coordinate of the upper edge of the rectangular region
  *  @param left - x-coordinate of the left side of the rectangular region
  *  @param lower - y-coordinate of the lower edge of the rectangular region
  *  @param right - x-coordinate of the right side of the rectangular region
  *  @return the sum of the appropriate color channel values in the defined rectangular area
  */
unsigned long Stats::GetColorSum(char channel, unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  
  //cout << "start GetColorSum" << endl;
  
  vector<vector<unsigned long>> *vect;

  switch (channel)
  {case 'r':
    vect = &sumR;
    break;

  case 'g':
    // code block
    vect = &sumG;
    break;

  case 'b':
    vect = &sumB;
    break;

  default:
    return 0;
  }

  unsigned long all = (*vect)[right][lower];
  unsigned long cornerRegion = left != 0 && upper != 0 ? (*vect)[left-1][upper-1] : 0;
  unsigned long topRegion = upper != 0 ? (*vect)[right][upper-1] : 0;
  unsigned long leftRegion = left != 0 ? (*vect)[left-1][lower]: 0;
  
  //cout << "end GetColorSum" << endl;

  return all - topRegion - leftRegion + cornerRegion;
}

/**
 *  Computes/retrieves the sum of alpha values in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the sum of the alpha values in the defined rectangular area
 */
double Stats::GetAlphaSum(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  //cout << "start GetAlphaSum" << endl;
  vector<vector<double>> *vect = &sumA;

  double all = (*vect)[right][lower];
  double cornerRegion = left != 0 && upper != 0 ? (*vect)[left-1][upper-1] : 0;
  double topRegion = upper != 0 ? (*vect)[right][upper-1] : 0;
  double leftRegion = left != 0 ? (*vect)[left-1][lower]: 0;
  
  //cout << "end GetAlphaSum" << endl;

  return all - topRegion - leftRegion + cornerRegion;
}

/**
 *  Computes/retrieves the squared sum of a single color channel in a defined rectangular region
 *  @pre channel is a valid channel identifier
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param channel - one of 'r', 'g', or 'b'
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the squared sum of the appropriate color channel values in the defined rectangular area
 */
unsigned long Stats::GetColorSumSq(char channel, unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  
  //cout << "start GetColorSumSq" << endl;

  vector<vector<unsigned long>> *vect;
  switch (channel)
  {
  case 'r':
    vect = &sumSqR;
    break;

  case 'g':
    // code block
    vect = &sumSqG;
    break;

  case 'b':
    vect = &sumSqB;
    break;

  default:
    return 0;
  }

  unsigned long all = (*vect)[right][lower];
  unsigned long cornerRegion = left != 0 && upper != 0 ? (*vect)[left-1][upper-1] : 0;
  unsigned long topRegion = upper != 0 ? (*vect)[right][upper-1] : 0;
  unsigned long leftRegion = left != 0 ? (*vect)[left-1][lower]: 0;

  //cout << "end GetColorSumSq" << endl;

  return all - topRegion - leftRegion + cornerRegion;
}

/**
 *  Computes/retrieves the squared sum of alpha values in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the squared sum of the alpha values in the defined rectangular area
 */
double Stats::GetAlphaSumSq(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  //cout << "start GetAlphaSumSq" << endl;

  vector<vector<double>> *vect = &sumSqA;

  double all = (*vect)[right][lower];
  double cornerRegion = left != 0 && upper != 0 ? (*vect)[left-1][upper-1] : 0;
  double topRegion = upper != 0 ? (*vect)[right][upper-1] : 0;
  double leftRegion = left != 0 ? (*vect)[left-1][lower]: 0;

  //cout << "end GetAlphaSumSq" << endl;

  return all - topRegion - leftRegion + cornerRegion;
}

/**
 *  Simple function to compute the number of pixels in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the area of the defined rectangular area, in pixels
 */
//NOTE: 0,0 0,0 returns 1, the pixles on the corners and edges are counted
unsigned int Stats::GetRectangleArea(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  unsigned int height = lower - upper + 1;
  unsigned int width = right - left + 1;
  unsigned int area = height * width;
  return area; // REPLACE THIS STUB
}

/**
 *  Parameterized constructor
 *  Builds the channel sum and squared sum vectors from the supplied input image.
 *  Each channel sum vector's entry (x,y) will contain the sum of their respective
 *  color channels of all pixels in the rectangular image region bounded by (0,0) and (x,y).
 *  Likewise, each channel squared sum vector's entry (x,y) will contain the squared sum of their
 *  respective color channels of all pixels in the rectangular image region bounded by (0,0) and (x,y).
 *
 *  ***DON'T FORGET TO PRE-MULTIPLY THE ALPHA CHANNEL***
 * 
 *  @param img - input image from which the channel sum vectors will be populated
 */
Stats::Stats(const PNG& img) {
  //cout << "start Stats" << endl;

  unsigned int height = img.height();
  unsigned int width = img.width();

  sumR.resize(width); sumG.resize(width); sumB.resize(width); sumA.resize(width);
  sumSqR.resize(width); sumSqG.resize(width); sumSqB.resize(width); sumSqA.resize(width);

  for (unsigned int i = 0; i < width; i++) {
    sumR[i].resize(height); sumG[i].resize(height); sumB[i].resize(height); sumA[i].resize(height);
    sumSqR[i].resize(height); sumSqG[i].resize(height); sumSqB[i].resize(height); sumSqA[i].resize(height);
  }

  unsigned long redTemp = 0;
  unsigned long blueTemp = 0;
  unsigned long greenTemp = 0;
  double alphaTemp = 0;

  unsigned long redSqTemp = 0;
  unsigned long blueSqTemp = 0;
  unsigned long greenSqTemp = 0;
  double alphaSqTemp = 0;

  RGBAPixel* pix;

  for (unsigned int y = 0; y < height; y++)
  {
    redTemp = 0;
    blueTemp = 0;
    greenTemp = 0;
    alphaTemp = 0;

    redSqTemp = 0;
    blueSqTemp = 0;
    greenSqTemp = 0;
    alphaSqTemp = 0;

    for (unsigned int x = 0; x < width; x++)
    {
      pix = img.getPixel(x, y);
      redTemp += (unsigned long) pix->r;
      greenTemp += (unsigned long)pix->g;
      blueTemp += (unsigned long)pix->b;
      alphaTemp += pix->a * 255.0;

      redSqTemp += (unsigned long)pix->r * (unsigned long)pix->r;
      blueSqTemp += (unsigned long)pix->g * (unsigned long)pix->g;
      greenSqTemp += (unsigned long)pix->b * (unsigned long)pix->b;
      alphaSqTemp += (pix->a * 255.0) * (pix->a * 255.0);

      if (y > 0) {
        sumR[x][y] = redTemp + sumR[x][y - 1];
        sumG[x][y] = greenTemp + sumG[x][y - 1];
        sumB[x][y] = blueTemp + sumB[x][y - 1];
        sumA[x][y] = alphaTemp + sumA[x][y - 1];

        sumSqR[x][y] = redSqTemp + sumSqR[x][y - 1];
        sumSqG[x][y] = greenSqTemp + sumSqG[x][y - 1];
        sumSqB[x][y] = blueSqTemp + sumSqB[x][y - 1];
        sumSqA[x][y] = alphaSqTemp + sumSqA[x][y - 1];
      } else {
        sumR[x][y] = redTemp;
        sumG[x][y] = greenTemp;
        sumB[x][y] = blueTemp;
        sumA[x][y] = alphaTemp;

        sumSqR[x][y] = redSqTemp;
        sumSqG[x][y] = greenSqTemp;
        sumSqB[x][y] = blueSqTemp;
        sumSqA[x][y] = alphaSqTemp;
      }
      
    }
  }

  // cout << endl;

  // for (int y = 0; y < height; y++) {
  //   for (int x = 0; x < width; x++) {
  //     cout << sumSqR[x][y] << " ";
  //   }
  //   cout << endl;
  // }

  // cout << GetColorSumSq('r', 1, 1, 2, 2) << endl;

  //cout << "start Stats" << endl;

}

/**
 *  Computes/retrieves the average color of all pixels contained in the rectangle
 *  bounded by upper, left, lower, and right. Fractional values should be
 *  truncated/rounded down for assignment into integer variables.
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return pixel containing the average color of the pixels in the defined rectangle
 */
RGBAPixel Stats::GetAvg(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  //cout << "start GetAvg" << endl;
  unsigned long red = GetColorSum('r', upper, left, lower, right);
  unsigned long green = GetColorSum('g', upper, left, lower, right);
  unsigned long blue = GetColorSum('b', upper, left, lower, right);
  double alpha = GetAlphaSum(upper, left, lower, right);
  unsigned int totalPixels = GetRectangleArea(upper, left, lower, right);
  red = red / totalPixels;
  green = green / totalPixels;
  blue = blue / totalPixels;
  alpha = alpha / totalPixels;

  //cout << "end GetAvg" << endl;

  return RGBAPixel(red, green, blue);// alpha/255);
}

/**
 *  Computes the total sum squared difference from the mean, for the specified rectangle.
 *  Each channel's sum squared difference is computed separately, and then added to form the total.
 *
 *  Note that using the GetAvg function in computing the sum squared difference will result in
 *  accumulation of error especially with larger rectangles.
 *  You should use more precise computation of the average color for this function's intermediate steps.
 * 
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return total sum of squared deviations from the mean, over all color channels.
 */
double Stats::GetSumSqDev(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  
  //cout << "start GetSumSqDev" << endl;

  double Sqred = GetColorSumSq('r', upper, left, lower, right);
  double Sqgreen = GetColorSumSq('g', upper, left, lower, right);
  double Sqblue = GetColorSumSq('b', upper, left, lower, right);
  double Sqalpha = GetAlphaSumSq(upper, left, lower, right);
  double totalPixels = GetRectangleArea(upper, left, lower, right);

  double red = GetColorSum('r', upper, left, lower, right);
  double green = GetColorSum('g', upper, left, lower, right);
  double blue = GetColorSum('b', upper, left, lower, right);
  double alpha = GetAlphaSum(upper, left, lower, right);

  double devRed = Sqred - red * red / totalPixels;
  double devGreen = Sqgreen - green * green / totalPixels;
  double devBlue = Sqblue - blue * blue / totalPixels;
  double devAlpha = Sqalpha - alpha * alpha / totalPixels;

  //cout << "end GetSumSqDev" << endl;

  return devRed + devGreen + devBlue; //+ devAlpha; // REPLACE THIS STUB
}