//This header file contains the definitions for the NumberGrid class
#ifndef _NUMBER_GRID_H_
#define _NUMBER_GRID_H_
#include "PPM.h"
#include <string>


class NumberGrid{
  public:
    NumberGrid( );
    NumberGrid(const int& height, const int& width);
    int getHeight( ) const;
    int getWidth( ) const;
    int getMaxNumber( ) const;
    void setGridSize(const int& height, const int& width);
    void setMaxNumber(const int& number);
    const std::vector< int >& getNumbers( ) const;
    int index(const int& row, const int& column) const;
    bool indexValid(const int& row, const int& column) const;
    bool numberValid(const int& number) const;
    int getNumber(const int& row, const int& column) const;
    void setNumber(const int& row, const int& column, const int& number);
    void setPPM(PPM& ppm) const;

  private:
    void setPixel(int row, int col, PPM& ppm) const;
    int mHeight;
    int mWidth;
    int mMax;
    std::vector<int> mGrid_vals;

};



#endif /*_NUMBER_GRID_H_*/
