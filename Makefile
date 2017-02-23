CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: rainforest brandonM brandonP AbdulelahA andyK JinH

rainforest: rainforest.cpp ppm.cpp log.cpp
	g++ $(CFLAGS) rainforest.cpp ppm.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o rainforest

brandonM: brandonM.cpp ppm.cpp log.cpp
	g++ $(CFLAGS) brandonM.cpp ppm.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o brandonM
	
brandonP: brandonP.cpp
	g++ brandonP.cpp ppm.cpp log.cpp libggfonts.a -Wall -o brandonP

brandonM: AbdulelahA.cpp ppm.cpp log.cpp
	g++ $(CFLAGS) AbdulelahA.cpp ppm.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o AbdulelahA
		
brandonM: JinH.cpp ppm.cpp log.cpp
	g++ $(CFLAGS) JinH.cpp ppm.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o JinH
		
brandonM: andyK.cpp ppm.cpp log.cpp
	g++ $(CFLAGS) andyK.cpp ppm.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o andyK
		
	
clean:
	rm -f rainforest, brandonM, brandonP, AbdulelahA, andyK, JinH
	rm -f *.o

