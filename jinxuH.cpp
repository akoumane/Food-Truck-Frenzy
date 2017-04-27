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
#include "jinxuH.h"
#include <time.h>
using namespace std;
Box::Box() {
    xPos1 = 100;
    xPos2 = 100;
    yPos1 = 100;
    yPos2 = 100;
}

void Box::gettableposition(int x1, int x2, int y1, int y2)
{
    for(int i =0; i < 4; i++)
    {
	tablexpos1[i]=x1;
	tablexpos2[i]=x2;
	tableypos1[i]=y1;
	tableypos2[i]=y2;
	gettx1();
	gettx2();
	getty1();
	getty2();
    }
}

void Box::getstableposition(int x1, int x2, int y1, int y2)
{
    for(int i =0; i < 2; i++)
    {
	stablexpos1[i]=x1;
	stablexpos2[i]=x2;
	stableypos1[i]=y1;
	stableypos2[i]=y2;
	getstx1();
	getstx2();
	getsty1();
	getsty2();
    }

}

void Box::getwposition(int x1, int y1)
{
    wxpos1=x1;
    //    wxpos2=x2;
    wypos1=y1;
    //    wypos2=y2;
    getwx1();
    // getwx2();
    getwy1();
    // getwy2();

}

void Box::makebox(int x1, int x2, int y1, int y2)
{
    //Position.p;
    xPos1=x1;
    xPos2=x2;
    yPos1=y1;
    yPos2=y2;
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos1, yPos1);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos1, yPos2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos2, yPos2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos2, yPos1);
    gettableposition(xPos1, xPos2, yPos1, yPos2);
}


void Box::makewaiter(int x1, int y1)
{
    //Position.p;
    xPos1=x1;
    //xPos2=x2;
    yPos1=y1;
    //yPos2=y2;
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1+95);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1+95, y1+95);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1+95, y1);
    //glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos1, yPos1);
    //glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos1, yPos2);
    //glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos2, yPos2);
    //glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos2, yPos1);
    // gettableposition(xPos1, xPos2, yPos1, yPos2);
}
void Box::drawtable(int x1, int x2, int y1, int y2)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, customerStandingTexture1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x2, y1);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x2, y2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1);
    glEnd();
    glPopMatrix();


}
void Box::drawwaiter(int x1, int y1)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, customerStandingTexture1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1+95);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1+95, y1+95);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1+95, y1);
    glEnd();
    glPopMatrix();
}
void Box::gettable()
{
    //draw table
    for (int i=0; i<4; i++)
    {
	switch (i) 
	{
	    case 0:
		makebox(13, 225, 225, 370);
		drawtable(13, 225,225, 370);
		break;
	    case 1:
		makebox(536, 754, 224, 370);
		drawtable(536, 754, 224, 370);
		break;
	    case 2:
		makebox(13, 225, 25, 170);
		drawtable(13, 225, 25, 170);
		break;
	    case 3:
		makebox(536, 754, 24, 170);
		drawtable(536, 754, 24, 170);
		break;

	}
    }

    //showItem();
    //draw side table
    makebox(467, 584, 533, 623);
    drawtable(467, 584, 533, 623);
    makebox(585, 705, 533, 623);
    drawtable(585, 705, 533, 623);

    //draw waiter
    makewaiter(253, 4);
    drawwaiter(253, 2453);
}

bool Box::colwithtable()
{
    bool col=false;
    int wxpos2=wxpos1+95;
    int wypos2=wxpos2+95;
    for (int i=0; i<4; i++)
    {
	if(wxpos1 >= tablexpos1[i] && wxpos2 <= tablexpos2[i] &&
		wypos1 >= tableypos1[i] && wypos2 <= tableypos2[i])
	{
	    return true;
	}

    }
    return col;
}

bool Box::colwithstable()
{
    int wxpos2=wxpos1+95;
    int wypos2=wxpos2+95;
    bool col=false;
    for(int i=0; i<4;i++)
	if(wxpos1 >= stablexpos1[i] && wxpos2 <= stablexpos2[i] &&
		wypos1 >= stableypos1[i] && wypos2 <= stableypos2[i])
	{
	    return true;
	}
    return col;
}
void Box::movewup()
{
    wxpos1 = wxpos1-5;
}
void Box::movewdown()
{
    wxpos1 = wxpos1+5;
}
void Box::movewleft()
{
    wypos1 = wypos1-5;
}
void Box::movewright()
{
    wypos1 = wypos1+5;
}


/*#ifdef RENDERTEST
  void Box::showItem()
  {
  for (int i=0; i<4; i++)
  {
  switch (i) 
  {
  case 0:
  drawtable(13, 225,225, 370);
  break;
  case 1:
  drawtable(536, 754, 224, 370);
  break;
  case 2:
  drawtable(13, 225, 25, 170);
  break;
  case 3:
  drawtable(536, 754, 24, 170);
  break;

  }
  }
  }
//#endif
*/

