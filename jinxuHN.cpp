//Jinxu Han
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
#include "jinxuHN.h"
#include <time.h>
using namespace std;

Box::Box() {
    xPos1 = 100;
    xPos2 = 100;
    yPos1 = 100;
    yPos2 = 100;
}

void Box::makebox(int x1, int x2, int y1, int y2)
{

    xPos1=x1;
    xPos2=x2;
    yPos1=y1;
    yPos2=y2;
    glTexCoord2f(0.0f, 1.0f); glVertex2i(xPos1, yPos1);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(xPos1, yPos2);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xPos2, yPos2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos2, yPos1);
}

void Box::drawtable(int x1, int x2, int y1, int y2)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, customerStandingTexture1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(x2, y1);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(x2, y2);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(x1, y2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1);
    glEnd();
    glPopMatrix();


}

void Box::gettable()
{
    for (int i; i<4; i++)
    {
	switch (i) {
	    case 0:
		makebox(3, 98, 253, 348);
		drawtable(3, 98, 253, 348);
		break;
	    case 1:
		makebox(669, 764, 253, 348);
		drawtable(3, 98, 253, 348);
		break;
	    case 2:
		makebox(3, 98, 49, 144);
		drawtable(3, 98, 253, 348);
		break;
	    case 3:
		makebox(669, 764, 49, 144);
		drawtable(3, 98, 253, 348);
		break;

	}
    }
}

