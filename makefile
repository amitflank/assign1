CC = g++


question_3: ppm_menu.o image_menu.o
	$(CC) -o question_3 -std=c++11 ppm_menu.o image_menu.o

tmp: ppm_menu.cpp image_menu.cpp
	$(CC) -std=c++11 -c ppm_menu.cpp image_menu.cpp

