
//Brandon Martinez 
//CMPS 3350 lab5
//
//UPDATES over Spring break so far
//Finished up the alphabet assets which can be viewable in the alphabet folder
//usage in program comming soon

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

void printBrandonName()
{
    Rect r;
    r.bot = 100;
    r.left = 140;
    r.center = 100;
    unsigned int color = 0x00dddd00;
    ggprint8b(&r, 16, color, "Brandon Martinez!!!");
}

void TitleScreen()
{
    StartMenu = ppm6GetImage("menu.ppm");
    glGenTextures(1, &StartMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, StartMenuTexture1);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    StartMenu->width, StartMenu->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, StartMenu->data);
    /*
    glDisable(GL_TEXTURE_2D);
    Rect t;
    glColor3ub(255, 0, 0);
    int cx = 800/2;
    int cy = 600/2;
    glBegin(GL_QUADS);
    glEnd();
    glEnable(GL_TEXTURE_2D);
    t.bot = cy;
    t.left = cx-150;
    t.center = 0;
    unsigned int color = 0x00dddd00;
    ggprint16(&t, 16, 0x00ffff00, "Food Truck Frenzy!!!");
    ggprint8b(&t, 16, color, "This is the second line");

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
*/
}
void Option_Menu()
{
//music on and off
//starting difficulty
}
void Help_Menu()
{
//controls
//main purpose of game
// ?credits?
}
void LeaderBoard_Menu()
{
}
void Pause_Menu() 
{	
    Rect r;
    glColor3f(1.0, 0.0,0.0);
    int cx = 800/2;
    int cy = 600/2;
    glBegin(GL_QUADS);
    glVertex2i(cx-100, cy+100);
    glVertex2i(cx+100, cy+100);
    glVertex2i(cx+100, cy-100);
    glVertex2i(cx-100, cy-100);
    glEnd();
    glEnable(GL_TEXTURE_2D);
    r.bot = cy + 20;
    r.left = cx;
    r.center = 1;
    unsigned int color = 0x00dddd00;
    ggprint8b(&r, 16, 0x00ffff00, "This is my menu");
    ggprint8b(&r, 16, color, "This is the second line");

}
