CXXFLAGS := -std=c++11 -Wall -Werror
CXX      := g++
all: ppm_menu

ppm_menu: ppm_menu.o image_menu.o PPM.o number_grid.o
	$(CXX) -o ppm_menu -std=c++11 ppm_menu.o image_menu.o PPM.o number_grid.o

ppm_menu.o: ppm_menu.cpp image_menu.cpp
	$(CXX)  $(CXXFLAGS) -c ppm_menu.cpp

image_menu.o: ppm_menu.cpp image_menu.cpp
	$(CXX)  $(CXXFLAGS) -c image_menu.cpp

PPM.o: ppm_menu.cpp image_menu.cpp
	$(CXX)  $(CXXFLAGS) -c PPM.cpp

number_grid.o: number_grid.cpp number_grid.h
	$(CXX)  $(CXXFLAGS) -c number_grid.cpp

clean:
	-rm -f *.o ppm_menu *~
