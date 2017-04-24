
//Brandon Martinez 
//CMPS 3350 lab5
//
//UPDATES 
//***********************
//Start menu added PRESS A to turn on and off
//temp turned off on start
//more render functions added
//************************
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
#include "brandonM.h"

using namespace std;

Ppmimage *StartMenu = NULL;
GLuint StartMenuTexture1;

Ppmimage *PauseMenu = NULL;
GLuint PauseMenuTexture1;

Ppmimage *HelpMenu = NULL;
GLuint HelpMenuTexture1;

Ppmimage *DefeatMenu = NULL;
GLuint DefeatMenuTexture1;

extern "C" {
#include "fonts.h"
}
struct Vec {
    float x,y,z;
};
struct Shape {
    float width, height;
    float radius;
    Vec center;
};
struct Game {
    Shape box[5];
    int n;
    int mouse[2];
};

unsigned char *Transparent(Ppmimage *img, unsigned char col[3])
{
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
	*(ptr+3) = 1;
	if (	a == col[0] &&
		b == col[1] && 
		c == col[2]) {
	    // * (ptr+3);
	}
	ptr += 4;
	data += 3;
    }
    return newdata;
}

void TitleScreen()
{
    StartMenu = ppm6GetImage("menu.ppm");
    glGenTextures(1, &StartMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, StartMenuTexture1);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    StartMenu->width, StartMenu->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, StartMenu->data);

#ifdef BOXES
    //Boxes to use for menu input
    Game game;
    game.n=0;

    //declare a box shape
    game.box[4].width = 100;
    game.box[4].height = 10;
    game.box[4].center.x = 120 + 5*65;
    game.box[4].center.y = 500 - 5*60;

    game.box[3].width = 100;
    game.box[3].height = 10;
    game.box[3].center.x = 120 + 4*65;
    game.box[3].center.y = 500 - 4*60;

    game.box[2].width = 100;
    game.box[2].height = 10;
    game.box[2].center.x = 120 + 3*65;
    game.box[2].center.y = 500 - 3*60;

    game.box[1].width = 100;
    game.box[1].height = 10;
    game.box[1].center.x = 120 + 2*65;
    game.box[1].center.y = 500 - 2*60;

    game.box[0].width = 100;
    game.box[0].height = 10;
    game.box[0].center.x = 120 + 1*65;
    game.box[0].center.y = 500 - 1*60;

    float w, h;

    for(int i=0; i<=5; i++)
    {
	Shape *s;
	glColor3ub(90,140,90);
	s = game.box[i];
	glPushMatrix();
	glTranslatef(s->center.x, s->center.y, s->center.z);
	w = s->width;
	h = s->height;
	glBegin(GL_QUADS);
	glVertex2i(-w,-h);
	glVertex2i(-w, h);
	glVertex2i( w, h);
	glVertex2i( w,-h);
	glEnd();
	glPopMatrix();
    }
#endif
}

void renderTitleScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, StartMenuTexture1);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(768, 768);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(768, 0);
    glEnd();
    glPopMatrix();
}

void Help_Menu()
{
       StartMenu = ppm6GetImage("menu_help.ppm");
       glGenTextures(1, &HelpMenuTexture1);
       glBindTexture(GL_TEXTURE_2D, HelpMenuTexture1);

       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
       glTexImage2D(GL_TEXTURE_2D, 0, 3,
       HelpMenu->width, HelpMenu->height,
       0, GL_RGB, GL_UNSIGNED_BYTE, HelpMenu->data);
}

void renderHelpScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, HelpMenuTexture1);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(768, 768);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(768, 0);
}

void Defeat_Menu() 
{	
    DefeatMenu = ppm6GetImage("menu_defeat.ppm");
    glGenTextures(1, &DefeatMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, DefeatMenuTexture1);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    DefeatMenu->width, DefeatMenu->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, DefeatMenu->data);

}

void renderDefeatScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, DefeatMenuTexture1);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
}

void Pause_Menu() 
{	
    PauseMenu = ppm6GetImage("menu_pause.ppm");
    glGenTextures(1, &PauseMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, PauseMenuTexture1);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    PauseMenu->width, PauseMenu->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, PauseMenu->data);

}

void renderPauseScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, PauseMenuTexture1);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(768, 768);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(768, 0);
    glEnd();
    glPopMatrix();
}

