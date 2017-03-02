CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: main

main: main.cpp ppm.cpp log.cpp brandonM.cpp brandonP.cpp AbdulelahA.cpp jinxuH.cpp andyK.cpp 
	g++ $(CFLAGS) main.cpp ppm.cpp log.cpp jinxuH.cpp andyK.cpp brandonM.cpp brandonP.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o main


clean:
	rm -f main
	rm -f *.o

