//Jinxu Han

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>

#include "fonts.h"
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


void object(void)
{
    //declare game object
    Box box;
    box.n=0;
    //declare a box shape
    for (int i = 0; i < 3; i++) {
        box.table[3].width = 30;
        box.table[3].height = 30;
    }
        //position of the table
        // box.table[1].center.x = 200+ i*65;
        // box.table[1].center.y = 500 - i*60;
        // box.table[2].center.x = 200+ i*65;
        // box.table[2].center.y = 500 - i*60;
        // box.table[3].center.x = 200+ i*65;
        // box.table[3].center.y = 500 - i*60;
        // box.table[4].center.x = 200+ i*65;
        // box.table[4].center.y = 500 - i*60;
    box.truck.width = 100;
    box.truck.height = 30;
    //position of the truck
    //box.truck.center.x = 10;
    //box.truck.center.y = 0;

}

void drawbox(Box *box)
{
    float w, h;
    glClear(GL_COLOR_BUFFER_BIT);
    //Draw shapes...

    //draw chair box
    Shape *s;
    for (int i=0; i<3;i++){
        glColor3ub(255,255,255);
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

    glColor3ub(255,255,255);
    s = &box->truck;
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
