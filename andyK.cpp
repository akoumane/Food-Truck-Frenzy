//Andy Koumane
//andyK.cpp

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "ppm.h"
#include <time.h>
using namespace std;

class Customer
{
	private:
		int xpos;
		int ypos;
		//random number will be chosen for foodChoice
		int foodChoice;

		//random number will be chosen for model
		int modelNum;

		bool inLine;
		bool inSeat;
		bool hasFood;
		bool isEating;
		bool finishFood;

	public:
		Customer()
		{
			srand(time(NULL));
			foodChoice = rand() % 4 + 1;
			modelNum = rand() % 4 + 1;
			inLine = true;
			inSeat = false;
			hasFood = false;
			isEating = false;
			finishFood = false;
		}
		void renderModel()
		{
			//reserved for rendering character model
		}
};

class Level
{
	private:
		int levelNum;
		int serveCount;
		bool start;
		Customer customers[];
	public:
		Level(int numLevel)
		{
			levelNum = numLevel;
			serveCount = 0;
			start = false;
		}
		
		void renderFood()
		{
			//reserved to render food images
		}
};
