#include "PPM.h"


PPM::PPM() {
  setMaxColorValue(0);
  setHeight(0);
  setWidth(0);
  mImageData.resize(getImageVectorSize());
}

  //could be an issue with refrence assignment and data type not matching
  //unisgne int and const int i guess
PPM::PPM(const int& height, const int& width) {
  setMaxColorValue(0);
  setHeight(height);
  setWidth(width);
  mImageData.resize(getImageVectorSize());
}

int PPM::getWidth() const {
  return mWidth;
}

int PPM::getHeight() const {
  return mHeight;
}

int PPM::getMaxColorValue() const {
  return mMaxColorValue;
}

int PPM::getChannel(const int& row, const int& column, const int& channel) const {

  if (indexValid(row, column, channel)) {
     int chan_val = mImageData[index(row, column, channel)];

    if (valueValid(chan_val)) {
      return chan_val;
    }

    return -1;
  }

  return -1;

}
bool PPM::indexValid( const int& row, const int& column, const int& channel) const {
  bool valid_row = (row >= 0 && row < getHeight());
  bool valid_col = (column >= 0 && column < getWidth());
  bool valid_channel = channel >= 0 && channel < 3;

  if (valid_row && valid_col && valid_channel) {
    return true;
  }
  return false;
}

int PPM::index(const int& row, const int& column, const int& channel) const {
    return (3 *  (row * getWidth() + column) + channel);
}

//Gets number of RGB values in image
unsigned int PPM::getImageVectorSize() {
  return getHeight() * getWidth() * 3;
}

bool PPM::valueValid( const int& value) const {
  if (value >= 0 && value <= getMaxColorValue()) {
    return true;
  }
  return false;

}

void PPM::setHeight( const int& height) {
  if (height >= 0) {
    mHeight = height;
    mImageData.resize(getImageVectorSize());
  }
}

void PPM::setWidth( const int& width) {
  if(width >= 0) {
    mWidth = width;
    mImageData.resize(getImageVectorSize());
  }

}

void PPM::setMaxColorValue( const int& max_color_value) {
  if(max_color_value >= 0 && max_color_value < 256){
    mMaxColorValue = max_color_value;
  }
}

void PPM::setChannel(const int& row, const int& column, const int& channel, const int& value) {
  if(indexValid(row, column, channel) && valueValid(value)) {
    int index_val = index(row, column, channel);
    mImageData[index_val] = value;
  }
}

void PPM::setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue) {
  setChannel(row, column, 0, red);
  setChannel(row, column, 1, green);
  setChannel(row, column, 2, blue);
}



//figure this operator overload stuff and do it later i guess
std::ostream& operator<<( std::ostream& os, const PPM& rhs) {
  char vec[rhs.mImageData.size()];


  for (int i = 0; i < rhs.mImageData.size(); i++) {
      vec[i] = rhs.mImageData[i];
  }

  os << 'P' << '6' << ' ' << rhs.getWidth() << ' ' << rhs.getHeight() << ' ' << rhs.getMaxColorValue() << std::endl;
  os.write((char *) &vec, sizeof(vec));

  return os;
}
