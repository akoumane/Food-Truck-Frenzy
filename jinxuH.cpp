//Jinxu Han

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "jinxuH.h"
#include "fonts.h"
/*
   struct Vec {
   float x, y, z;
   };

   struct Shape {
   float width, height;
   float radius;
   Vec center;
   };

   struct Box {
   Shape table[3];
   Shape truck;
//    Shape circle;
//    Particle particle[MAX_PARTICLES];
int n;
int bubbler;
int mouse[2];
Box() {
n=0;
bubbler=0;

}
};

 */
/*void object(Box *box)
{
    //declare game object
    //Box box;
    //box.n=0;
    //declare a box shape
    for (int i = 0; i < 4; i++) {
        box->table[i].width = 95;
        box->table[i].height = 68;
    }
    //position of the table
    //table 1
    box->table[0].center.x = 120;
    box->table[0].center.y = 300;
    //table 2
    box->table[1].center.x = 642;
    box->table[1].center.y = 300;
    //table 3
    box->table[2].center.x = 120;
    box->table[2].center.y = 97;
    //table 4
    box->table[3].center.x = 642;
    box->table[3].center.y = 97;
    //declare the stable shape
    for (int i=0; i<2;i++){
        box->stable[i].width = 58;
        box->stable[i].height =36;
    }
    //position of the sidetable
    box->stable[0].center.x = 527;
    box->stable[0].center.y = 576;
    box->stable[1].center.x = 643;
    box->stable[1].center.y = 576;

    //declare the waiter box
    box->waiter[0].width = 5;
    box->waiter[0].height =40;
    //position of the waiter
    box->waiter[0].center.x = 527;
    box->waiter[0].center.y = 300;



}

void drawbox(Box *box)
{
    float w, h;
    //glClear(GL_COLOR_BUFFER_BIT);
    //Draw shapes...

    //draw table box
    Shape *s;
    for (int i=0; i<4;i++){
        //glColor3ub(246,29,88);
        s = &box->table[i];
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
    //draw truck box
    for (int i=0; i<2; i++)
    {
        //glColor3ub(246,29,29);
        s = &box->stable[i];
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
    //draw waiter box
    s = &box->waiter[0];
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

bool iscolisionwithtable(Box *box)
{
    bool col=false;
    //Shape *s;
    Shape *t;
    Shape *w;
    for (int i = 0; i<5;i++)
    {
       //s = &box -> sidetalbe[j];
        t = &box -> table[i];
        w = &box -> waiter[0];
        if (w->center.y < t->center.y + t->height &&
            w->center.y > t->center.y - t->height && 
            w->center.x >= t->center.x - t->width && 
            w->center.x <= t->center.x + t->width  
            )
        {
            col = true;
        }
        else
            col = false;
    }
    return col;
}

bool isclolisionwithstable(Box *box)
{
    bool col=false;
    Shape *s;
    Shape *w;
    for (int i=0; i< 2; i++)
    {
        s = &box->stable[i];
        w = &box -> waiter[0];
        if (w->center.y < s->center.y + s->height &&
            w->center.y > s->center.y - s->height && 
            w->center.x >= s->center.x - s->width &&  
            w->center.x <= s->center.x + s->width  
            )
        {
            col =  true;
        }
        else 
        col = false;

    }
    return col;

}*/
