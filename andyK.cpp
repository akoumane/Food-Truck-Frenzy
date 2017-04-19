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

Ppmimage *customerStanding1 = NULL;
Ppmimage *customerSitting1 = NULL;
Ppmimage *customerSitting2 = NULL;
Ppmimage *customerSitting3 = NULL;
Ppmimage *customerSitting4 = NULL;
GLuint customerStandingTexture1;
GLuint customerSittingTexture1;
GLuint customerSittingTexture2;
GLuint customerSittingTexture3;
GLuint customerSittingTexture4;

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

void makeCustomers()
{

    customerStanding1 = ppm6GetImage("customer1standing.ppm");
    customerSitting1 = ppm6GetImage("customer1sitting.ppm");
    customerSitting2 = ppm6GetImage("customer2sitting.ppm");
    customerSitting3 = ppm6GetImage("customer3sitting.ppm");
    customerSitting4 = ppm6GetImage("customer4sitting.ppm");
    glGenTextures(1, &customerStandingTexture1);
    glGenTextures(1, &customerSittingTexture1);
    glGenTextures(1, &customerSittingTexture2);
    glGenTextures(1, &customerSittingTexture3);
    glGenTextures(1, &customerSittingTexture4);
    //customer1Standing
    glBindTexture(GL_TEXTURE_2D, customerStandingTexture1);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerStanding1->width, customerStanding1->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerStanding1->data);
    //customer1Sitting
    glBindTexture(GL_TEXTURE_2D, customerSittingTexture1);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerSitting1->width, customerSitting1->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerSitting1->data);
    //customer2Sitting
    glBindTexture(GL_TEXTURE_2D, customerSittingTexture2);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerSitting2->width, customerSitting2->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerSitting2->data);
    //customer3Sitting
    glBindTexture(GL_TEXTURE_2D, customerSittingTexture3);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerSitting3->width, customerSitting3->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerSitting3->data);
    //customer4Sitting
    glBindTexture(GL_TEXTURE_2D, customerSittingTexture4);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerSitting4->width, customerSitting4->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerSitting4->data);
}

void renderCustomers()
{

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, customerStandingTexture1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(74, 498);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(74, 594);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(170, 594);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(170, 498);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, customerSittingTexture1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(4, 253);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(4, 347);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(98, 347);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(98, 253);
    glEnd();
    glPopMatrix();
    
	glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, customerSittingTexture2);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(526, 253);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(526, 347);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(620, 347);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(620, 253);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, customerSittingTexture3);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(4, 48);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(4, 142);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(98, 142);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(98, 48);
    glEnd();
	glPopMatrix();
	
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, customerSittingTexture4);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(526, 48);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(526, 142);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(620, 142);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(620, 48);
    glEnd();
	glPopMatrix();
}

