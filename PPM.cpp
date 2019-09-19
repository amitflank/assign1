#include "PPM.h"
#include <sstream>

PPM::PPM() {
  setMaxColorValue(0);
  setHeight(0);
  setWidth(0);
  mImageData.resize(getImageVectorSize());
}

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
int PPM::getImageVectorSize() {
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
void PPM::setMetaData(int width, int height, int max_color){
  setWidth(width);
  setHeight(height);
  setMaxColorValue(max_color);
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
void PPM::assignToSource(int row, int col, int src_chan, PPM src_img) {
    int val = src_img.getChannel(row, col, src_chan);
    setPixel(row, col, val, val, val);
  }

void PPM::grayFromChannel(PPM& dst, const int& src_channel) const{
  int width = getWidth();
  int height = getHeight();
  int max_color_value = getMaxColorValue();
  dst.setMetaData(width, height, max_color_value);

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col ++) {
      dst.assignToSource(row, col, src_channel, *this);
      }
    }
  }

  void PPM::grayFromRed(PPM& dst) const {
    this->grayFromChannel(dst, 0);
  }
  void PPM::grayFromGreen(PPM& dst) const{
    this->grayFromChannel(dst, 1);
  }
  void PPM::grayFromBlue(PPM& dst) const{
    this->grayFromChannel(dst, 2);
  }


double PPM::linearColorimetricPixelValue(const int& row, const int& column) const{
  int red = getChannel(row, column, 0);
  int green = getChannel(row, column, 1);
  int blue = getChannel(row, column, 2);
  return (0.2126*red + 0.7152*green + 0.0722*blue);
}

//this is stupid bad coding yay for lazieness!!!
void PPM::grayFromLinearColorimetric(PPM& dst) const{
  int width = getWidth();
  int height = getHeight();
  int max_color_value = getMaxColorValue();
  dst.setMetaData(width, height, max_color_value);
  int val;

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col ++) {
      val = (int) linearColorimetricPixelValue(row, col);
      dst.setPixel(row, col, val, val, val);
    }
  }
}

//figure this operator overload stuff and do it later i guess
std::ostream& operator<<(std::ostream& os, const PPM& rhs) {
  char *vec = new char[rhs.mImageData.size()];

  int vec_size = 0;
  for (int i = 0; i < (int) rhs.mImageData.size(); i++) {
      vec[i] = rhs.mImageData[i];
      vec_size++;
  }

  os << 'P' << '6' << ' ' << rhs.getWidth() << ' ' << rhs.getHeight() << ' ' << rhs.getMaxColorValue() << std::endl;
  os.write((char *) vec, vec_size);

  return os;
}

int PPM::getRowFromIndex(int index){
  int num_cols = getWidth();

  int row = index / (num_cols * 3);
  return row;
}

int PPM::getColFromIndex(int index){
  int num_cols = getWidth();

  int row = getRowFromIndex(index);
  int col = (index - (row * num_cols * 3)) / 3;
  return col;
}

int PPM::getChanFromIndex(int index){
  int num_cols = getWidth();

  int row = getRowFromIndex(index);
  int col = getColFromIndex(index);

  int chan = index - (row * num_cols * 3) - col * 3;
  return chan;

}

void skipNL(std::istream& is)  {
  unsigned char c;
  while(true){
    if(is.peek() == '\n'){
      is.read((char*) &c,1);
    }
    else{
      break;
    }
  }
}
std::istream& operator>>(std::istream& is, PPM& rhs){
  unsigned char c;
  char tmp1;
  std::string tmp;
  int width, height, max;

  //get meta data assign it and skip first white space
  is >> tmp;
  skipNL(is);
  is >> width;
  rhs.setWidth(width);
  skipNL(is);
  is >> height;
  rhs.setHeight(height);
  skipNL(is);
  is >> max;
  rhs.setMaxColorValue(max);
  skipNL(is);

  int index = 0;
  int row;
  int col;
  int chan;


  while(index < width * height * 3) {
    is.read((char*) &tmp1,1);
    c = (unsigned char) tmp1;

    row = rhs.getRowFromIndex(index);
    col = rhs.getColFromIndex(index);
    chan = rhs.getChanFromIndex(index);

    rhs.setChannel(row, col, chan, c);
    index++;
  }
  return is;

}
