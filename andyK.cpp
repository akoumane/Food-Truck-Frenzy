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
#include "andyK.h"
#include <time.h>
using namespace std;

Ppmimage *customer1 = NULL;
Ppmimage *customer2 = NULL;
Ppmimage *customer3 = NULL;
Ppmimage *customer4 = NULL;

Ppmimage *customer1Sitting = NULL;
Ppmimage *customer2Sitting = NULL;
Ppmimage *customer3Sitting = NULL;
Ppmimage *customer4Sitting = NULL;

Ppmimage *zero = NULL;
Ppmimage *one = NULL;
Ppmimage *two = NULL;
Ppmimage *three = NULL;
Ppmimage *four = NULL;
Ppmimage *five = NULL;
Ppmimage *six = NULL;
Ppmimage *seven = NULL;
Ppmimage *eight = NULL;
Ppmimage *nine = NULL;

Ppmimage *thoughtbox = NULL;

GLuint customer1Texture;
GLuint customer2Texture;
GLuint customer3Texture;
GLuint customer4Texture;

GLuint customer1SittingTexture;
GLuint customer2SittingTexture;
GLuint customer3SittingTexture;
GLuint customer4SittingTexture;

GLuint zeroTexture;
GLuint oneTexture;
GLuint twoTexture;
GLuint threeTexture;
GLuint fourTexture;
GLuint fiveTexture;
GLuint sixTexture;
GLuint sevenTexture;
GLuint eightTexture;
GLuint nineTexture;

GLuint thoughtboxTexture;

void makeCustomers()
{
	unsigned char col[] = {0, 255, 0};

	customer1 = ppm6GetImage("customer1.ppm");
	customer2 = ppm6GetImage("customer2.ppm");
	customer3 = ppm6GetImage("customer3.ppm");
	customer4 = ppm6GetImage("customer4.ppm");
	glGenTextures(1, &customer1Texture);
	glGenTextures(1, &customer2Texture);
	glGenTextures(1, &customer3Texture);
	glGenTextures(1, &customer4Texture);

	customer1Sitting = ppm6GetImage("customer1sitting.ppm");
	customer2Sitting = ppm6GetImage("customer2sitting.ppm");
	customer3Sitting = ppm6GetImage("customer3sitting.ppm");
	customer4Sitting = ppm6GetImage("customer4sitting.ppm");
	glGenTextures(1, &customer1SittingTexture);
	glGenTextures(1, &customer2SittingTexture);
	glGenTextures(1, &customer3SittingTexture);
	glGenTextures(1, &customer4SittingTexture);

	thoughtbox = ppm6GetImage("thoughtbox.ppm");
	glGenTextures(1, &thoughtboxTexture);

	//customer1
	glBindTexture(GL_TEXTURE_2D, customer1Texture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *customer1Data = buildAlphaData2(customer1, col);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		customer1->width, customer1->height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, customer1Data);
	free(customer1Data);
	//customer2
	glBindTexture(GL_TEXTURE_2D, customer2Texture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *customer2Data = buildAlphaData2(customer2, col);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		customer2->width, customer2->height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, customer2Data);
	free(customer2Data);
	//customer3
	glBindTexture(GL_TEXTURE_2D, customer3Texture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *customer3Data = buildAlphaData2(customer3, col);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		customer3->width, customer3->height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, customer3Data);
	free(customer3Data);
	//customer4
	glBindTexture(GL_TEXTURE_2D, customer4Texture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *customer4Data = buildAlphaData2(customer4, col);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		customer4->width, customer4->height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, customer4Data);
	free(customer4Data);

	//customer1sitting
	glBindTexture(GL_TEXTURE_2D, customer1SittingTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		customer1Sitting->width, customer1Sitting->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, customer1Sitting->data);

	//customer2sitting
	glBindTexture(GL_TEXTURE_2D, customer2SittingTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		customer2Sitting->width, customer2Sitting->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, customer2Sitting->data);

	//customer3sitting
	glBindTexture(GL_TEXTURE_2D, customer3SittingTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		customer3Sitting->width, customer3Sitting->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, customer3Sitting->data);

	//customer4sitting
	glBindTexture(GL_TEXTURE_2D, customer4SittingTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		customer4Sitting->width, customer4Sitting->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, customer4Sitting->data);

	//thoughtbox
	glBindTexture(GL_TEXTURE_2D, thoughtboxTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *thoughtboxData = buildAlphaData2(thoughtbox, col);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		thoughtbox->width, thoughtbox->height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, thoughtboxData);
	free(thoughtboxData);
}

#ifdef RENDERTEST
void renderCustomers()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, customer1Texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(74, 498);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(74, 594);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(170, 594);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(170, 498);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, customer1Texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(4, 253);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(4, 347);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(98, 347);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(98, 253);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, customer2Texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(526, 253);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(526, 347);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(620, 347);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(620, 253);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, customer3Texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(4, 48);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(4, 142);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(98, 142);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(98, 48);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, customer4Texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(526, 48);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(526, 142);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(620, 142);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(620, 48);
	glEnd();
	glPopMatrix();
}
#endif

void makeNumbers()
{
	zero = ppm6GetImage("0.ppm");
	one = ppm6GetImage("1.ppm");
	two = ppm6GetImage("2.ppm");
	three = ppm6GetImage("3.ppm");
	four = ppm6GetImage("4.ppm");
	five = ppm6GetImage("5.ppm");
	six = ppm6GetImage("6.ppm");
	seven = ppm6GetImage("7.ppm");
	eight = ppm6GetImage("8.ppm");
	nine = ppm6GetImage("9.ppm");

	glGenTextures(1, &zeroTexture);
	glGenTextures(1, &oneTexture);
	glGenTextures(1, &twoTexture);
	glGenTextures(1, &threeTexture);
	glGenTextures(1, &fourTexture);
	glGenTextures(1, &fiveTexture);
	glGenTextures(1, &sixTexture);
	glGenTextures(1, &sevenTexture);
	glGenTextures(1, &eightTexture);
	glGenTextures(1, &nineTexture);

	//0
	glBindTexture(GL_TEXTURE_2D, zeroTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		zero->width, zero->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, zero->data);

	//1
	glBindTexture(GL_TEXTURE_2D, oneTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		one->width, one->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, one->data);

	//2
	glBindTexture(GL_TEXTURE_2D, twoTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		two->width, two->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, two->data);

	//3
	glBindTexture(GL_TEXTURE_2D, threeTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		three->width, three->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, three->data);

	//4
	glBindTexture(GL_TEXTURE_2D, fourTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		four->width, four->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, four->data);
	
	//5
	glBindTexture(GL_TEXTURE_2D, fiveTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		five->width, five->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, five->data);

	//6
	glBindTexture(GL_TEXTURE_2D, sixTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		six->width, six->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, six->data);

	//7
	glBindTexture(GL_TEXTURE_2D, sevenTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		seven->width, seven->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, seven->data);

	//8
	glBindTexture(GL_TEXTURE_2D, eightTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		eight->width, eight->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, eight->data);

	//9
	glBindTexture(GL_TEXTURE_2D, nineTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		nine->width, nine->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, nine->data);
}

unsigned char *buildAlphaData2(Ppmimage *img, unsigned char col[3])
{
	//col - color that should be transparent
	//add 4th component to RGB stream...
	int i;
	int a,b,c;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->width * img->height * 4);
	ptr = newdata;
	for (i=0; i<img->width * img->height * 3; i+=3) {
		a = *(data+0);
		b = *(data+1);
		c = *(data+2);
		*(ptr+0) = a;
		*(ptr+1) = b;
		*(ptr+2) = c;
		//continue to use glEnable(GL_ALPHA_TEST);
		//andglAlphaFunc(GL_GREATER, 0.0f);i
		*(ptr+3) = 1;
		if (a == col[0] && b == col[1] && c == col[2])
			*(ptr+3) = 0;

		ptr += 4;
		data += 3;
	}
	return newdata;
}

Customer::Customer()
{
	xPos1 = 74;
	xPos2 = 170;
	yPos1 = 498;
	yPos2 = 594;
	pauseTotal = 0;
	foodChoice = rand() % 4 + 1;
	modelNum = (rand() % 1000) % 4 + 1;
	seatNum = 1;
	inLine = false;
	inSeat = false;
	hasFood = false;
	isEating = false;
	finishFood = false;
	leave = true;
	assignSeat = true;
	startTimer = false;
	moveToSeat = false;
}

void Customer::reset()
{
	xPos1 = 74;
	xPos2 = 170;
	yPos1 = 498;
	yPos2 = 594;
	pauseTotal = 0;
	foodChoice = rand() % 4 + 1;
	modelNum = (rand() % 1000 + 1) % 4 + 1;
	seatNum = 1;
	inLine = false;
	inSeat = false;
	hasFood = false;
	isEating = false;
	finishFood = false;
	leave = true;
	assignSeat = true;
	startTimer = false;
	moveToSeat = false;
}

void Customer::setInLine(bool a)
{
	inLine = a;
}

void Customer::setInSeat (bool a)
{
	inSeat = a;
}

void Customer::setHasFood (bool a)
{
	hasFood = a;
}

void Customer::setIsEating (bool a)
{
	isEating = a;
}

void Customer::setFinishFood (bool a)
{
	finishFood = a;
}

void Customer::addPauseTotal(double a)
{
	if (inLine == true || inSeat == true)
	pauseTotal += a;
}

void Customer::renderModel(bool &line, bool seat[], int &count)
{
	if (inSeat == false && inLine == false) {
		if (!line) {
			inLine = true;
			line = true;
			leave = false;
			clock_gettime(CLOCK_REALTIME, &custStart);
			clock_gettime(CLOCK_REALTIME, &custCurrent);
			startTime = (double)custStart.tv_sec;
			currentTime = (double)custCurrent.tv_sec;
		}
	}


	waitTime = currentTime - startTime - pauseTotal;

	//if (inLine == true)
	//cout << waitTime << endl;



	if (leave == false) {
		if (inLine) {
			line = true;
			finishFood = false;
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);

			switch(modelNum) {
				case 1:
					glBindTexture(GL_TEXTURE_2D, customer1Texture);
					break;
				case 2:
					glBindTexture(GL_TEXTURE_2D, customer2Texture);
					break;
				case 3:
					glBindTexture(GL_TEXTURE_2D, customer3Texture);
					break;
				case 4:
					glBindTexture(GL_TEXTURE_2D, customer4Texture);
					break;
			}

			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.0f);
			glColor4ub(255,255,255,255);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(xPos2, yPos1);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(xPos2, yPos2);
			glTexCoord2f(1.0f, 0.0f); glVertex2i(xPos1, yPos2);
			glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos1, yPos1);
			glEnd();
			glPopMatrix();
		}


		if (waitTime < 5.0) {
			clock_gettime(CLOCK_REALTIME, &custCurrent);
			currentTime = (double)custCurrent.tv_sec;
		}
		else {
			if (assignSeat) {
				if (seat[seatNum-1] == false) {
					seat[seatNum-1] = true;
					assignSeat = false;
				}
				else {
					seatNum++;
					if (seatNum > 4)
						seatNum = 1;
				}
			}
			if (assignSeat == false && seat[seatNum-1] == true) {
				inLine = false;
				if (moveToSeat == false) {
					moveToSeat = true;
					line = false;
				}
				inSeat = true;
			}
		}

		if (inSeat) {
			//glDisable(GL_TEXTURE_2D);
			renderThoughtBox();
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);

			switch(modelNum) {
				case 1:
					glBindTexture(GL_TEXTURE_2D, customer1SittingTexture);
					break;
				case 2:
					glBindTexture(GL_TEXTURE_2D, customer2SittingTexture);
					break;
				case 3:
					glBindTexture(GL_TEXTURE_2D, customer3SittingTexture);
					break;
				case 4:
					glBindTexture(GL_TEXTURE_2D, customer4SittingTexture);
					break;
			}

			glBegin(GL_QUADS);

			switch(seatNum) {
				case 1:
					xPos1 = 3;
					xPos2 = 98;
					yPos1 = 253;
					yPos2 = 348;
					glTexCoord2f(0.0f, 1.0f); glVertex2i(xPos1, yPos1);
					glTexCoord2f(0.0f, 0.0f); glVertex2i(xPos1, yPos2);
					glTexCoord2f(1.0f, 0.0f); glVertex2i(xPos2, yPos2);
					glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos2, yPos1);
					break;
				case 2:
					xPos1 = 669;
					xPos2 = 764;
					yPos1 = 253;
					yPos2 = 348;
					glTexCoord2f(0.0f, 1.0f); glVertex2i(xPos2, yPos1);
					glTexCoord2f(0.0f, 0.0f); glVertex2i(xPos2, yPos2);
					glTexCoord2f(1.0f, 0.0f); glVertex2i(xPos1, yPos2);
					glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos1, yPos1);
					break;
				case 3:
					xPos1 = 3;
					xPos2 = 98;
					yPos1 = 49;
					yPos2 = 144;
					glTexCoord2f(0.0f, 1.0f); glVertex2i(xPos1, yPos1);
					glTexCoord2f(0.0f, 0.0f); glVertex2i(xPos1, yPos2);
					glTexCoord2f(1.0f, 0.0f); glVertex2i(xPos2, yPos2);
					glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos2, yPos1);
					break;
				case 4:
					xPos1 = 669;
					xPos2 = 764;
					yPos1 = 49;
					yPos2 = 144;
					glTexCoord2f(0.0f, 1.0f); glVertex2i(xPos2, yPos1);
					glTexCoord2f(0.0f, 0.0f); glVertex2i(xPos2, yPos2);
					glTexCoord2f(1.0f, 0.0f); glVertex2i(xPos1, yPos2);
					glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos1, yPos1);
					break;
			}

			if (hasFood == true) {
				clock_gettime(CLOCK_REALTIME, &custStart);
				clock_gettime(CLOCK_REALTIME, &custCurrent);
				startTime = (double)custStart.tv_sec;
				currentTime = (double)custCurrent.tv_sec;
				pauseTotal = 0;
				hasFood = false;
				isEating = true;
			}

			if (isEating == true) {
				if (waitTime < 5.5) {
					clock_gettime(CLOCK_REALTIME, &custCurrent);
					currentTime = (double)custCurrent.tv_sec;
				}
				else
					finishFood = true;
			}

			if (finishFood) {
				count++;
				seat[seatNum-1] = false;
				reset();
				leave = true;
			}

			glEnd();
			glPopMatrix();
		}
	}
}

void Customer::renderThoughtBox()
{
	if (isEating == false) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, thoughtboxTexture);

		glBegin(GL_QUADS);

		switch(seatNum) {
			case 1:
				glTexCoord2f(0.0f, 1.0f); glVertex2i(216, 355);
				glTexCoord2f(0.0f, 0.0f); glVertex2i(216, 418);
				glTexCoord2f(1.0f, 0.0f); glVertex2i(279, 418);
				glTexCoord2f(1.0f, 1.0f); glVertex2i(279, 355);
				break;
			case 2:
				glTexCoord2f(0.0f, 1.0f); glVertex2i(488, 355);
				glTexCoord2f(0.0f, 0.0f); glVertex2i(488, 418);
				glTexCoord2f(1.0f, 0.0f); glVertex2i(551, 418);
				glTexCoord2f(1.0f, 1.0f); glVertex2i(551, 355);
				break;
			case 3:
				glTexCoord2f(0.0f, 1.0f); glVertex2i(216, 151);
				glTexCoord2f(0.0f, 0.0f); glVertex2i(216, 214);
				glTexCoord2f(1.0f, 0.0f); glVertex2i(279, 214);
				glTexCoord2f(1.0f, 1.0f); glVertex2i(279, 151);
				break;
			case 4:
				glTexCoord2f(0.0f, 1.0f); glVertex2i(488, 151);
				glTexCoord2f(0.0f, 0.0f); glVertex2i(488, 214);
				glTexCoord2f(1.0f, 0.0f); glVertex2i(551, 214);
				glTexCoord2f(1.0f, 1.0f); glVertex2i(551, 151);
				break;
		}

		glEnd();
		glPopMatrix();
	}
}

int Customer::returnSeat()
{
	return seatNum;
}

int Customer::returnFood()
{
	return foodChoice;
}

Level::Level()
{
	custCount = 15;
	gameLength = 999;
	customers = new Customer[5];
	startPauseTimer = true;
	startCountdownTimer = true;
	addTime = false;
	complete = false;
	gameOver = false;
	win = false;
}

Customer Level::getCustomer(int n)
{
	return customers[n];
}

void Level::makeNewLevel(int n)
{
	levelNum = n;
	custMultiplier = n;
	customerGoal = custMultiplier * custCount;
	start = false;
	complete = false;

	serveCount = 0;

	lineOccupied = false;

	for (int i = 0; i < 4; i++)
		seatOccupied[i] = false;
}

void Level::startGame()
{
	renderCountdown();
	renderServeCounter();
	renderCustomers();
}

void Level::setCustomerLeave(int n)
{
	customers[n].setFinishFood(true);
}

void Level::renderCustomers()
{
	for (int i = 0; i < 5; i++)
		customers[i].renderModel(lineOccupied, seatOccupied, serveCount);

	//customers[0].renderModel(lineOccupied, seatOccupied);
}

void Level::printLine()
{
	cout << lineOccupied << endl;
}

void Level::printSeat()
{
	cout << seatOccupied[0];
	cout << seatOccupied[1];
	cout << seatOccupied[2];
	cout << seatOccupied[3];

	cout << endl;
}

void Level::setStartTimer(bool a)
{
	startPauseTimer = a;
}

void Level::addPauseTotal()
{
	startPauseTimer = true;

	if (addTime == true) {
		pauseTotal += pauseWaitTime;

		for (int i = 0; i < 5; i++) 
			customers[i].addPauseTotal(pauseWaitTime);

		addTime = false;
	}

	//cout << pauseTotal << endl;
}

void Level::calcPauseTime()
{
	if (startPauseTimer == true) {
		clock_gettime(CLOCK_REALTIME, &pauseStart);
		pauseStartTime = (double)pauseStart.tv_sec;

		startPauseTimer = false;
	}

	clock_gettime(CLOCK_REALTIME, &pauseEnd);
	pauseEndTime = (double)pauseEnd.tv_sec;

	pauseWaitTime = pauseEndTime - pauseStartTime;
	//cout << pauseWaitTime << endl;
	addTime = true;
}

void Level::renderCountdown()
{
	int countdown;
	double length;

	if (startCountdownTimer == true){
		clock_gettime(CLOCK_REALTIME, &countdownStart);
		countdownStartTime = (double)countdownStart.tv_sec;

		startCountdownTimer = false;
	}

	clock_gettime(CLOCK_REALTIME, &countdownEnd);
	countdownEndTime = (double)countdownEnd.tv_sec;

	length = countdownEndTime - countdownStartTime - pauseTotal;
	countdown = gameLength - length;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	switch(countdown % 10) {
		case 0:
			glBindTexture(GL_TEXTURE_2D, zeroTexture);
			break;
		case 1:
			glBindTexture(GL_TEXTURE_2D, oneTexture);
			break;
		case 2:
			glBindTexture(GL_TEXTURE_2D, twoTexture);
			break;
		case 3:
			glBindTexture(GL_TEXTURE_2D, threeTexture);
			break;
		case 4:
			glBindTexture(GL_TEXTURE_2D, fourTexture);
			break;
		case 5:
			glBindTexture(GL_TEXTURE_2D, fiveTexture);
			break;
		case 6:
			glBindTexture(GL_TEXTURE_2D, sixTexture);
			break;
		case 7:
			glBindTexture(GL_TEXTURE_2D, sevenTexture);
			break;
		case 8:
			glBindTexture(GL_TEXTURE_2D, eightTexture);
			break;
		case 9:
			glBindTexture(GL_TEXTURE_2D, nineTexture);
			break;
	}

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(432, 673);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(432, 768);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(527, 768);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(527, 673);
	glEnd();
	glPopMatrix();

	if (countdown > 9 ) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		if ((countdown % 100) < 10)
			glBindTexture(GL_TEXTURE_2D, zeroTexture);
		else {
			switch((countdown % 100) - (countdown % 10)) {
				case 10:
					glBindTexture(GL_TEXTURE_2D, oneTexture);
					break;
				case 20:
					glBindTexture(GL_TEXTURE_2D, twoTexture);
					break;
				case 30:
					glBindTexture(GL_TEXTURE_2D, threeTexture);
					break;
				case 40:
					glBindTexture(GL_TEXTURE_2D, fourTexture);
					break;
				case 50:
					glBindTexture(GL_TEXTURE_2D, fiveTexture);
					break;
				case 60:
					glBindTexture(GL_TEXTURE_2D, sixTexture);
					break;
				case 70:
					glBindTexture(GL_TEXTURE_2D, sevenTexture);
					break;
				case 80:
					glBindTexture(GL_TEXTURE_2D, eightTexture);
					break;
				case 90:
					glBindTexture(GL_TEXTURE_2D, nineTexture);
					break;
			}
		}

	}
	else
		glBindTexture(GL_TEXTURE_2D, zeroTexture);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(336, 673);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(336, 768);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(431, 768);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(431, 673);
	glEnd();
	glPopMatrix();

	if (countdown > 99 ) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		if (countdown <= 109 && countdown >= 101)
			glBindTexture(GL_TEXTURE_2D, oneTexture);
		else {
			switch(countdown - (countdown % 100)) {
				case 100:
					glBindTexture(GL_TEXTURE_2D, oneTexture);
					break;
				case 200:
					glBindTexture(GL_TEXTURE_2D, twoTexture);
					break;
				case 300:
					glBindTexture(GL_TEXTURE_2D, threeTexture);
					break;
				case 400:
					glBindTexture(GL_TEXTURE_2D, fourTexture);
					break;
				case 500:
					glBindTexture(GL_TEXTURE_2D, fiveTexture);
					break;
				case 600:
					glBindTexture(GL_TEXTURE_2D, sixTexture);
					break;
				case 700:
					glBindTexture(GL_TEXTURE_2D, sevenTexture);
					break;
				case 800:
					glBindTexture(GL_TEXTURE_2D, eightTexture);
					break;
				case 900:
					glBindTexture(GL_TEXTURE_2D, nineTexture);
					break;
			}
		}

	}
	else {
		glBindTexture(GL_TEXTURE_2D, zeroTexture);
	}

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(240, 673);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(240, 768);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(335, 768);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(335, 673);
	glEnd();
	glPopMatrix();

	if (countdown < 0) {
		start = false;
		complete = true;
	}
}

void Level::renderServeCounter()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	if (serveCount > 9) {
		switch(serveCount - (serveCount % 10)) {
			case 10:
				glBindTexture(GL_TEXTURE_2D, oneTexture);
				break;
			case 20:
				glBindTexture(GL_TEXTURE_2D, twoTexture);
				break;
			case 30:
				glBindTexture(GL_TEXTURE_2D, threeTexture);
				break;
			case 40:
				glBindTexture(GL_TEXTURE_2D, fourTexture);
				break;
			case 50:
				glBindTexture(GL_TEXTURE_2D, fiveTexture);
				break;
			case 60:
				glBindTexture(GL_TEXTURE_2D, sixTexture);
				break;
			case 70:
				glBindTexture(GL_TEXTURE_2D, sevenTexture);
				break;
			case 80:
				glBindTexture(GL_TEXTURE_2D, eightTexture);
				break;
			case 90:
				glBindTexture(GL_TEXTURE_2D, nineTexture);
				break;
		}
	}
	else
		glBindTexture(GL_TEXTURE_2D, zeroTexture);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(701, 736);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(701, 767);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(732, 767);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(732, 736);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	switch(serveCount % 10) {
		case 0:
			glBindTexture(GL_TEXTURE_2D, zeroTexture);
			break;
		case 1:
			glBindTexture(GL_TEXTURE_2D, oneTexture);
			break;
		case 2:
			glBindTexture(GL_TEXTURE_2D, twoTexture);
			break;
		case 3:
			glBindTexture(GL_TEXTURE_2D, threeTexture);
			break;
		case 4:
			glBindTexture(GL_TEXTURE_2D, fourTexture);
			break;
		case 5:
			glBindTexture(GL_TEXTURE_2D, fiveTexture);
			break;
		case 6:
			glBindTexture(GL_TEXTURE_2D, sixTexture);
			break;
		case 7:
			glBindTexture(GL_TEXTURE_2D, sevenTexture);
			break;
		case 8:
			glBindTexture(GL_TEXTURE_2D, eightTexture);
			break;
		case 9:
			glBindTexture(GL_TEXTURE_2D, nineTexture);
			break;
	}

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(732, 736);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(732, 767);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(763, 767);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(763, 736);
	glEnd();
	glPopMatrix();
}

void Level::setHasFood(int n)
{
	customers[n].setHasFood(true);
}

void Level::setComplete(bool a)
{
	complete = a;
}

void Level::setGameOver(bool a)
{
	gameOver = a;
}

void Level::setWin(bool a)
{
	win = a;
}

void Level::startGame(bool a)
{
	start = a;
}

bool Level::checkLine()
{
	return lineOccupied;
}

bool Level::checkTables()
{
	return seatOccupied;
}

bool Level::getStart()
{
	return start;
}

bool Level::getWin()
{
	return win;
}

bool Level::getComplete()
{
	return complete;
}

bool Level::getGameOver()
{
	return gameOver;
}

int Level::getServeCount()
{
	return serveCount;
}

int Level::getCustomerGoal()
{
	return customerGoal;
}

int Level::getSeatNum(int n)
{
	return customers[n].returnSeat();
}

int Level::getFoodId(int n)
{
	return customers[n].returnFood();
}
