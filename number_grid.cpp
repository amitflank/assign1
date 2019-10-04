#include "number_grid.h"


NumberGrid::NumberGrid(): mHeight(300), mWidth(400),
mMax(255),mGrid_vals(mHeight * mWidth, 0){
}

NumberGrid::NumberGrid(const int& height, const int& width): mHeight(height),
mWidth(width), mMax(255),mGrid_vals(mHeight * mWidth, 0){
}

int NumberGrid::getHeight() const{
  return mHeight;
}

int NumberGrid::getWidth() const{
  return mWidth;
}

int NumberGrid::getMaxNumber() const{
  return mMax;
}

void NumberGrid::setGridSize(const int& height, const int& width){
  if(height >= 2 && width >= 2){
    mGrid_vals.resize(height * width);
    mHeight = height;
    mWidth = width;
  }
}

void NumberGrid::setMaxNumber(const int& number){
  if(number >= 0){
    mMax = number;
  }
}

const std::vector<int>& NumberGrid::getNumbers() const{
  return mGrid_vals;
}

int NumberGrid::index(const int& row, const int& column) const{
  return row * getWidth() + column;
}

bool NumberGrid::indexValid(const int& row, const int& column) const{
  bool validRow = row >= 0 && row <  getHeight();
  bool validCol = column >= 0 && column <  getWidth();
  return validRow && validCol;
}

bool NumberGrid::numberValid(const int& number) const{
  bool nonNeg = number >= 0;
  bool nonOverMax = number <= getMaxNumber();
  return nonNeg && nonOverMax;
}

int NumberGrid::getNumber(const int& row, const int& column) const{
  if(indexValid(row, column)){
    int idx = index(row, column);
    return getNumbers()[idx];
  }
  return -1;
}

void NumberGrid::setNumber(const int& row, const int& column, const int& number){
  if(numberValid(number) && indexValid(row, column)){
    int idx = index(row, column);
    mGrid_vals[idx] = number;
  }
}

void NumberGrid::setPixel(int row, int col, PPM& ppm) const{
  int num = getNumber(row, col);
  if(num == 0){
    ppm.setPixel(row, col, 0, 0, 0);
  }
  else if(num == getMaxNumber()){
    ppm.setPixel(row, col, 63, 31, 31);
  }
  else if(num % 8 == 0){
    ppm.setPixel(row, col, 63, 63, 63);
  }
  else if(num % 8 == 1){
    ppm.setPixel(row, col, 63, 31, 31);
  }
  else if(num % 8 == 2){
    ppm.setPixel(row, col, 63, 63, 31);
  }
  else if(num % 8 == 3){
    ppm.setPixel(row, col, 31, 63, 31);
  }
  else if(num % 8 == 4){
    ppm.setPixel(row, col, 0, 0, 0);
  }
  else if(num % 8 == 5){
    ppm.setPixel(row, col, 31, 63, 63);
  }
  else if(num % 8 == 6){
    ppm.setPixel(row, col, 31, 31, 63);
  }
  else {
    ppm.setPixel(row, col, 63, 31, 63);
  }

}
void NumberGrid::setPPM(PPM& ppm) const{
  int width = getWidth();
  int height = getHeight();
  ppm.setMetaData(width, height, 63);
  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){
      setPixel(row, col, ppm);
    }
  }
}
