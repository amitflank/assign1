CC = g++

all: ppm_menu

ppm_menu: ppm_menu.o image_menu.o PPM.o
	$(CC) -o ppm_menu -std=c++11 ppm_menu.o image_menu.o PPM.o

ppm_menu.o: ppm_menu.cpp image_menu.cpp
	$(CC) -std=c++11 -Wpedantic -g -Wall -Wextra -Werror -I. -pthread -c ppm_menu.cpp 

image_menu.o: ppm_menu.cpp image_menu.cpp
	$(CC) -std=c++11 -Wpedantic -g -Wall -Wextra -Werror -I. -pthread -c image_menu.cpp

PPM.o: ppm_menu.cpp image_menu.cpp
	$(CC) -std=c++11 -Wpedantic -g -Wall -Wextra -Werror -I. -pthread -c PPM.cpp

clean:
	-rm -f *.o ppm_menu *~
