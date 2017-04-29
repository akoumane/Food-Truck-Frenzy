//Andy Koumane
//andyK.cpp

/**
 * As of 4/19/2017, I've rendered the character models and foods
 * in their appropiate places, leaving them for Jin to added
 * collision boxes for them. Now that I have the base model for the
 * rendering, I will apply them to the appropiate classes made below
 * in order for them to operate with the AI that I plan to program
 * in the near future.
 */

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

Ppmimage *customerStanding1 = NULL;
Ppmimage *customerStanding2 = NULL;
Ppmimage *customerStanding3 = NULL;
Ppmimage *customerStanding4 = NULL;
Ppmimage *customerSitting1 = NULL;
Ppmimage *customerSitting2 = NULL;
Ppmimage *customerSitting3 = NULL;
Ppmimage *customerSitting4 = NULL;

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

GLuint customerStandingTexture1;
GLuint customerStandingTexture2;
GLuint customerStandingTexture3;
GLuint customerStandingTexture4;
GLuint customerSittingTexture1;
GLuint customerSittingTexture2;
GLuint customerSittingTexture3;
GLuint customerSittingTexture4;

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

void Customer::renderModel(bool &line, bool seat[])
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
	//	cout << waitTime << endl;

	

    if (leave == false) {
        if (inLine) {
			line = true;
            finishFood = false;
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);

            switch(modelNum) {
                case 1:
                    glBindTexture(GL_TEXTURE_2D, customerStandingTexture1);
                    break;
                case 2:
                    glBindTexture(GL_TEXTURE_2D, customerStandingTexture2);
                    break;
                case 3:
                    glBindTexture(GL_TEXTURE_2D, customerStandingTexture3);
                    break;
                case 4:
                    glBindTexture(GL_TEXTURE_2D, customerStandingTexture4);
                    break;
            }

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
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);

            switch(modelNum) {
                case 1:
                    glBindTexture(GL_TEXTURE_2D, customerSittingTexture1);
                    break;
                case 2:
                    glBindTexture(GL_TEXTURE_2D, customerSittingTexture2);
                    break;
                case 3:
                    glBindTexture(GL_TEXTURE_2D, customerSittingTexture3);
                    break;
                case 4:
                    glBindTexture(GL_TEXTURE_2D, customerSittingTexture4);
                    break;
				default:
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



            if (finishFood) {
				seat[seatNum-1] = false;
				reset();
                //inLine = true;
				/*glTexCoord2f(0.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f);*/
				glDisable(GL_TEXTURE_2D);
                leave = true;
            }

			glEnd();
            glPopMatrix();
        }
    }

}

Level::Level()
{
	custCount = 30;
	gameLength = 120;
	customers = new Customer[5];
	startPauseTimer = true;
	startCountdownTimer = true;
	addTime = false;
}

void Level::makeNewLevel(int n)
{
	levelNum = n;
	custMultiplier = 0.5 * n;
	customerGoal = (int)custMultiplier * custCount;
	start = false;
	complete = false;

	serveCount = 0;

	lineOccupied = false;

	for (int i = 0; i < 4; i++) {
		seatOccupied[i] = false;
	}


}

void Level::startGame()
{
	renderCountdown();
	renderCustomers();
}

Customer Level::getCustomer(int n)
{
	return customers[n];
}

void Level::setCustomerLeave(int n)
{
	customers[n].setFinishFood(true);
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

void Level::startGame(bool a)
{
	start = a;
}

void Level::renderCustomers()
{
	for (int i = 0; i < 5; i++)
		customers[i].renderModel(lineOccupied, seatOccupied);

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
		for (int i = 0; i < 5; i++) {
			customers[i].addPauseTotal(pauseWaitTime);		
		}
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

	length = countdownEndTime - countdownStartTime;
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

		if (countdown <= 109 && countdown >= 101)
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
	else {
		glBindTexture(GL_TEXTURE_2D, zeroTexture);
	}	
		
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
			switch(countdown - (countdown % 100) - (countdown % 10)) {
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


void makeCustomers()
{

    customerStanding1 = ppm6GetImage("customer1standing.ppm");
    customerStanding2 = ppm6GetImage("customer2standing.ppm");
    customerStanding3 = ppm6GetImage("customer3standing.ppm");
    customerStanding4 = ppm6GetImage("customer4standing.ppm");
    customerSitting1 = ppm6GetImage("customer1sitting.ppm");
    customerSitting2 = ppm6GetImage("customer2sitting.ppm");
    customerSitting3 = ppm6GetImage("customer3sitting.ppm");
    customerSitting4 = ppm6GetImage("customer4sitting.ppm");
    glGenTextures(1, &customerStandingTexture1);
    glGenTextures(1, &customerStandingTexture2);
    glGenTextures(1, &customerStandingTexture3);
    glGenTextures(1, &customerStandingTexture4);
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
    //customer2Standing
    glBindTexture(GL_TEXTURE_2D, customerStandingTexture2);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerStanding2->width, customerStanding2->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerStanding2->data);
    //customer3Standing
    glBindTexture(GL_TEXTURE_2D, customerStandingTexture3);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerStanding3->width, customerStanding3->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerStanding3->data);
    //customer4Standing
    glBindTexture(GL_TEXTURE_2D, customerStandingTexture4);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerStanding4->width, customerStanding4->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerStanding4->data);
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



#ifdef RENDERTEST
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
#endif
