//This header file contains the definitions for the PPM class
#ifndef _PPM_H_
#define _PPM_H_
#include <iostream>
#include <vector>

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
    int getImageVectorSize();
    std::vector <int> mImageData;

  private:

    unsigned int mMaxColorValue;
    unsigned int mHeight;
    unsigned int mWidth;

};

#endif /*_PPM_H_*/

//figure this operator overload stuff and do it later i guess
std::ostream& operator<<( std::ostream& os, const PPM& rhs);
