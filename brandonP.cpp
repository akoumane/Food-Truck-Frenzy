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

#define YMAX 394
#define XMAX 668
#define YMIN 0
#define XMIN 8
#define STEP_SIZE 6

/*
void interaction(Player &p, Food &f1, Food &f2, Food &f3, Food &f4, Food &f5
    Food &f6)
{
    if (p->xPos() >= 439 && p->xPos() <= 475 && p->yPos() >= 382 &&
        p->yPos() <= 338) {

    }
    if (p->xPo

*/
void Food::makeFood()
{
    burgeronplateonside = ppm6GetImage("burgeronplateonside.ppm");
    glGenTextures(1, &burgeronplateonside_texture);
    glBindTexture(GL_TEXTURE_2D, burgeronplateonside_texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    burgeronplateonside->width, burgeronplateonside->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, burgeronplateonside->data);

	burgerontable = ppm6GetImage("burgerontable.ppm");
	glGenTextures(1, &burgerontable_texture);
	glBindTexture(GL_TEXTURE_2D, burgerontable_texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		burgerontable->width, burgerontable->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, burgerontable->data);

	hotdogonplateonside = ppm6GetImage("hotdogonplateonside.ppm");
    glGenTextures(1, &hotdogonplateonside_texture);
    glBindTexture(GL_TEXTURE_2D, hotdogonplateonside_texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    hotdogonplateonside->width, hotdogonplateonside->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, hotdogonplateonside->data);

	hotdogontable = ppm6GetImage("hotdogontable.ppm");
    glGenTextures(1, &hotdogontable_texture);
    glBindTexture(GL_TEXTURE_2D, hotdogontable_texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    hotdogontable->width, hotdogontable->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, hotdogontable->data);

	pizzaonplateonside = ppm6GetImage("pizzaonplateonside.ppm");
    glGenTextures(1, &pizzaonplateonside_texture);
    glBindTexture(GL_TEXTURE_2D, pizzaonplateonside_texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    pizzaonplateonside->width, pizzaonplateonside->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, pizzaonplateonside->data);

	pizzaontable = ppm6GetImage("pizzaontable.ppm");
	glGenTextures(1, &pizzaontable_texture);
	glBindTexture(GL_TEXTURE_2D, pizzaontable_texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		pizzaontable->width, pizzaontable->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, pizzaontable->data);

}

Food::Food()
{
	on_side = 1;
	on_table = 0;
	moving = 0;
	ypos = 555;
	xpos = 482;
	makeFood();
}

bool Food::check_on_side()
{
	return on_side;
}

bool Food::check_on_table()
{
	return on_table;
}

bool Food::check_moving()
{
	return moving;
}

void Food::set_on_side()
{
	on_side = 1;
	on_table = 0;
	moving = 0;
	return;
}

void Food::set_on_table()
{
	on_side = 0;
	on_table = 1;
	moving = 0;
	return;
}

void Food::set_moving()
{
	on_side = 0;
	on_table = 0;
	moving = 1;
	return;
}

void Food::setPos(int table)
{
	// 1 = top left table
	// 2 = top right table
	// 3 = bottom left table
	// 4 = bottom right table
	// 5 = serving table position 1
	// 6 = serving table position 2
	if (table < 1 || table > 6) {
		cout << "ERROR: table out of bounds\n"
			 << "brandonP.cpp void Food::setPos(int table)\n";
		return;
	}
	if (moving) {
		xpos = 9999;
		ypos = 9999;
		return;
	}
	switch (table)
	{
		case 1:
			xpos = 124;
			ypos = 270;
			break;
		case 2:
			xpos = 580;
			ypos = 270;
			break;
		case 3:
			xpos = 124;
			ypos = 66;
			break;
		case 4:
			xpos = 580;
			ypos = 66;
			break;
		case 5:
			xpos = 482;
			ypos = 556;
			break;
		case 6:
			xpos = 625;
			ypos = 556;
			break;
	}
}

void Food::renderFood(bool in_seat, int seat_num, int food_id)
{
	int width = 64;
	if (!in_seat)
		return;
	setPos(seat_num);
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
			glTexCoord2f(0.0f, 0.0f); glVertex2i(xpos, ypos+width);
		    glTexCoord2f(1.0f, 0.0f); glVertex2i(xpos+width, ypos+width);
		    glTexCoord2f(1.0f, 1.0f); glVertex2i(xpos+width, ypos);
		    glEnd();
		    glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			if (on_side)
				glBindTexture(GL_TEXTURE_2D, hotdogonplateonside_texture);
			if (on_table)
				glBindTexture(GL_TEXTURE_2D, hotdogontable_texture);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(xpos, ypos);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(xpos, ypos+width);
		    glTexCoord2f(1.0f, 0.0f); glVertex2i(xpos+width, ypos+width);
		    glTexCoord2f(1.0f, 1.0f); glVertex2i(xpos+width, ypos);
			glEnd();
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			if (on_side)
				glBindTexture(GL_TEXTURE_2D, pizzaonplateonside_texture);
			if (on_table)
				glBindTexture(GL_TEXTURE_2D, pizzaontable_texture);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(xpos, ypos);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(xpos, ypos+width);
		    glTexCoord2f(1.0f, 0.0f); glVertex2i(xpos+width, ypos+width);
		    glTexCoord2f(1.0f, 1.0f); glVertex2i(xpos+width, ypos);
			glEnd();
			glPopMatrix();
			break;
	}

}

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

void waiterBurger()
{
	waiter = ppm6GetImage("waiterholdingburger.ppm");
	glGenTextures(1, &waiterTexture);
	glBindTexture(GL_TEXTURE_2D, waiterTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    waiter->width, waiter->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, waiter->data);
    return;
}

void waiterHotdog()
{
	waiter = ppm6GetImage("waiterholdinghotdog.ppm");
	glGenTextures(1, &waiterTexture);
	glBindTexture(GL_TEXTURE_2D, waiterTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    waiter->width, waiter->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, waiter->data);
    return;
}

void waiterPizza()
{
	waiter = ppm6GetImage("waiterholdingpizza.ppm");
	glGenTextures(1, &waiterTexture);
	glBindTexture(GL_TEXTURE_2D, waiterTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    waiter->width, waiter->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, waiter->data);
    return;
}
Player::Player(int y, int x)
{
	xpos = x;
	ypos = y;
}
void Player::moveLeft()
{
	if (xpos - STEP_SIZE < XMIN)
		return;
	xpos = xpos - STEP_SIZE;
}
void Player::moveRight()
{
	if (xpos + STEP_SIZE >= XMAX)
		return;
	xpos = xpos + STEP_SIZE;
}
void Player::moveUp()
{
	if (ypos + STEP_SIZE >= YMAX)
		return;
	ypos = ypos + STEP_SIZE;
}
void Player::moveDown()
{
	if (ypos - STEP_SIZE < YMIN)
		return;
	ypos = ypos - STEP_SIZE;
}
int Player::xPos()
{
	return xpos;
}
int Player::yPos()
{
	return ypos;
}

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
		burgeronplateonside.png burgeronplateonside.ppm \
		burgerontable.png burgeronside.ppm \
		hotdogonplateonside.png hotdogonplateonside.ppm \
		hotdogontable.png hotdogontable.ppm \
		pizzaonplateonside.png pizzaonplateonside.ppm \
		pizzaontable.png pizzaontable.ppm \
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
		9.png 9.ppm \
        waiterholdingburger.png waiterholdingburger.ppm \
        waiterholdinghotdog.png waiterholdinghotdog.ppm \
        waiterholdingpizza.png waiterholdingpizza.ppm ");
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
	system("cp pixel-sprites/burgerontable.png .");
	system("cp pixel-sprites/hotdogonplateonside.png .");
	system("cp pixel-sprites/hotdogontable.png .");
	system("cp pixel-sprites/pizzaonplateonside.png .");
	system("cp pixel-sprites/pizzaontable.png .");
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
    system("cp pixel-sprites/waiterholdingburger.png .");
    system("cp pixel-sprites/waiterholdinghotdog.png .");
    system("cp pixel-sprites/waiterholdingpizza.png .");
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
	system("convert burgerontable.png burgerontable.ppm");
	system("convert pizzaonplateonside.png pizzaonplateonside.ppm");
	system("convert pizzaontable.png pizzaontable.ppm");
	system("convert hotdogontable.png hotdogontable.ppm");
	system("convert hotdogonplateonside.png hotdogonplateonside.ppm");
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
    system("convert waiterholdingburger.png waiterholdingburger.ppm");
    system("convert waiterholdinghotdog.png waiterholdinghotdog.ppm");
    system("convert waiterholdingpizza.png waiterholdingpizza.ppm");
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
		burgerontable.png burgerontable.ppm \
		hotdogonplateonside.png hotdogonplateonside.ppm \
		hotdogontable.png hotdogontable.ppm \
		pizzaonplateonside.png pizzaonplateonside.ppm \
		pizzaontable.png pizzaontable.ppm \
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
		9.png 9.ppm \
        waiterholdingburger.png waiterholdingburger.ppm \
        waiterholdinghotdog.png waiterholdinghotdog.ppm \
        waiterholdingpizza.png waiterholdingpizza.ppm");
	cout << "\n*** Image clean up complete. ***\n\n";

	return;
}

// *** NO LONGER BEING USED, LEFT IN FOR PRESENTATION ***
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
//==============================================================================
