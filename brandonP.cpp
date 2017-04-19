// Brandon Pitcher
// CMPS 3350 Spring 2017
// Food Truck Frenzy

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
#include "brandonP.h"
extern "C" {
#include "fonts.h"
}

using namespace std;

int X_Dem = 50;
int Y_Dem = 50;

//==============================================================================
// Game Objects

class Grid {
	public:
		// Grid will be initialized to 0.
		// If data equals 1, then it is the player.
		// Computer players will be integers greater than 1.
		// Array will not be initalized to full 1080p resolution.
		int grid[1920][1080];
		int xres, yres;
		Grid(int y, int x) 
		{
			yres = y;
			xres = x;
			for (int i=0; i<y; i++)
				for (int j=0; j<x; j++)
					grid[i][j] = 0;
		}
		void printGrid()
		{
			for (int i=0; i<yres; i++) {
				for (int j=0; j<xres; j++)
					cout << grid[i][j] << " ";
				cout << endl;
			}

		}
};

class Player {
	public:
		int xpos;
		int ypos;
		int id;		// Integer stored in array to identify each character
		bool line;	// Is the customer waiting in line?
		bool served;	// Does the customer have food?
		bool done;	// Has the customer finished eating?
		void moveLeft()
		{
			if (xpos - 1 < 0)
				return;
			xpos = xpos - 1;
		}
		void moveRight()
		{
			if (ypos + 1 >= X_Dem)
				return;
			ypos = ypos -1;
		}
		void moveDown()
		{
			if (ypos + 1 >= Y_Dem)
				return;
			ypos = ypos + 1;
		}
		void moveUp()
		{
			if (ypos - 1 < 0)
				return;
			ypos = ypos - 1;
		}
		int xPos()
		{
			return xpos;
		}
		int yPos()
		{
			return ypos;
		}
};


//==============================================================================

void printName()
{
	Rect r;
	r.bot = 420;
	r.left = 315;	
	r.center = 300;
	unsigned int color = 0x00dddd00;
	ggprint8b(&r, 16, color, "Brandon Pitcher!!!");
}

void imageConvert()
{
	// remove converted ppm files to help with crash recovery
	system("rm -f background.png background.ppm customer1standing.png \
		customer1standing.ppm customer1sitting.png customer1sitting.ppm \
		customer2sitting.png customer2sitting.pp \
		customer3sitting.png customer3sitting.ppm \
	    customer4sitting.png customer4sitting.ppm \
		burgeronplateonside.png burgeronplateonside menu.png menu.ppm");

	// copy images to main folder
	system("cp pixel-sprites/background.png .");
	system("cp pixel-sprites/menu.png .");
	system("cp pixel-sprites/customer1standing.png .");
	system("cp pixel-sprites/customer1sitting.png .");
	system("cp pixel-sprites/customer2sitting.png .");
	system("cp pixel-sprites/customer3sitting.png .");
	system("cp pixel-sprites/customer4sitting.png .");
	system("cp pixel-sprites/burgeronplateonside.png .");
	

	// convert from png to ppm
	system("convert menu.png menu.ppm");
	system("convert background.png background.ppm");
	system("convert customer1standing.png customer1standing.ppm");
	system("convert customer1sitting.png customer1sitting.ppm");
	system("convert customer2sitting.png customer2sitting.ppm");
	system("convert customer3sitting.png customer3sitting.ppm");
	system("convert customer4sitting.png customer4sitting.ppm");
	system("convert burgeronplateonside.png burgeronplateonside.ppm");

	return;
}

void cleanUp()
{
	system("rm -f burger.ppm hamburger.ppm hotdog.ppm pizza.ppm \
			plate.ppm burger.png hamburger.png hotdog.png pizza.png \
			plate.png background.png background.ppm customer1standing.png \
			customer1standing.ppm customer1sitting.png customer1sitting.ppm \
			customer2sitting.png customer2sitting.pp \
			customer3sitting.png customer3sitting.ppm \
			customer4sitting.png customer4sitting.ppm \
			burgeronplateonside.png burgeronplateonside.ppm menu.png menu.ppm");
	
	return;
}
