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
    col = false;
    //x1pos for table
    tablexpos1[0]=13;
    tablexpos1[1]=536;
    tablexpos1[2]=13;
    tablexpos1[3]=536;
    //x2pos for table
    tablexpos2[0]=225;
    tablexpos2[1]=754;
    tablexpos2[2]=225;
    tablexpos2[3]=754;
    //y1pos for table
    tableypos1[0]=225;
    tableypos1[1]=225;
    tableypos1[2]=25;
    tableypos1[3]=25;
    //y2pos for table
    tableypos2[0]=370;
    tableypos2[1]=370;
    tableypos2[2]=170;
    tableypos2[3]=170;
    //pos for stable;
    //x1pos for stable
    stablexpos1[0]=467;
    stablexpos1[1]=585;
    //x2pos for stable
    stablexpos2[0]=584;
    stablexpos2[1]=705;
    //y1pos for stable
    stableypos1[0]=533;
    stableypos1[1]=533;
    //y2pos for stable
    stableypos2[0]=623;
    stableypos2[1]=623;
    //start pos for waiter
    wxpos1=253;
    wypos1=4;
}
//make the box
void Box::makebox(int x1, int x2, int y1, int y2)
{
    xPos1=x1;
    xPos2=x2;
    yPos1=y1;
    yPos2=y2;
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos1, yPos1);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos1, yPos2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos2, yPos2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos2, yPos1);
}


void Box::makewaiter(int x1, int y1)
{
    xPos1=x1;
    yPos1=y1;
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1+95);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1+95, y1+95);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1+95, y1);
}
void Box::drawtable(int x1, int x2, int y1, int y2)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
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
		break;
	    case 1:
		makebox(536, 754, 224, 370);
		break;
	    case 2:
		makebox(13, 225, 25, 170);
		break;
	    case 3:
		makebox(536, 754, 24, 170);
		break;

	}
    }

    //drawtablebox
		drawtable(13, 225,225, 370);
		drawtable(536, 754, 224, 370);
		drawtable(13, 225, 25, 170);
		drawtable(536, 754, 24, 170);
    //make and draw side table
    makebox(467, 584, 533, 623);
    makebox(585, 705, 533, 623);
    drawtable(467, 584, 533, 623);
    drawtable(585, 705, 533, 623);
    drawwaiter(wxpos1, wypos1);


}
void Box::getwaiter()
{
    makewaiter(wxpos1, wypos1);
}

bool Box::colwithRight()
{
    //int wxpos2=wxpos1+95;
    int wypos2=wypos1+95;
    for(int i=0; i<4; i++){
	if((wxpos1>tablexpos1[i] && wxpos1 < tablexpos2[i])&&
		((wypos1>tableypos1[i] && wypos1 <tableypos2[i])||
		 (wypos2>tableypos1[i] && wypos2 < tableypos2[i])))
	{
	    colR = true;
	}
    }
    return colR;
}
bool Box::colwithLeft()
{
    int wxpos2=wxpos1+95;
    int wypos2=wypos1+95;
    for(int i=0; i<4;i++)
    {
	if((wxpos2>tablexpos1[i] && wxpos2 < tablexpos2[i])&&
		((wypos1>tableypos1[i] && wypos1 <tableypos2[i])||
		 (wypos2>tableypos1[i] && wypos2 < tableypos2[i])))
	{
	    colL = true;
	}
    }
    return colL;
}
bool Box::colwithUp()
{
    int wxpos2=wxpos1+95;
    //int wypos2=wypos1+95;
    for(int i=0; i<4; i++)
    {
	if((wypos1>tableypos1[i]+5 && wypos1<tableypos2[i]+5) &&
		((wxpos1>tablexpos1[i]+5 && wxpos1<tablexpos2[i]+5)||
		 (wxpos2>tablexpos1[i]+5&&wxpos2<tablexpos2[i]+5))) 
	{
	    colU = true;
	}
    }
    return colU;
}
bool Box::colwithDown()
{
    int wxpos2=wxpos1+95;
    int wypos2=wxpos2+95;
    for(int i=0; i<4; i++)
    {
	if((wypos2>tableypos1[i] && wypos2<tableypos2[i]) &&
		((wxpos1>tablexpos1[i] && wxpos1<tablexpos2[i])||
		 (wxpos2>tablexpos1[i]&& wxpos2<tablexpos2[i]))) 
	{
	    colD = true;
	}
	else  
	{ //for sidebox only col down
	    for(int i=0; i<2; i++)
	    {
		if((wypos2>stableypos1[i] && wypos2<stableypos2[i]) &&
			((wxpos1>stablexpos1[i] && wxpos1<stablexpos2[i])||
			 (wxpos2>stablexpos1[i]&& wxpos2<stablexpos2[i]))) 
		{
		    colD = true;
		}
	    }
	}
    }
    return colD;
}

void Box::movewDown()
{
    if(colwithUp()==true)
    {
	wypos1=wypos1;
    }
    else
	wypos1 = wypos1-5;
    colU=false;
}

void Box::movewUp()
{
    if(colwithDown()==true)
    {
	wypos1=wypos1;
    }
    else
	wypos1 = wypos1+5;
    colD=false;
}

void Box::movewLeft()
{
    if(colwithRight()==true)
    {
	wxpos1=wxpos1;
    }
    else
	wxpos1 = wxpos1-5;
    colR=false;
}

void Box::movewRight()
{
    if(colwithLeft()==true)
    {
	wxpos1 = wxpos1;
    }
    else
	wxpos1 = wxpos1+5;
    
    colL=false;

}


#ifdef RENDERTEST
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
    drawwaiter(253, 4);
    drawwaiter(wxpos1, wypos1);
    drawtable(467, 584, 533, 623);
    drawtable(585, 705, 533, 623);
}
#endif


