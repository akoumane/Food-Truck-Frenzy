//modified by:
//date:
//purpose:
//
//3350
//program: rainforest
//author:  Gordon Griesel
//date:    2013 to present
//
//This program demonstrates the use of OpenGL and XWindows
//
//Texture maps are displayed.
//Press B to see bigfoot roaming his forest.
//
//The rain builds up like snow on the ground.
//Fix it by removing each raindrop for the rain linked list.
//look for the 
//
//
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

extern "C" {
#include "fonts.h"
}

using namespace std;

void printBrandonName()
{
	Rect r;
	r.bot = 100;
	r.left = 140;
	r.center = 100;
	unsigned int color = 0x00dddd00;
	ggprint8b(&r, 16, color, "Brandon Martinez!!!");
}