//Jinxu Han
/*
The task I have for this project is to make the collision box 
and the collision function between the waiter and the tables.
The way I did the collision function is using the four corner 
instead the mid point
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
//#include "brandonP.h"     *DO NOT REMOVE THIS COMMENT
#include "jinxuH.h"
#include "andyK.h"
#include <time.h>

using namespace std;
#define YUB 384 //Ymax up
#define YDB 0 //Ymax down
#define XRB 668 //xmax left
#define XLB 8 //xmax Right
void renderNumber()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, zeroTexture);
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

}
Box::Box() {
    xPos1 = 100;
    xPos2 = 100;
    yPos1 = 100;
    yPos2 = 100;
    col = false;
    //x1pos for table
    tablexpos1[0]=13;
    tablexpos1[1]=558;
    tablexpos1[2]=13;
    tablexpos1[3]=558;
    //x2pos for table
    tablexpos2[0]=213;
    tablexpos2[1]=754;
    tablexpos2[2]=213;
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
    wxpos1=252;
    wypos1=6;
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

//make the waiter box
void Box::makewaiter(int x1, int y1)
{
    xPos1=x1;
    yPos1=y1;
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1+95);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1+95, y1+95);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(x1+95, y1);
}

//function to draw the table 
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

//function to draw the waiter
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
		makebox(tablexpos1[0], tablexpos2[0], tableypos1[0], tableypos2[0]);
		break;
	    case 1:
		makebox(tablexpos1[1], tablexpos2[1], tableypos1[1], tableypos2[1]);
		//	makebox(536, 754, 224, 370);
		break;
	    case 2:
		makebox(tablexpos1[2], tablexpos2[2], tableypos1[2], tableypos2[2]);
		//	makebox(13, 225, 25, 170);
		break;
	    case 3:
		makebox(tablexpos1[3], tablexpos2[3], tableypos1[3], tableypos2[3]);
		//makebox(536, 754, 24, 170);
		break;

	}
    }

    //drawtablebox
    drawtable(tablexpos1[0], tablexpos2[0],tableypos1[0], tableypos2[0]);
    drawtable(tablexpos1[1], tablexpos2[1],tableypos1[1], tableypos2[1]);
    drawtable(tablexpos1[2], tablexpos2[2],tableypos1[2], tableypos2[2]);
    drawtable(tablexpos1[3], tablexpos2[3],tableypos1[3], tableypos2[3]);
    //drawtable(13, 225,225, 370);
    //drawtable(536, 754, 224, 370);
    //drawtable(13, 225, 25, 170);
    //drawtable(536, 754, 24, 170);
    //make and draw side table
    makebox(stablexpos1[0], stablexpos2[0], stableypos1[0], stableypos2[0]);
    makebox(stablexpos1[0], stablexpos2[0], stableypos1[0], stableypos2[0]);
    //makebox(467, 584, 533, 623);
    //makebox(585, 705, 533, 623);
    drawtable(stablexpos1[0], stablexpos2[0], stableypos1[0], stableypos2[0]);
    drawtable(stablexpos1[1], stablexpos2[1], stableypos1[1], stableypos2[1]);
    //drawtable(467, 584, 533, 623);
    //drawtable(585, 705, 533, 623);
    drawwaiter(wxpos1, wypos1);


}

void Box::getwaiter()
{
    makewaiter(wxpos1, wypos1);
}

//waiter box collision with the right side of the table box
bool Box::colwithRight()
{
    //int wxpos2=wxpos1+95;
	//if the left corners positions are in between the posion right side corner  
	//for the table box then it's true
    int wypos2=wypos1+95;
    for(int i=0; i<4; i++)
    {
	if((wxpos1>=tablexpos1[i]+5 && wxpos1 <= tablexpos2[i]+5)&&
		((wypos1>tableypos1[i] && wypos1 <tableypos2[i])||
		 (wypos2>tableypos1[i] && wypos2 < tableypos2[i])))
	{
	    colR = true;
	    col = true;
	}
    }
    return colR;
}


bool Box::colwithLeft()
{
	//if the right corners positions are in between the posion of left side corner  
	//for the table box then it's true
    int wxpos2=wxpos1+95;
    int wypos2=wypos1+95;
    for(int i=0; i<4;i++)
    {
	if((wxpos2>=tablexpos1[i]-5 && wxpos2 <= tablexpos2[i])&&
		((wypos1>=tableypos1[i] && wypos1 <= tableypos2[i])||
		 (wypos2>=tableypos1[i] && wypos2 <= tableypos2[i])))
	{
	    colL = true;
	    col = true;
	}
    }
    return colL;
}

bool Box::colwithUp()
{
	//if the down corners positions are in between the posion of up side corner  
	//for the table box then it's true
    int wxpos2=wxpos1+95;
    //int wypos2=wypos1+95;
    for(int i=0; i<4; i++)
    {
	if((wypos1>=tableypos1[i] && wypos1<=tableypos2[i]+8) &&
		((wxpos1>tablexpos1[i] && wxpos1<tablexpos2[i])||
		 (wxpos2>tablexpos1[i]&&wxpos2<tablexpos2[i])))
	{
	    colU = true;
	    col = true;
	}
    }
    return colU;
}

bool Box::colwithDown()
{
	//if the up corners positions are in between the posion of down side corner  
	//for the table box then it's true
    int wxpos2=wxpos1+95;
    int wypos2=wypos1+95;
    for(int i=0; i<4; i++)
    {
	if((wypos2>=tableypos1[i] && wypos2<=tableypos2[i]) &&
		((wxpos1>tablexpos1[i] && wxpos1<tablexpos2[i])||
		 (wypos2>tablexpos1[i]&& wxpos2<tablexpos2[i])))
	{
	    colD = true;
	    col = true;
	}
	else
	{ //for sidebox only col down
	    for(int j=0; j<2; j++)
	    {
		if((wypos2>=stableypos1[j] && wypos2<=stableypos2[j]) &&
			((wxpos1>stablexpos1[j] && wxpos1<stablexpos2[j])||
			 (wxpos2>stablexpos1[j]&& wxpos2<stablexpos2[j])))
		{
		    colD = true;
		    col = true;
		}
	    }
	}
    }
    return colD;
}

void Box::movewDown()
{
    //Player *p1;
    if(colwithUp()==true)
    {
	wypos1=wypos1;
    }
    else if (wypos1-6<YDB)
	return;
    else
    {
	wypos1 = wypos1-6;
	//&moveDown();
    }
    colU=false;
}

void Box::movewUp()
{
    //Player *p1;
    if(colwithDown()==true)
    {
	wypos1=wypos1;
    }
    else if (wypos1+6 >=YUB)
	return;
    else
    {
	wypos1 = wypos1+6;
	// &moveUp();
    }
    colD=false;
}

void Box::movewLeft()
{
    //Player *p1;
    if(colwithRight()==true)
    {
	wxpos1=wxpos1;
    }
    else if(wxpos1-6 < XLB)
	return;
    else
    {
	wxpos1 = wxpos1-6;
	//&moveLeft();
    }
    colR=false;
}

void Box::movewRight()
{
    //Player *p1;
    if(colwithLeft()==true)
    {
	wxpos1 = wxpos1;
    }
    else if(wxpos1+6>=XRB)
	return;
    else
    {
	wxpos1 = wxpos1+6;
	// &moveRight();
    }
    colL=false;

}

int setscore(bool inSeat, double waitTime, bool hasFood, bool &getScore)
{
    static int score;
    cout << "Wait Time: "<< waitTime<<endl;
    if (inSeat==true && hasFood==false)
    {
	if(waitTime<=10)
	    score=10;
	else if(waitTime>10 && waitTime<=20)
	    score=5;
	else if(waitTime>20)
	    score=1;
    }
    cout << "score: " << score << endl;
    if(getScore==true)
    {
	getScore=false;
	return score;
    }
    else
    {
	return 0;
    }
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
