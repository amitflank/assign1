#include "PPM.h"


PPM::PPM() {
  mMaxColorValue = 0;
  mHeight = 0;
  mWidth = 0;
  mImageData.resize(getImageVectorSize());
}

PPM::PPM(const int& height, const int& width) {
  mMaxColorValue = 0;
  mHeight = height;
  mWidth = width;
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
int PPM::getImageVectorSize() const{
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

int PPM::edgePixelValue(const int& row1, const int& column1, const int& row2, const int& column2) const{
  double pix1 = linearColorimetricPixelValue(row1, column1);
  double pix2 = linearColorimetricPixelValue(row2, column2);
  double diff = abs(pix1 - pix2);
  double d_max = (double) getMaxColorValue();//not sure the how auto type casting works in c++ so i'll just make it explicit


  if(diff >= (.1 * d_max)){
    return getMaxColorValue();
  }
  return 0;
}

//Do operations for either vertical of horiontal allEdges
//edgeType = 0 for vertical, edgeType = 1 for horiontal
void PPM::allEdges(PPM& dst, int edgeType) const{
  int h = getHeight();
  int w = getWidth();
  int val = 0;

  dst.setMetaData(w, h, getMaxColorValue());

  for(int row = 0; row < h; row++){
    for(int col = 0; col < w; col++){

      if (col != 0 && edgeType == 0){
        val = edgePixelValue(row, col, row, col - 1);
      }
      if (row != 0 && edgeType == 1){
        val = edgePixelValue(row - 1, col, row, col);
      }
      dst.setPixel(row, col, val, val, val);
    }
  }
}

void PPM::findVerticalEdges(PPM& dst) const{
  allEdges(dst, 0);
}

void PPM::findHorizontalEdges(PPM& dst) const{
  allEdges(dst, 1);
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

bool PPM::operator==(const PPM& rhs) const{
  int t_size = getImageVectorSize();
  int c_size = rhs.getImageVectorSize();
  if(t_size == c_size){
    return true;
  }
  return false;
}

bool PPM::operator!=(const PPM& rhs) const{
  int t_size = getImageVectorSize();
  int c_size = rhs.getImageVectorSize();
  if(t_size ==  c_size){
    return false;
  }
  return true;
}

bool PPM::operator<(const PPM& rhs) const{
  int t_size = getImageVectorSize();
  int c_size = rhs.getImageVectorSize();
  if(t_size < c_size){
    return true;
  }
  return false;
}

bool PPM::operator<=(const PPM& rhs) const{
  int t_size = getImageVectorSize();
  int c_size = rhs.getImageVectorSize();
  if(t_size <= c_size){
    return true;
  }
  return false;
}

bool PPM::operator>(const PPM& rhs) const{
  int t_size = getImageVectorSize();
  int c_size = rhs.getImageVectorSize();
  if(t_size > c_size){
    return true;
  }
  return false;
}

bool PPM::operator>=(const PPM& rhs) const{
  int t_size = getImageVectorSize();
  int c_size = rhs.getImageVectorSize();
  if(t_size >= c_size){
    return true;
  }
  return false;
}

//Assign given channel to val if legal otherwise assign to closest legal value
void PPM::assignLegalVal(int row, int col, int chan, int val){
  int max = getMaxColorValue();
  if(val > max){
    setChannel(row, col, chan, max);
  }
  else if(val < 0){
    setChannel(row, col, chan, 0);
  }
  else{
    //std::cout << "Max is: " << max << " Val is: " << val << std::endl;
    setChannel(row, col, chan, val);
    //std::cout << "Post op chan is: " << getChannel(row, col, chan)<< std::endl;
  }
}

PPM& PPM::operator+=(const PPM& rhs){
  int width = getWidth();
  int height = getHeight();
  int val;

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++){
      for(int chan = 0; chan < 3; chan++){
        val =  this->getChannel(row, col, chan) + rhs.getChannel(row, col, chan);
        assignLegalVal(row, col, chan, val);
      }
    }
  }
  return *this;
}

PPM& PPM::operator-=(const PPM& rhs){
  int width = getWidth();
  int height = getHeight();
  int val;

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++){
      for(int chan = 0; chan < 3; chan++){
        val =  this->getChannel(row, col, chan) - rhs.getChannel(row, col, chan);
        assignLegalVal(row, col, chan, val);
      }
    }
  }
  return *this;
}

PPM& PPM::operator*=(const double& rhs){
  int width = getWidth();
  int height = getHeight();
  int val;
  //std::cout << "m_row is: " << height << "m_col is: " << width << std::endl;

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++){
      for(int chan = 0; chan < 3; chan++){
        val =  (int) (getChannel(row, col, chan) * rhs);
        //std::cout << "RHS is: " << rhs << "Val is: " << val  << std::endl;
        assignLegalVal(row, col, chan, val);
      }
    }
  }
  return *this;
}

PPM& PPM::operator/=(const double& rhs){
  int width = getWidth();
  int height = getHeight();
  int val;
  //int test;
  //std::cout << "m_row is: " << height << "m_col is: " << width << std::endl;

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++){
      for(int chan = 0; chan < 3; chan++){
    //    test = getChannel(row, col, chan);
        val =  (int) (getChannel(row, col, chan) / rhs);
        //std::cout << "Chan is: " << test << "Val is: " << val << rhs << std::endl;
        //std::cout << "RHS is: " << rhs << "Val is: " << val  << std::endl;
        assignLegalVal(row, col, chan, val);
        //test = getChannel(row, col, chan);
        //std::cout << "Post op chan is: " << test << std::endl;
      }
    }
  }
  return *this;
}

PPM PPM::operator+(const PPM& rhs) const{
  int width = getWidth();
  int height = getHeight();
  int max = getMaxColorValue();
  int val;

  PPM r_ppm = PPM(height, width);
  r_ppm.setMaxColorValue(max);

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++){
      for(int chan = 0; chan < 3; chan++){
        val =  this->getChannel(row, col, chan) + rhs.getChannel(row, col, chan);
        r_ppm.assignLegalVal(row, col, chan, val);
      }
    }
  }

  return r_ppm;
}

PPM PPM::operator-(const PPM& rhs) const{
  int width = getWidth();
  int height = getHeight();
  int max = getMaxColorValue();
  int val;

  PPM r_ppm = PPM(height, width);
  r_ppm.setMaxColorValue(max);

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++){
      for(int chan = 0; chan < 3; chan++){
        val =  getChannel(row, col, chan) - rhs.getChannel(row, col, chan);
        r_ppm.assignLegalVal(row, col, chan, val);
      }
    }
  }

  return r_ppm;
}

PPM PPM::operator*(const double& rhs) const{
  int width = getWidth();
  int height = getHeight();
  int max = getMaxColorValue();
  int val;
  //int test;

  PPM r_ppm = PPM(height, width);
  r_ppm.setMaxColorValue(max);

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++){
      for(int chan = 0; chan < 3; chan++){
        //test = getChannel(row, col, chan);
        val =  (int) (getChannel(row, col, chan) * rhs);
      //  std::cout << "Chan is: " << test << "Val is: " << val << std::endl;
        r_ppm.assignLegalVal(row, col, chan, val);
      //  test = r_ppm.getChannel(row, col, chan);
      //  std::cout << "Post op chan is: " << test << std::endl;
      }
    }
  }

  return r_ppm;
}

PPM PPM::operator/(const double& rhs) const{
  int width = getWidth();
  int height = getHeight();
  int max = getMaxColorValue();
  int val;

  PPM r_ppm = PPM(height, width);
  r_ppm.setMaxColorValue(max);

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++){
      for(int chan = 0; chan < 3; chan++){
        val =  (int) (getChannel(row, col, chan) / rhs);
        r_ppm.assignLegalVal(row, col, chan, val);
      }
    }
  }

  return r_ppm;
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
