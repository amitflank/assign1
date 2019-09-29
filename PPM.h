//This header file contains the definitions for the PPM class
#ifndef _PPM_H_
#define _PPM_H_
#include <iostream>
#include <vector>
#include <sstream>


class PPM {

  public:
    PPM( );
    PPM(const int& height, const int& width);
    int getHeight( ) const;
    int getWidth( ) const;
    int getMaxColorValue( ) const;
    int getChannel(const int& row, const int& column, const int& channel) const;
    bool indexValid(const int& row, const int& column, const int& channel) const;
    int index(const int& row, const int& column, const int& channel) const;
    bool valueValid(const int& value) const;
    void setHeight(const int& height);
    void setWidth(const int& width);
    void setMaxColorValue(const int& max_color_value);
    void setChannel(const int& row, const int& column, const int& channel, const int& value);
    void setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue);
    int getImageVectorSize() const;
    void grayFromChannel(PPM& dst, const int& src_channel) const;
    void grayFromRed(PPM& dst) const;
    void grayFromGreen(PPM& dst) const;
    void grayFromBlue(PPM& dst) const;
    double linearColorimetricPixelValue(const int& row, const int& column) const;
    void grayFromLinearColorimetric(PPM& dst) const;
    std::vector <int> mImageData;
    int getRowFromIndex(int index);
    int getColFromIndex(int index);
    int getChanFromIndex(int index);
    bool operator==(const PPM& rhs) const;
    bool operator!=(const PPM& rhs) const;
    bool operator<(const PPM& rhs) const;
    bool operator<=(const PPM& rhs) const;
    bool operator>(const PPM& rhs) const;
    bool operator>=(const PPM& rhs) const;
    PPM& operator+=(const PPM& rhs);
    PPM& operator-=(const PPM& rhs);
    PPM& operator*=(const double& rhs);
    PPM& operator/=(const double& rhs);
    PPM operator+(const PPM& rhs) const;
    PPM operator-(const PPM& rhs) const;
    PPM operator*(const double& rhs) const;
    PPM operator/(const double& rhs) const;
    int edgePixelValue(const int& row1, const int& column1, const int& row2, const int& column2) const;
    void findVerticalEdges(PPM& dst) const;
    void findHorizontalEdges(PPM& dst) const;

  private:
    void setMetaData(int width, int height, int max_color);
    void assignToSource(int row, int col, int src_chan, PPM src_img);
    void assignLegalVal(int row, int col, int chan, int val);
    void allEdges(PPM& dst, int edgeType) const;
    unsigned int mMaxColorValue;
    unsigned int mHeight;
    unsigned int mWidth;
};
//figure this operator overload stuff and do it later i guess
std::ostream& operator<<(std::ostream& os, const PPM& rhs);
std::istream& operator>>(std::istream& is, PPM& rhs);
void skipNL(std::istream& is);

#endif /*_PPM_H_*/
