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
#include "andyK.h"
extern "C" {
#include "fonts.h"
}
using namespace std;

#define YMAX
#define XMAX
/*
void Food::makeFood()
{
    burgerOnSide = ppm6GetImage("burgeronplateonside.ppm");
    glGenTextures(1, &burgerOnSideTexture);

	//Burger on side of truck
    glBindTexture(GL_TEXTURE_2D, burgerOnSideTexture);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    burgerOnSide->width, burgerOnSide->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, burgerOnSide->data);
}
*/
Food::Food()
{
	on_side = 1;
	on_table = 0;
	moving = 0;
	ypos = 555;
	xpos = 482;
	//makeFood();
}
/*
void Food::renderFood()
{
	switch(food_id) {
		case 1:
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			if (on_side)
				glBindTexture(GL_TEXTURE_2D, burgeronplateonside_texture);
			if (on_table)
				glBindTexture(GL_TEXTURE_2D, burgerontable_texture);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(xpos, ypos);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(xpos, ypos+95);
		    glTexCoord2f(1.0f, 0.0f); glVertex2i(xpos+95, ypos+95);
		    glTexCoord2f(1.0f, 1.0f); glVertex2i(xpos+95, ypos);
		    glEnd();
		    glPopMatrix();
	}
}
*/
// Rendering waiter
Ppmimage *waiter = NULL;
GLuint waiterTexture;

void renderWaiter(int ypos, int xpos)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, waiterTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(xpos, ypos);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(xpos, ypos+95);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xpos+95, ypos+95);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xpos+95, ypos);
    glEnd();
    glPopMatrix();
	return;
}

void makeWaiter()
{
	waiter = ppm6GetImage("waiter.ppm");
	glGenTextures(1, &waiterTexture);
	glBindTexture(GL_TEXTURE_2D, waiterTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    waiter->width, waiter->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, waiter->data);
	return;
}

//==============================================================================
// Game Object Functions

Grid::Grid(int y, int x)
{
	yres = y;
	xres = x;
	for (int i=0; i<y; i++) {
		for (int j=0; j<x; j++) {
			grid[i][j] = 0;
		}
	}
	// Set tables
	grid[2][1] = 9;
	grid[4][1] = 9;
	grid[2][5] = 9;
	grid[4][5] = 9;
	// Set chairs
	grid[2][0] = 8;
	grid[4][0] = 8;
	grid[2][6] = 8;
	grid[4][6] = 8;
	// Set restriced area
	grid[3][0] = 7;
	grid[3][1] = 7;
	grid[3][5] = 7;
	grid[3][6] = 7;
	for (int i=0; i<7; i++) {
		grid[0][i] = 7;
	}
	grid[0][1] =0;
}
void Grid::printGrid()
{
	// Press 'g' in game to view in terminal
	for (int i=0; i<yres; i++) {
		for (int j=0; j<xres; j++) {
			cout << grid[i][j] << "   ";
		}
		cout << endl;
	}
	cout << "\n\n\n";
}
void Grid::gridItem(int y, int x, int id)
{
	grid[y][x] = id;
	return;
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
	//if (xpos - 1 < 0)
		//return;
	xpos = xpos - 5;
}
void Player::moveRight()	// Parameter is X_Dem
{
//	if (ypos + 1 >= x)
//		return;
	xpos = xpos + 5;
}
void Player::moveDown()	// Parameter is Y_Dem
{
//	if (ypos + 1 >= y)
//		return;
	ypos = ypos + 5;
}
void Player::moveUp()
{
//	if (ypos - 1 < 0)
//		return;
	ypos = ypos - 5;
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
		menu_help.png menu_help.ppm \
		menu_victory.png menu_victory.ppm \
		waiter.png waiter.ppm \
		waiterleftstep.png waiterleftstep.ppm \
		waiterrightstep.png waiterrightstep.ppm \
		0.png 0.ppm 1.png 1.ppm 2.png 2.ppm \
		3.png 3.ppm 4.png 4.ppm 5.png 5.ppm \
		6.png 6.ppm 7.png 7.ppm 8.png 8.ppm \
		9.png 9.ppm");
	cout << "\n*** Image removal complete.***\n\n";

	// copy images to main folder
	cout << "\n*** Copying images to main folder... ***\n\n";
	system("cp pixel-sprites/background.png .");
	system("cp pixel-sprites/menu.png .");
	system("cp pixel-sprites/menu_pause.png .");
	system("cp pixel-sprites/menu_defeat.png .");
	system("cp pixel-sprites/menu_help.png .");
	system("cp pixel-sprites/menu_victory.png .");
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
	system("cp pixel-sprites/0.png .");
	system("cp pixel-sprites/1.png .");
	system("cp pixel-sprites/2.png .");
	system("cp pixel-sprites/3.png .");
	system("cp pixel-sprites/4.png .");
	system("cp pixel-sprites/5.png .");
	system("cp pixel-sprites/6.png .");
	system("cp pixel-sprites/7.png .");
	system("cp pixel-sprites/8.png .");
	system("cp pixel-sprites/9.png .");
	cout << "\n*** Copying images complete. ***\n\n";

	// convert from png to ppm using terminal GIMP
	cout << "\n*** Converting .png images to .ppm... ***\n\n";
	system("convert menu.png menu.ppm");
	system("convert menu_defeat.png menu_defeat.ppm");
	system("convert menu_pause.png menu_pause.ppm");
	system("convert menu_help.png menu_help.ppm");
	system("convert menu_victory.png menu_victory.ppm");
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
	system("convert 0.png 0.ppm");
	system("convert 1.png 1.ppm");
	system("convert 2.png 2.ppm");
	system("convert 3.png 3.ppm");
	system("convert 4.png 4.ppm");
	system("convert 5.png 5.ppm");
	system("convert 6.png 6.ppm");
	system("convert 7.png 7.ppm");
	system("convert 8.png 8.ppm");
	system("convert 9.png 9.ppm");
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
		menu_help.png menu_help.ppm \
		menu_victory.png menu_victory.ppm \
		menu_pause.png menu_pause.ppm \
		waiter.png waiter.ppm \
		waiterleftstep.png waiterleftstep.ppm \
		waiterrightstep.png waiterrightstep.ppm \
		0.png 0.ppm 1.png 1.ppm 2.png 2.ppm \
		3.png 3.ppm 4.png 4.ppm 5.png 5.ppm \
		6.png 6.ppm 7.png 7.ppm 8.png 8.ppm \
		9.png 9.ppm");
	cout << "\n*** Image clean up complete. ***\n\n";

	return;
}
