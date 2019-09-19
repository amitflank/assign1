#ifndef _IMAGE_MENU_H_
#define _IMAGE_MENU_H_
#include <string>
#include <iostream>
#include "PPM.h"

std::string getString( std::istream& is, std::ostream& os, const std::string& prompt);
int getInteger(std::istream& is, std::ostream& os, const std::string& prompt);
double getDouble(std::istream& is, std::ostream& os, const std::string& prompt);
int assignment1(std::istream& is, std::ostream& os);
void writeUserImage(std::istream& is, std::ostream& os, const PPM& p);
int assignment2(std::istream& is, std::ostream& os);

void showMenu(std::ostream& os);
std::string getChoice(std::istream& is, std::ostream& os);
void commentLine(std::istream& is);
void setSize(std::istream& is, std::ostream& os, PPM& src);
void setMaxColorValue(std::istream& is, std::ostream& os, PPM& src);
void setChannel(std::istream& is, std::ostream& os, PPM& src);
void setPixel(std::istream& is, std::ostream& os, PPM& src);
void clearAll(PPM& src);
void drawDiamond(std::istream& is, std::ostream& os, PPM& src);
void drawCircle(std::istream& is, std::ostream& os, PPM& src);
void drawBox(std::istream& is, std::ostream& os, PPM& src);
void takeAction(std::istream& is, std::ostream& os, const std::string& choice, PPM& input_image1, PPM& input_image2, PPM& output_image);
int imageMenu(std::istream& is, std::ostream& os);
void readUserImage(std::istream& is, std::ostream& os, PPM& ppm);

bool inDiamond(int row, int col, int cRow, int cCol, int size);
bool inCircle(int row, int col, int cRow, int cCol, int radius);
bool inBox(int row, int col, int lCol, int rCol, int tRow, int bRow);

#endif /*_IMAGE_MENU_H_*/
