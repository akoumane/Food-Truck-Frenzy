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
#include "andyK.h"
#include "brandonP.h"

extern "C" {
#include "fonts.h"
}
using namespace std;

#define YMAX 394
#define XMAX 668
#define YMIN 0
#define XMIN 8
#define STEP_SIZE 6

Table::Table()
{
	for (int i=0; i<6; i++) {
		arr[i] = 0;
	}
	f1 = new Food();
	f2 = new Food();
	f3 = new Food();
	f4 = new Food();
	f5 = new Food();
	f6 = new Food();
}

void interaction(Player *p1, Table *t1, Level *level)
{
	Customer c0 = level->getCustomer(0);
	Customer c1 = level->getCustomer(1);
	Customer c2 = level->getCustomer(2);
	Customer c3 = level->getCustomer(3);
	Customer c4 = level->getCustomer(4);
	Customer c5 = level->getCustomer(5);

	// Table 1
	if (p1->xPos() >= 235 && p1->xPos() <= 241 && p1->yPos() >= 232 &&
		p1->yPos() <=280) {
		
	}
	// Table 2
	if (p1->xPos() >= 427 && p1->xPos() <= 433 && p1->yPos() >= 232 &&
		p1->yPos() <=280) {

	}
	// Table 3
	if (p1->xPos() >= 235 && p1->xPos() <= 241 && p1->yPos() >= 28 &&
		p1->yPos() <=270) {

	}
	// Table 4
	if (p1->xPos() >= 427 && p1->xPos() <= 433 && p1->yPos() >= 28 &&
		p1->yPos() <=70) {

	}
	// Table 5
	if (p1->xPos() >= 367 && p1->xPos() <= 409 && p1->yPos() >= 376 &&
		p1->yPos() <=388) {

	}
	// Table 6
	if (p1->xPos() >= 367 && p1->xPos() <= 409 && p1->yPos() >= 376 &&
		p1->yPos() <=388) {

	}





}

void Food::makeFood()
{
	unsigned char col[] = {0, 255, 0};

    burgeronplate = ppm6GetImage("burgeronplate.ppm");
    glGenTextures(1, &burgeronplate_texture);
    glBindTexture(GL_TEXTURE_2D, burgeronplate_texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *burgeronplateData = buildAlphaData2(burgeronplate, col);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	    burgeronplate->width, burgeronplate->height,
	    0, GL_RGBA, GL_UNSIGNED_BYTE, burgeronplateData);
	free(burgeronplateData);

	hotdogonplate = ppm6GetImage("hotdogonplate.ppm");
	glGenTextures(1, &hotdogonplate_texture);
	glBindTexture(GL_TEXTURE_2D, hotdogonplate_texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *hotdogonplateData = buildAlphaData2(hotdogonplate, col);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		hotdogonplate->width, hotdogonplate->height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, hotdogonplateData);
	free(hotdogonplateData);

	pizzaonplate = ppm6GetImage("pizzaonplate.ppm");
	glGenTextures(1, &pizzaonplate_texture);
	glBindTexture(GL_TEXTURE_2D, pizzaonplate_texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *pizzaonplateData = buildAlphaData2(pizzaonplate, col);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		pizzaonplate->width, pizzaonplate->height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pizzaonplateData);
	free(pizzaonplateData);
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
			ypos = 271;
			break;
		case 2:
			xpos = 580;
			ypos = 271;
			break;
		case 3:
			xpos = 124;
			ypos = 67;
			break;
		case 4:
			xpos = 580;
			ypos = 67;
			break;
		case 5:
			xpos = 415;
			ypos = 490;
			break;
		case 6:
			xpos = 515;
			ypos = 490;
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
				glBindTexture(GL_TEXTURE_2D, burgeronplate_texture);
			//if (on_table)
				//glBindTexture(GL_TEXTURE_2D, burgerontable_texture);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.0f);
			glColor4ub(255,255,255,255);
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
                glBindTexture(GL_TEXTURE_2D, hotdogonplate_texture);
            //if (on_table)
                //glBindTexture(GL_TEXTURE_2D, hotdogontable_texture);
            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(GL_GREATER, 0.0f);
            glColor4ub(255,255,255,255);
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
                glBindTexture(GL_TEXTURE_2D, pizzaonplate_texture);
            //if (on_table)
                //glBindTexture(GL_TEXTURE_2D, pizzaontable_texture);
            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(GL_GREATER, 0.0f);
            glColor4ub(255,255,255,255);
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
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(xpos, ypos);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(xpos, ypos+95);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xpos+95, ypos+95);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xpos+95, ypos);
    glEnd();
    glPopMatrix();
	return;
}

void makeWaiter(int model)
{
	unsigned char col[] = {0, 255, 0};

	if (model == 0) {
		waiter = ppm6GetImage("waiter.ppm");
		glGenTextures(1, &waiterTexture);
		glBindTexture(GL_TEXTURE_2D, waiterTexture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		unsigned char *waiterData = buildAlphaData2(waiter, col);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		    waiter->width, waiter->height,
		    0, GL_RGBA, GL_UNSIGNED_BYTE, waiterData);
		free(waiterData);
	}
	if (model == 1) {
		waiter = ppm6GetImage("waiterholdingburger.ppm");
		glGenTextures(1, &waiterTexture);
		glBindTexture(GL_TEXTURE_2D, waiterTexture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		unsigned char *waiterData = buildAlphaData2(waiter, col);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			waiter->width, waiter->height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, waiterData);
		free(waiterData);
	}
	if (model == 2) {
		waiter = ppm6GetImage("waiterholdinghotdog.ppm");
		glGenTextures(1, &waiterTexture);
		glBindTexture(GL_TEXTURE_2D, waiterTexture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		unsigned char *waiterData = buildAlphaData2(waiter, col);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		    waiter->width, waiter->height,
		    0, GL_RGBA, GL_UNSIGNED_BYTE, waiterData);
		free(waiterData);
	}
	if (model == 3) {
		waiter = ppm6GetImage("waiterholdingpizza.ppm");
		glGenTextures(1, &waiterTexture);
		glBindTexture(GL_TEXTURE_2D, waiterTexture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		unsigned char *waiterData = buildAlphaData2(waiter, col);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		    waiter->width, waiter->height,
		    0, GL_RGBA, GL_UNSIGNED_BYTE, waiterData);
		free(waiterData);
	}
	if (model == 4) {
		waiter = ppm6GetImage("waiterholdingsoda.ppm");
		glGenTextures(1, &waiterTexture);
		glBindTexture(GL_TEXTURE_2D, waiterTexture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		unsigned char *waiterData = buildAlphaData2(waiter, col);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		    waiter->width, waiter->height,
		    0, GL_RGBA, GL_UNSIGNED_BYTE, waiterData);
		free(waiterData);
	}
	return;
}

Player::Player(int y, int x, int choice)
{
	xpos = x;
	ypos = y;
	foodChoice = choice;
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
	cleanUp();
	system("clear");

	// copy images to main folder
	cout << "\n*** Copying images to main folder... ***\n\n";
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
	system("cp pixel-sprites/background.png .");
	system("cp pixel-sprites/burger.png .");
	system("cp pixel-sprites/burgeronplate.png .");
	system("cp pixel-sprites/chair.png .");
	system("cp pixel-sprites/customer1.png .");
	system("cp pixel-sprites/customer1sitting.png .");
	system("cp pixel-sprites/customer2.png .");
	system("cp pixel-sprites/customer2sitting.png .");
	system("cp pixel-sprites/customer3.png .");
	system("cp pixel-sprites/customer3sitting.png .");
	system("cp pixel-sprites/customer4.png .");
	system("cp pixel-sprites/customer4sitting.png .");
	system("cp pixel-sprites/defeat.png .");
	system("cp pixel-sprites/exit.png .");
	system("cp pixel-sprites/foodtruck.png .");
	system("cp pixel-sprites/hotdog.png .");
	system("cp pixel-sprites/hotdogonplate.png .");
	system("cp pixel-sprites/menu.png .");
	system("cp pixel-sprites/menu_credit.png .");
	system("cp pixel-sprites/menu_defeat.png .");
	system("cp pixel-sprites/menu_help.png .");
	system("cp pixel-sprites/menu_level.png .");
	system("cp pixel-sprites/menu_pause.png .");
	system("cp pixel-sprites/menu_victory.png .");
	system("cp pixel-sprites/pizza.png .");
	system("cp pixel-sprites/pizzaonplate.png .");
	system("cp pixel-sprites/plate.png .");
	system("cp pixel-sprites/soda.png .");
	system("cp pixel-sprites/sodaonplate.png .");
	system("cp pixel-sprites/start.png .");
	system("cp pixel-sprites/table.png .");
	system("cp pixel-sprites/thoughtbox.png .");
	system("cp pixel-sprites/waiter.png .");
	system("cp pixel-sprites/waiterholdingburger.png .");
	system("cp pixel-sprites/waiterholdinghotdog.png .");
	system("cp pixel-sprites/waiterholdingpizza.png .");
	system("cp pixel-sprites/waiterholdingsoda.png .");
	cout << "\n*** Copying images complete. ***\n\n";

	// convert from png to ppm using terminal GIMP
	cout << "\n*** Converting .png images to .ppm... ***\n\n";
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
	system("convert background.png background.ppm");
	system("convert burger.png burger.ppm");
	system("convert burgeronplate.png burgeronplate.ppm");
	system("convert chair.png chair.ppm");
	system("convert customer1.png customer1.ppm");
	system("convert customer1sitting.png customer1sitting.ppm");
	system("convert customer2.png customer2.ppm");
	system("convert customer2sitting.png customer2sitting.ppm");
	system("convert customer3.png customer3.ppm");
	system("convert customer3sitting.png customer3sitting.ppm");
	system("convert customer4.png customer4.ppm");
	system("convert customer4sitting.png customer4sitting.ppm");
	system("convert defeat.png defeat.ppm");
	system("convert exit.png exit.ppm");
	system("convert foodtruck.png foodtruck.ppm");
	system("convert hotdog.png hotdog.ppm");
	system("convert hotdogonplate.png hotdogonplate.ppm");
	system("convert menu.png menu.ppm");
	system("convert menu_credit.png menu_credit.ppm");
	system("convert menu_defeat.png menu_defeat.ppm");
	system("convert menu_help.png menu_help.ppm");
	system("convert menu_level.png menu_level.ppm");
	system("convert menu_pause.png menu_pause.ppm");
	system("convert menu_victory.png menu_victory.ppm");
	system("convert pizza.png pizza.ppm");
	system("convert pizzaonplate.png pizzaonplate.ppm");
	system("convert plate.png plate.ppm");
	system("convert soda.png soda.ppm");
	system("convert sodaonplate.png sodaonplate.ppm");
	system("convert start.png start.ppm");
	system("convert table.png table.ppm");
	system("convert thoughtbox.png thoughtbox.ppm");
	system("convert waiter.png waiter.ppm");
	system("convert waiterholdingburger.png waiterholdingburger.ppm");
	system("convert waiterholdinghotdog.png waiterholdinghotdog.ppm");
	system("convert waiterholdingpizza.png waiterholdingpizza.ppm");
	system("convert waiterholdingsoda.png waiterholdingsoda.ppm");

	cout << "\n*** Image conversion complete. ***\n\n";
	return;
}

void cleanUp()
{
	cout << "\n*** Cleaning up images... ***\n\n";
	if (remove("0.png") != 0)
		cout << "ERROR: could not remove '0.png'\n";
	if (remove("0.ppm") != 0)
		cout << "ERROR: could not remove '0.ppm'\n";
	if (remove("1.png") != 0)
		cout << "ERROR: could not remove '1.png'\n";
	if (remove("1.ppm") != 0)
		cout << "ERROR: could not remove '1.ppm'\n";
	if (remove("2.png") != 0)
		cout << "ERROR: could not remove '2.png'\n";
	if (remove("2.ppm") != 0)
		cout << "ERROR: could not remove '2.ppm'\n";
	if (remove("3.png") != 0)
		cout << "ERROR: could not remove '3.png'\n";
	if (remove("3.ppm") != 0)
		cout << "ERROR: could not remove '3.ppm'\n";
	if (remove("4.png") != 0)
		cout << "ERROR: could not remove '4.png'\n";
	if (remove("4.ppm") != 0)
		cout << "ERROR: could not remove '4.ppm'\n";
	if (remove("5.png") != 0)
		cout << "ERROR: could not remove '5.png'\n";
	if (remove("5.ppm") != 0)
		cout << "ERROR: could not remove '5.ppm'\n";
	if (remove("6.png") != 0)
		cout << "ERROR: could not remove '6.png'\n";
	if (remove("6.ppm") != 0)
		cout << "ERROR: could not remove '6.ppm'\n";
	if (remove("7.png") != 0)
		cout << "ERROR: could not remove '7.png'\n";
	if (remove("7.ppm") != 0)
		cout << "ERROR: could not remove '7.ppm'\n";
	if (remove("8.png") != 0)
		cout << "ERROR: could not remove '8.png'\n";
	if (remove("8.ppm") != 0)
		cout << "ERROR: could not remove '8.ppm'\n";
	if (remove("9.png") != 0)
		cout << "ERROR: could not remove '9.png'\n";
	if (remove("9.ppm") != 0)
		cout << "ERROR: could not remove '9.ppm'\n";
	if (remove("background.png") != 0)
		cout << "ERROR: could not remove 'background.png'\n";
	if (remove("background.ppm") != 0)
		cout << "ERROR: could not remove 'background.ppm'\n";
	if (remove("burger.png") != 0)
		cout << "ERROR: could not remove 'burger.png'\n";
	if (remove("burger.ppm") != 0)
		cout << "ERROR: could not remove 'burger.ppm'\n";
	if (remove("burgeronplate.png") != 0)
		cout << "ERROR: could not remove 'burgeronplate.png'\n";
	if (remove("burgeronplate.ppm") != 0)
		cout << "ERROR: could not remove 'burgeronplate.ppm'\n";
	if (remove("chair.png") != 0)
		cout << "ERROR: could not remove 'chair.png'\n";
	if (remove("chair.ppm") != 0)
		cout << "ERROR: could not remove 'chair.ppm'\n";
	if (remove("customer1.png") != 0)
		cout << "ERROR: could not remove 'customer1.png'\n";
	if (remove("customer1.ppm") != 0)
		cout << "ERROR: could not remove 'customer1.ppm'\n";
	if (remove("customer2.png") != 0)
		cout << "ERROR: could not remove 'customer2.png'\n";
	if (remove("customer2.ppm") != 0)
		cout << "ERROR: could not remove 'customer2.ppm'\n";
	if (remove("customer3.png") != 0)
		cout << "ERROR: could not remove 'customer3.png'\n";
	if (remove("customer3.ppm") != 0)
		cout << "ERROR: could not remove 'customer3.ppm'\n";
	if (remove("customer4.png") != 0)
		cout << "ERROR: could not remove 'customer4.png'\n";
	if (remove("customer4.ppm") != 0)
		cout << "ERROR: could not remove 'customer4.ppm'\n";
	if (remove("customer1sitting.png") != 0)
		cout << "ERROR: could not remove 'customer1sitting.png'\n";
	if (remove("customer1sitting.ppm") != 0)
		cout << "ERROR: could not remove 'customer1sitting.ppm'\n";
	if (remove("customer2sitting.png") != 0)
		cout << "ERROR: could not remove 'customer2sitting.png'\n";
	if (remove("customer2sitting.ppm") != 0)
		cout << "ERROR: could not remove 'customer2sitting.ppm'\n";
	if (remove("customer3sitting.png") != 0)
		cout << "ERROR: could not remove 'customer3sitting.png'\n";
	if (remove("customer3sitting.ppm") != 0)
		cout << "ERROR: could not remove 'customer3sitting.ppm'\n";
	if (remove("customer4sitting.png") != 0)
		cout << "ERROR: could not remove 'customer4sitting.png'\n";
	if (remove("customer4sitting.ppm") != 0)
		cout << "ERROR: could not remove 'customer4sitting.ppm'\n";
	if (remove("defeat.png") != 0)
		cout << "ERROR: could not remove 'defeat.png'\n";
	if (remove("defeat.ppm") != 0)
		cout << "ERROR: could not remove 'defeat.ppm'\n";
	if (remove("exit.png") != 0)
		cout << "ERROR: could not remove 'exit.png'\n";
	if (remove("exit.ppm") != 0)
		cout << "ERROR: could not remove 'exit.ppm'\n";
	if (remove("foodtruck.png") != 0)
		cout << "ERROR: could not remove 'foodtruck.png'\n";
	if (remove("foodtruck.ppm") != 0)
		cout << "ERROR: could not remove 'foodtruck.ppm'\n";
	if (remove("hotdog.png") != 0)
		cout << "ERROR: could not remove 'hotdog.png'\n";
	if (remove("hotdog.ppm") != 0)
		cout << "ERROR: could not remove 'hotdog.ppm'\n";
	if (remove("hotdogonplate.png") != 0)
		cout << "ERROR: could not remove 'hotdogonplate.png'\n";
	if (remove("hotdogonplate.ppm") != 0)
		cout << "ERROR: could not remove 'hotdogonplate.ppm'\n";
	if (remove("pizza.png") != 0)
		cout << "ERROR: could not remove 'pizza.png'\n";
	if (remove("pizza.ppm") != 0)
		cout << "ERROR: could not remove 'pizza.ppm'\n";
	if (remove("pizzaonplate.png") != 0)
		cout << "ERROR: could not remove 'pizzaonplate.png'\n";
	if (remove("pizzaonplate.ppm") != 0)
		cout << "ERROR: could not remove 'pizzaonplate.ppm'\n";
	if (remove("soda.png") != 0)
		cout << "ERROR: could not remove 'soda.png'\n";
	if (remove("soda.ppm") != 0)
		cout << "ERROR: could not remove 'soda.ppm'\n";
	if (remove("sodaonplate.png") != 0)
		cout << "ERROR: could not remove 'sodaonplate.png'\n";
	if (remove("sodaonplate.ppm") != 0)
		cout << "ERROR: could not remove 'sodaonplate.ppm'\n";
	if (remove("menu.png") != 0)
		cout << "ERROR: could not remove 'menu.png'\n";
	if (remove("menu.ppm") != 0)
		cout << "ERROR: could not remove 'menu.ppm'\n";
	if (remove("menu_credit.png") != 0)
		cout << "ERROR: could not remove 'menu_credit.png'\n";
	if (remove("menu_credit.ppm") != 0)
		cout << "ERROR: could not remove 'menu_credit.ppm'\n";
	if (remove("menu_defeat.png") != 0)
		cout << "ERROR: could not remove 'menu_defeat.png'\n";
	if (remove("menu_defeat.ppm") != 0)
		cout << "ERROR: could not remove 'menu_defeat.ppm'\n";
	if (remove("menu_help.png") != 0)
		cout << "ERROR: could not remove 'menu_help.png'\n";
	if (remove("menu_help.ppm") != 0)
		cout << "ERROR: could not re	ve 'menu_level.ppm'\n";
	if (remove("menu_pause.png") != 0)
		cout << "ERROR: could not remove 'menu_pause.png'\n";
	if (remove("menu_pause.ppm") != 0)
		cout << "ERROR: could not remove 'menu_pause.ppm'\n";
	if (remove("menu_victory.png") != 0)
		cout << "ERROR: could not remove 'menu_victory.png'\n";
	if (remove("menu_victory.ppm") != 0)
		cout << "ERROR: could not remove 'menu_victory.ppm'\n";
	if (remove("plate.png") != 0)
		cout << "ERROR: could not remove 'plate.png'\n";
	if (remove("plate.ppm") != 0)
		cout << "ERROR: could not remove 'plate.ppm'\n";
	if (remove("start.png") != 0)
		cout << "ERROR: cuold not remove 'start.png'\n";
	if (remove("start.ppm") != 0)
		cout << "ERROR: could not remove 'start.ppm'\n";
	if (remove("table.png") != 0)
		cout << "ERROR: could not remove 'table.png'\n";
	if (remove("table.ppm") != 0)
		cout << "ERROR: could not remove 'table.ppm'\n";
	if (remove("thoughtbox.png") != 0)
		cout << "ERROR: could not remove 'thoughtbox.png'\n";
	if (remove("thoughtbox.ppm") != 0)
		cout << "ERROR: could not rSemove 'thoughtbox.ppm'\n";
	if (remove("waiter.png") != 0)
	 	cout << "ERROR: could not remove 'waiter.png'\n";
	if (remove("waiter.ppm") != 0)
		cout << "ERROR: could not remove 'waiter.ppm'\n";
	if (remove("waiterholdingburger.png") != 0)
		cout << "ERROR: could not remove 'waiterholdingburger.png'\n";
	if (remove("waiterholdingburger.ppm") != 0)
		cout << "ERROR: could not remove 'waiterholdingburger.ppm'\n";
	if (remove("waiterholdinghotdog.png") != 0)
		cout << "ERROR: could not remove 'waiterholdinghotdog.png'\n";
	if (remove("waiterholdinghotdog.ppm") != 0)
		cout << "ERROR: could not remove 'waiterholdinghotdog.ppm'\n";
	if (remove("waiterholdingpizza.png") != 0)
		cout << "ERROR: could not remove 'waiterholdingpizza.png'\n";
	if (remove("waiterholdingpizza.ppm") != 0)
		cout << "ERROR: could not remove 'waiterholdingpizza.png'\n";
	if (remove("waiterholdingsoda.png") != 0)
		cout << "ERROR: could not remove 'waiterholdingsoda.png'\n";
	if (remove("waiterholdingsoda.ppm") != 0)
		cout << "ERROR: coul dnot remove 'waiterholdingsoda.ppm'\n";
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
