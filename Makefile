CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: main

main: main.cpp ppm.h log.h brandonM.cpp brandonP.cpp AbdulelahA.cpp JinH.cpp andyK.cpp
	g++ $(CFLAGS) main.cpp ./libraries/ppm.cpp ./libraries/log.cpp ./libraries/libggfonts.a -Wall -Wextra $(LFLAGS) -o main


clean:
	rm -f main
	rm -f *.o

