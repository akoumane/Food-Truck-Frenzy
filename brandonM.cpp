
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

extern "C" {
#include "fonts.h"
}

using namespace std;

void printBrandonName()
{
    Rect r;
    r.bot = 100;
    r.left = 140;
    r.center = 100;
    unsigned int color = 0x00dddd00;
    ggprint8b(&r, 16, color, "Brandon Martinez!!!");
}
/*
   void input_title_screen()
   {
   title_screen ^= 1;
   }
   */
void TitleScreen()
{
    glDisable(GL_TEXTURE_2D);
    Rect t;
    glColor3ub(255, 0, 0);
    int cx = 800/2;
    int cy = 600/2;
    glBegin(GL_QUADS);
    //glVertex2i(cx-400, cy+400);
    //glVertex2i(cx+300, cy+400);
    //glVertex2i(cx+300, cy-400);
    //glVertex2i(cx-400, cy-400);
    glEnd();
    glEnable(GL_TEXTURE_2D);
    t.bot = cy;
    t.left = cx-150;
    t.center = 0;
    unsigned int color = 0x00dddd00;
    ggprint16(&t, 16, 0x00ffff00, "Food Truck Frenzy!!!");
    ggprint8b(&t, 16, color, "This is the second line");


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
