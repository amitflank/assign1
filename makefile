CC = g++


ppm_image: ppm_menu.o image_menu.o PPM.o
	$(CC) -o ppm_image -std=c++11 ppm_menu.o image_menu.o PPM.o

tmp: ppm_menu.cpp image_menu.cpp
	$(CC) -std=c++11 -c ppm_menu.cpp image_menu.cpp PPM.cpp


