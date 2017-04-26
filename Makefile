CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: FoodTruckFrenzy test

FoodTruckFrenzy: main.cpp ppm.cpp log.cpp brandonM.cpp brandonP.cpp abdulelahA.cpp jinxuH.cpp jinxuHN.cpp andyK.cpp 
	g++ $(CFLAGS) main.cpp ppm.cpp log.cpp jinxuH.cpp andyK.cpp brandonM.cpp brandonP.cpp abdulelahA.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o FoodTruckFrenzy

test: main.cpp ppm.cpp log.cpp brandonM.cpp brandonP.cpp abdulelahA.cpp jinxuH.cpp jinxuHN.cpp andyK.cpp 
	g++ $(CFLAGS) main.cpp ppm.cpp log.cpp jinxuH.cpp andyK.cpp brandonM.cpp brandonP.cpp abdulelahA.cpp libggfonts.a -D RENDERTEST -Wall -Wextra $(LFLAGS) -o test

clean:
	rm -f FoodTruckFrenzy
	rm -f test
	rm -f *.o

