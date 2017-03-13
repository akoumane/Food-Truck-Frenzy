// Brandon Pitcher
// CMPS 3350 Lab 5
// Created: 23 February 2017
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
	system("convert burger.png burger.ppm");
	system("convert hamburger.png hamburger.ppm");
	system("convert hotdog.png hotdog.ppm");
	system("convert pizza.png pizza.ppm");
	system("convert plate.png plate.ppm");
	return;
}

void cleanUp()
{
	system("rm -f *.ppm");
	return;
}
