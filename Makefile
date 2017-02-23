CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: rainforest brandonM brandonP

rainforest: rainforest.cpp ppm.cpp log.cpp
	g++ $(CFLAGS) rainforest.cpp ppm.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o rainforest

brandonM: brandonM.cpp ppm.cpp log.cpp
	g++ $(CFLAGS) brandonM.cpp ppm.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o brandonM
	
brandonP: brandonP.cpp
	g++ brandonP.cpp ppm.cpp log.cpp libggfonts.a -Wall -o brandonP

clean:
	rm -f rainforest, brandonM, brandonP
	rm -f *.o

