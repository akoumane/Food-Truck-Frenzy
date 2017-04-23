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

//==============================================================================
// Game Object Functions

Grid::Grid(int y, int x)
{
	yres = y;
	xres = x;
	for (int i=0; i<y; i++)
		for (int j=0; j<x; j++)
			grid[i][j] = 0;
}
void Grid::printGrid()
{
	// Press 'g' in game to view in terminal
	for (int i=0; i<yres; i++) {
		for (int j=0; j<xres; j++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
	cout << "\n\n\n";
}
int Grid::xdem()
{
	return xres;
}
int Grid::ydem()
{
	return yres;
}
Player::Player(int y, int x)
{
	xpos = x;
	ypos = y;
}
void Player::moveLeft()
{
	if (xpos - 1 < 0)
		return;
	xpos = xpos - 1;
}
void Player::moveRight(int x)	// Parameter is X_Dem
{
	if (ypos + 1 >= x)
		return;
	ypos = ypos -1;
}
void Player::moveDown(int y)	// Parameter is Y_Dem
{
	if (ypos + 1 >= y)
		return;
	ypos = ypos + 1;
}
void Player::moveUp()
{
	if (ypos - 1 < 0)
		return;
	ypos = ypos - 1;
}
int Player::xPos()
{
	return xpos;
}
int Player::yPos()
{
	return ypos;
}
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
	cout << "\n*** Removing any images left behind... ***\n\n";
	system("rm -f background.png background.ppm \
		customer1standing.png customer1standing.ppm \
		customer2standing.png customer2standing.ppm \
		customer3standing.png customer3standing.ppm \
		customer4standing.png customer4standing.ppm \
		customer1sitting.png customer1sitting.ppm \
		customer2sitting.png customer2sitting.ppm \
		customer3sitting.png customer3sitting.ppm \
	    customer4sitting.png customer4sitting.ppm \
		burgeronplateonside.png burgeronplateonside \
		menu.png menu.ppm \
		menu_defeat.png menu_defeat.ppm \
		menu_pause.png menu_pause.ppm \
		waiter.png waiter.ppm \
		waiterleftstep.png waiterleftstep.ppm \
		waiterrightstep.png waiterrightstep.ppm");
	cout << "\n*** Image removal complete.***\n\n";

	// copy images to main folder
	cout << "\n*** Copying images to main folder... ***\n\n";
	system("cp pixel-sprites/background.png .");
	system("cp pixel-sprites/menu.png .");
	system("cp pixel-sprites/menu_pause.png .");
	system("cp pixel-sprites/menu_defeat.png .");
	system("cp pixel-sprites/customer1standing.png .");
	system("cp pixel-sprites/customer2standing.png .");
	system("cp pixel-sprites/customer3standing.png .");
	system("cp pixel-sprites/customer4standing.png .");
	system("cp pixel-sprites/customer1sitting.png .");
	system("cp pixel-sprites/customer2sitting.png .");
	system("cp pixel-sprites/customer3sitting.png .");
	system("cp pixel-sprites/customer4sitting.png .");
	system("cp pixel-sprites/burgeronplateonside.png .");
	system("cp pixel-sprites/waiter.png .");
	system("cp pixel-sprites/waiterleftstep.png .");
	system("cp pixel-sprites/waiterrightstep.png .");
	cout << "\n*** Copying images complete. ***\n\n";

	// convert from png to ppm using terminal GIMP
	cout << "\n*** Converting .png images to .ppm... ***\n\n";
	system("convert menu.png menu.ppm");
	system("convert menu_defeat.png menu_defeat.ppm");
	system("convert menu_pause.png menu_pause.ppm");
	system("convert background.png background.ppm");
	system("convert customer1standing.png customer1standing.ppm");
	system("convert customer2standing.png customer2standing.ppm");
	system("convert customer3standing.png customer3standing.ppm");
	system("convert customer4standing.png customer4standing.ppm");
	system("convert customer1sitting.png customer1sitting.ppm");
	system("convert customer2sitting.png customer2sitting.ppm");
	system("convert customer3sitting.png customer3sitting.ppm");
	system("convert customer4sitting.png customer4sitting.ppm");
	system("convert burgeronplateonside.png burgeronplateonside.ppm");
	system("convert waiter.png waiter.ppm");
	system("convert waiterleftstep.png waiterleftstep.ppm");
	system("convert waiterrightstep.png waiterrightstep.ppm");
	cout << "\n*** Image conversion complete. ***\n\n";
	return;
}

void cleanUp()
{
	cout << "\n*** Cleaning up images... ***\n\n";
	system("rm -f 	background.png background.ppm \
		customer1standing.png customer1standing.ppm \
		customer2standing.png customer2standing.ppm \
		customer3standing.png customer3standing.ppm \
		customer4standing.png customer4standing.ppm \
		customer1sitting.png customer1sitting.ppm \
		customer2sitting.png customer2sitting.ppm \
		customer3sitting.png customer3sitting.ppm \
		customer4sitting.png customer4sitting.ppm \
		burgeronplateonside.png burgeronplateonside.ppm \
		menu.png menu.ppm \
		menu_defeat.png menu_defeat.ppm \
		menu_pause.png menu_pause.ppm \
		waiter.png waiter.ppm \
		waiterleftstep.png waiterleftstep.ppm \
		waiterrightstep.png waiterrightstep.ppm");
	cout << "\n*** Image clean up complete. ***\n\n";

	return;
}
