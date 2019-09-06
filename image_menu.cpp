#include <iostream>
#include <string>
#include <fstream>
#include "PPM.h"

std::string getString( std::istream& is, std::ostream& os, const std::string& prompt ) {

	std::string s;
	os << prompt;
	is >> s;
	return s;
}

int getInteger( std::istream& is, std::ostream& os, const std::string& prompt ) {

	int i;
	os << prompt;
	is >> i;
	return i;

}

double getDouble( std::istream& is, std::ostream& os, const std::string& prompt ) {

	double d;
	os << prompt;
	is >> d;
	return d;

}

int assignment1( std::istream& is, std::ostream& os ){

	std::string prompt1("What's your favorite color? ");
	std::string prompt2("What's your favorite integer? ");
	std::string prompt3("What's your favorite number? ");

	std::string color(getString(is, os, prompt1));

	int num_loops;
	num_loops = getInteger(is, os, prompt2);

	double num;
	num = getDouble(is, os, prompt3);

	for (int i = 0; i < num_loops; i++) {
		os << i + 1 << " " << color << " " << num << std::endl;
	}

	return num_loops;
}

//93.7% chance we end up with a memory leak or break something really
//stupidly here becuase file reading ops lol
//Also this function is totally not done atm so ya
void writeUserImage(std::istream& is, std::ostream& os, const PPM& p) {

	std::string file_prompt = "What is the file name? ";
	std::string filename = getString(is, os, file_prompt);
	std::ofstream outfile(filename.c_str());

	outfile << p;
	outfile.close();

}

int assignment2(std::istream& is, std::ostream& os) {

	//prompt user for width and height of image and calc max color val
	std::string prompt1("What is the width of the image? ");
	std::string prompt2("What's is the height of the image? ");

	int width = getInteger(is, os, prompt1);
	int height = getInteger(is, os, prompt2);
	int maxColorVal = (width + height) / 3;

	//init our ppm obj based on user info
	PPM img = PPM(height, width);
	img.setMaxColorValue(maxColorVal);


	for(int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {

			if(row < height / 2) {
				img.setChannel(row, col, 0, 0);
			}
			else{
				img.setChannel(row, col, 0, maxColorVal);
			}

			if(col < width / 2) {
				img.setChannel(row, col, 2, 0);
			}
			else{
				img.setChannel(row, col, 2, maxColorVal);
			}
			int green = (row + col) % (maxColorVal + 1);
			img.setChannel(row, col, 1, green);

		}


	}
	writeUserImage(is, os, img);
	return 0;
}
