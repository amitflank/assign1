#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "image_menu.h"

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

void showMenu(std::ostream& os){
	os << "\nActions available:\n\n";
	os << "read1) Read file into input image 1.\n";
	os << "read2) Read file into input image 2.\n";
	os << "write) Write output image to file.\n";
	os << "copy) Copy input image 1 to output image.\n";
	os << "red-gray) Set output image from input image 1's grayscale from red.\n";
	os << "green-gray) Set output image from input image 1's grayscale from green.\n";
	os << "blue-gray) Set output image from input image 1's grayscale from blue.\n";
	os << "v-edge) Set output image from input image 1's vertical edge detection\n";
	os << "h-edge) Set output image from input image 1's horizontal edge detection\n";
	os << "linear-gray) Set output image from input image 1's grayscale from linear colorimetric.\n";
	os << "+) Set output image from sum of input image 1 and input image 2\n";
	os << "+=) Set input image 1 by adding in input image 2\n";
	os << "-) Set output image from difference of input image 1 and input image 2\n";
	os << "-=) Set input image 1 by subtracting input image 2\n";
	os << "*) Set output image from input image 1 multiplied by a number\n";
	os << "*=) Set input image 1 by multiplying by a number\n";
	os << "/) Set output image from input image 1 divided by a number\n";
	os << "/=) Set input image 1 by dividing by a number\n";
	os << "# Comment to end of line\n";
	os << "size) Set the size of input image 1\n";
	os << "max) Set the max color value of input image 1\n";
	os << "channel) Set a channel value in input image 1\n";
	os << "pixel) Set a pixel's 3 values in input image 1\n";
	os << "clear) Set all pixels to 0,0,0 in input image 1\n";
	os << "diamond) Draw a diamond shape in input image 1\n";
	os << "circle) Draw a circle shape in input image 1\n";
	os << "box) Draw a box shape in input image 1\n";
	os << "quiet) Toggle output quieting\n";
	os << "run) Run commands from another file\n";
	os << "grid) Configure the grid.\n";
	os << "square) Draw a square shape in input image 1\n";
	os << "grid-set) Set a single value in the grid.\n";
	os << "grid-apply) Use the grid values to set colors in the output image.\n";
	os << "quit) Quit\n\n";
}

std::string getChoice(std::istream& is, std::ostream& os) {
	std::string prompt("Choice? ");
	return getString(is, os, prompt);
}

void commentLine(std::istream& is) {
	char * buffer = new char [1];

	while(true) {
		is.read(buffer, 1);

		if (is.eof()) {
			break;
		}

		if(buffer[0] == '\n') {
			break;
		}
	}
}

void setSize(std::istream& is, std::ostream& os, PPM& src){
	std::string heightPrompt = "Height? ";
	std::string widthPrompt= "Width? ";
	src.setHeight(getInteger(is, os, heightPrompt));
	src.setWidth(getInteger(is, os, widthPrompt));
}

void setMaxColorValue(std::istream& is, std::ostream& os, PPM& src) {
	std::string maxPrompt = "Max color value? ";
	src.setMaxColorValue(getInteger(is, os, maxPrompt));
}

void setChannel(std::istream& is, std::ostream& os, PPM& src){
	int row = getInteger(is, os, "Row? ");
	int col = getInteger(is, os, "Column? ");
	int chan = getInteger(is, os, "Channel? ");
	int val = getInteger(is, os, "Value? ");
	src.setChannel(row, col, chan, val);
}

void setPixel(std::istream& is, std::ostream& os, PPM& src) {
	int row = getInteger(is, os, "Row? ");
	int col = getInteger(is, os, "Column? ");
	int red = getInteger(is, os, "Red? ");
	int green = getInteger(is, os, "Green? ");
	int blue = getInteger(is, os, "Blue? ");
	src.setPixel(row, col, red, green, blue);
}

void clearAll(PPM& src){
	int num_cols = src.getWidth();
	int num_rows = src.getHeight();
	const int black = 0; //RGB color for black

	for(int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			src.setPixel(row, col, black, black, black);
		}
	}
}

bool inDiamond(int row, int col, int cRow, int cCol, int size){
	if (std::abs(cRow - row) + std::abs(cCol - col) <= size) {
		return true;
	}
	return false;
}

void drawDiamond(std::istream& is, std::ostream& os, PPM& src) {
	int num_cols = src.getWidth();
	int num_rows = src.getHeight();

	int cRow = getInteger(is, os, "Center Row? ");
	int cCol = getInteger(is, os, "Center Column? ");
	int size = getInteger(is, os, "Size? ");
	int red = getInteger(is, os, "Red? ");
	int green = getInteger(is, os, "Green? ");
	int blue = getInteger(is, os, "Blue? ");

	for(int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			bool inD = inDiamond(row, col, cRow, cCol, size);
			if(inD) {
				src.setPixel(row, col, red, green, blue);
			}
		}
	}

}

bool inCircle(int row, int col, int cRow, int cCol, int radius){
	int distSqr = (col - cCol) * (col - cCol) + (row - cRow) * (row - cRow);
	int rSqr = radius * radius;
	if (distSqr <= rSqr){
		return true;
	}
	return false;
}

void drawCircle(std::istream& is, std::ostream& os, PPM& src){
	int num_cols = src.getWidth();
	int num_rows = src.getHeight();

	int cRow = getInteger(is, os, "Center Row? ");
	int cCol = getInteger(is, os, "Center Column? ");
	int radius = getInteger(is, os, "Radius? ");
	int red = getInteger(is, os, "Red? ");
	int green = getInteger(is, os, "Green? ");
	int blue = getInteger(is, os, "Blue? ");

	for(int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			bool inC = inCircle(row, col, cRow, cCol, radius);
			if(inC) {
				src.setPixel(row, col, red, green, blue);
			}
		}
	}

}

bool inBox(int row, int col, int lCol, int rCol, int tRow, int bRow){
	bool validCol = (col >= lCol) && (col <= rCol);
	bool validRow = (row >= tRow) &&  (row <= bRow);
	if (validRow && validCol) {
		return true;
	}
	return false;
}

void drawBox(std::istream& is, std::ostream& os, PPM& src){
	int num_cols = src.getWidth();
	int num_rows = src.getHeight();

	int tRow = getInteger(is, os, "Top Row? ");
	int lCol = getInteger(is, os, "Left Column? ");
	int bRow = getInteger(is, os, "Bottom Row? ");
	int rCol = getInteger(is, os, "Right Column? ");
	int red = getInteger(is, os, "Red? ");
	int green = getInteger(is, os, "Green? ");
	int blue = getInteger(is, os, "Blue? ");

	for(int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			bool inB = inBox(row, col, lCol, rCol, tRow, bRow);
			if(inB) {
				src.setPixel(row, col, red, green, blue);
			}
		}
	}
}
void takeAction(std::istream& is, std::ostream& os, const std::string& choice, PPM& input_image1, PPM& input_image2, PPM& output_image, NumberGrid& grid){

	if (choice.compare("write") == 0) {
		writeUserImage(is, os, output_image);
	}
	else if(choice.compare("read1") == 0){
		readUserImage(is, os, input_image1);
	}
	else if(choice.compare("read2") == 0){
		readUserImage(is, os, input_image2);
	}
	else if(choice.compare("+") == 0){
		plus(is, os, input_image1, input_image2, output_image);
	}
	else if(choice.compare("+=") == 0){
		plusEquals(is, os, input_image1, input_image2);
	}
	else if(choice.compare("-") == 0){
		minus(is, os, input_image1, input_image2, output_image);
	}
	else if(choice.compare("-=") == 0){
		minusEquals(is, os, input_image1, input_image2);
	}
	else if(choice.compare("*") == 0){
		times(is, os, input_image1, output_image);
	}
	else if(choice.compare("*=") == 0){
		timesEquals(is, os, input_image1);
	}
	else if(choice.compare("/") == 0){
		divide(is, os, input_image1, output_image);
	}
	else if(choice.compare("/=") == 0){
		divideEquals(is, os, input_image1);
	}
	else if(choice.compare("red-gray") == 0){
		input_image1.grayFromRed(output_image);
	}
	else if(choice.compare("blue-gray") == 0){
		input_image1.grayFromBlue(output_image);
	}
	else if(choice.compare("green-gray") == 0){
		input_image1.grayFromGreen(output_image);
	}
	else if(choice.compare("linear-gray") == 0){
		input_image1.grayFromLinearColorimetric(output_image);
	}
	else if(choice.compare("v-edge") == 0){
		input_image1.findVerticalEdges(output_image);
	}
	else if(choice.compare("h-edge") == 0){
		input_image1.findHorizontalEdges(output_image);
	}
	else if(choice.compare("quiet") == 0){
		int z = 0; //placeholder do nothing
		z++; //stupid compilier
	}
	else if(choice.compare("run") == 0){
		runFile(is, os, input_image1, input_image2, output_image, grid);
	}
	else if (choice.compare("copy") == 0) {
		output_image = input_image1;
	}
	//first char is comment
	else if (choice.at(0) == '#' && choice.length() > 0) {
	 	commentLine(is);
		}
	else if (choice.compare("size") == 0) {
		setSize(is, os, input_image1);
	}
	else if (choice.compare("max") == 0) {
		setMaxColorValue(is, os, input_image1);
	}
	else if (choice.compare("channel") == 0) {
		setChannel(is, os, input_image1);
	}
	else if (choice.compare("pixel") == 0) {
		setPixel(is, os, input_image1);
	}
	else if (choice.compare("clear") == 0) {
		clearAll(input_image1);
	}
	else if (choice.compare("diamond") == 0) {
		drawDiamond(is, os, input_image1);
	}
	else if (choice.compare("circle") == 0) {
		drawCircle(is, os, input_image1);
	}
	else if (choice.compare("box") == 0) {
		drawBox(is, os, input_image1);
	}
	else if (choice.compare("grid") == 0) {
		configureGrid(is, os, grid);
	}
	else if (choice.compare("grid-set") == 0) {
		setGrid(is, os, grid);
	}
	else if (choice.compare("grid-apply") == 0) {
		applyGrid(is, os, grid, output_image);
	}
	else if (choice.compare("square") == 0) {
		drawSquare(is, os, input_image1);
	}
	else if (choice.compare("quit") == 0) {
		int z = 0; //placeholder do nothing
		z++; //stupid compilier
	}
	//print error msg
	else {
		os << "Unknown action '" << choice << "'." << std::endl;
	}

}

void plusEquals(std::istream& is, std::ostream& os, PPM& src1, const PPM& src2){
	(void)is;
	(void)os;
	src1 += src2;
}

void minusEquals(std::istream& is, std::ostream& os, PPM& src1, const PPM& src2){
	(void)is;
	(void)os;
	src1 -= src2;
}

void timesEquals(std::istream& is, std::ostream& os, PPM& src){
	std::string prompt("Factor? ");
	double factor = getDouble(is, os, prompt);
	src *= factor;
}

void divideEquals(std::istream& is, std::ostream& os, PPM& src){
	std::string prompt("Factor? ");
	double factor = getDouble(is, os, prompt) ;
	src /= factor;
}

void plus(std::istream& is, std::ostream& os, const PPM& src1, const PPM& src2, PPM& dst){
	(void)is;
	(void)os;
	dst = src1 + src2;
}

void minus(std::istream& is, std::ostream& os, const PPM& src1, const PPM& src2, PPM& dst){
	(void)is;
	(void)os;
	dst = src1 - src2;
}

void times(std::istream& is, std::ostream& os, const PPM& src, PPM& dst){
	std::string prompt("Factor? ");
	double factor = getDouble(is, os, prompt);
	dst = src * factor;
}

void divide(std::istream& is, std::ostream& os, const PPM& src, PPM& dst){
	std::string prompt("Factor? ");
	double factor = getDouble(is, os, prompt);
	dst = src / factor;
}

void quietMenu(std::ostream& os, bool quiet){
	if(!quiet){
		showMenu(os);
	}
}
std::string quietChoice(std::istream& is, std::ostream& os, bool quiet){
	std::stringstream dummy;
	if(!quiet){
	 return getChoice(is, os);
	}
	else{
		return getChoice(is, dummy);
	}
}

void quietAction(std::istream& is, std::ostream& os, const std::string& choice, PPM& input_image1, PPM& input_image2, PPM& output_image, bool quiet, NumberGrid& grid){
	std::stringstream dummy;
	if(!quiet){
		takeAction(is, os, choice, input_image1, input_image2, output_image, grid);
	}
	else{
		takeAction(is, dummy, choice, input_image1, input_image2, output_image, grid);
	}
}
int imageMenu(std::istream& is, std::ostream& os){
	PPM img1 = PPM(); // tmp vals change in future i geuess
	PPM img2 = PPM();
	PPM outfile = PPM();
	bool quiet = false;
	NumberGrid grid = NumberGrid();

	while(true) {

		quietMenu(os, quiet);
		std::string choice = quietChoice(is, os, quiet);

		//We exit if we get a quit msg from user
		if (choice.compare("quit") == 0) {
			break;
		}
		if (choice.compare("quiet") == 0){
			quiet = !quiet;
		}
		quietAction(is, os, choice, img1, img2, outfile, quiet, grid);
	}
	return 0;
}

void readUserImage(std::istream& is, std::ostream& os, PPM& ppm){
	std::string file_prompt = "Input filename? ";
	std::string filename = getString(is, os, file_prompt);
	std::ifstream inFile(filename.c_str());

	inFile >> ppm;
	inFile.close();
}

int runFile(std::istream& is, std::ostream& os, PPM& input_image1, PPM& input_image2, PPM& output_image, NumberGrid& grid){
	std::string file_prompt = "File? ";
	std::string filename = getString(is, os, file_prompt);
	std::ifstream inFile(filename.c_str());


	if(inFile.is_open()){
		std::string choice;
		bool quiet = true;

		while(inFile.good()){

			choice = quietChoice(inFile, os, quiet);
			if (choice.compare("quit") == 0) {
				break;
			}
			quietAction(inFile, os, choice, input_image1, input_image2, output_image, quiet, grid);
		}
		inFile.close();
		return 0;
	}
	else{
		return 1;
	}
}

void configureGrid(std::istream& is, std::ostream& os, NumberGrid& grid){
	std::string prompt1 = "Grid Height? ";
	std::string prompt2 = "Grid Width? ";
	std::string prompt3 = "Grid Max Value? ";

	int height = getInteger(is, os, prompt1);
	int width = getInteger(is, os, prompt2);
	int max = getInteger(is, os, prompt3);

	grid.setGridSize(height, width);
	grid.setMaxNumber(max);
}

void setGrid(std::istream& is, std::ostream& os, NumberGrid& grid){
	std::string prompt1 = "Grid Row? ";
	std::string prompt2 = "Grid Column? ";
	std::string prompt3 = "Grid Value? ";

	int row = getInteger(is, os, prompt1);
	int col = getInteger(is, os, prompt2);
	int val = getInteger(is, os, prompt3);

	grid.setNumber(row, col, val);
}

void applyGrid(std::istream& is, std::ostream& os, NumberGrid& grid, PPM& dst){
	(void) is;
	(void) os;
	grid.setPPM(dst);
}

void drawSquare(std::istream& is, std::ostream& os, PPM& src){
	std::string prompt1 = "Row? ";
	std::string prompt2 = "Column? ";
	std::string prompt3 = "Size? ";
	std::string prompt4 = "Red? ";
	std::string prompt5 = "Green? ";
	std::string prompt6 = "Blue? ";

	int crow = getInteger(is, os, prompt1);
	int ccol = getInteger(is, os, prompt2);
	int size = getInteger(is, os, prompt3);
	int red = getInteger(is, os, prompt4);
	int green = getInteger(is, os, prompt5);
	int blue = getInteger(is, os, prompt6);
	bool validRow;
	bool validCol;



	for(int row = 0; row < src.getHeight(); row++){
		for(int col = 0; col < src.getWidth(); col++){
			validRow = (row > (crow - size / 2)) && (crow < (crow + size / 2));
			validCol = (col > (ccol - size / 2)) && (ccol < (ccol + size / 2));
			if(validCol && validRow){
				src.setPixel(row, col, red, green, blue);
			}
	}

}
