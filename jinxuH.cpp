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
extern "C" {
#include "fonts.h"
}
//#include "Rectangle.h"

using namespace std;

void makeItem();//make Item box

struct Game {
    Shape table[4];
    Shape chairl[4]; //leftside chair
    Shape chairr[4]; //rightside chair
    Shape truck;
    Shape trashcan;
    int n;
};
void makeItem()
{
    Game game;
    game.n=0;
    //make table boxes
    for (int i=0; i<4; i++)
    {
        //make table boxes
        game.table[i].width = 50;
        game.table[i].height = 50;
        //position of tables;
        game.table[i].center.x = 100 + i*65;
        game.table[i].center.y = 500 - i*60;
        //make right chairs box
        game.chairr[i].width = 50;
        game.chairr[i].height = 50;
        //position of chairs
        game.chairr[i].center.x = 100 + i*65;
        game.chairr[i].center.y = 500 - i*60;
        //make left chairs box
        game.chairl[i].width = 50;
        game.chairl[i].height = 50;
        //position of chairs
        game.chairl[i].center.x = 100 + i*65;
        game.chairl[i].center.y = 500 - i*60;
    }
    //make truck boxes
    game.truck.width = 300;
    game.truck.height = 30;
    //poition of truck
    game.truck.center.x = 650;
    game.truck.center.y = 800;
    //make trushcan boxes
    game.trushcan.width = 10;
    game.trushcan.length = 220;
    //positioin of trush can
    game.trushcan.center.x = 300;
    game.trushcan.center.y = 200;

}
void printNameJ()
{
    Rect r;
    r.bot =200;
    r.center = 300;
    r.left = 200;
    unsigned int color = 0x80B7EE;
    ggprint8b(&r, 16, color, "Jinxu Han");
}

bool isCollision(SDL_Rect& obj1, Game *game)
{
    //check collision with table
    Shape *s;
    //left1 < right2 && right1>left2 && top1 < bottom2 && bottom1 > top2
    /*
       if (obj1.center < obj2.x +obj2.w &&
       obj1.x + obj1.w > obj2.x &&
       obj1.y < obj2.y + obj2.h &&
       obj1.y + obj1.h > obj2.y)
       {
       return true;
       }
       else
       return false;
       */
    //need replace p->.s with the charlector object
    for (int j=0;j<4;j++){
        t = &game->table[j];
        cl = &game -> chairl[j];
        cr = &game -> chairr[j];
        if (p->s.center.y < t->center.y + t->height &&
                p->s.center.y> t->center.y - t->height &&
                p->s.center.x >= t->center.x -t->width &&
                p->s.center.x <= t->center.x +t->width &&
                //col with chair l
                p->s.center.y < s->center.y + s->height &&
                p->s.center.y> cl->center.y - cl->height &&
                p->s.center.x >= cl->center.x -cl->width &&
                p->s.center.x <= cl->center.x +cl->width &&
                //col with chair r
                p->s.center.y < cr->center.y + cr->height &&
                p->s.center.y> cr->center.y - cr->height &&
                p->s.center.x >= cr->center.x -cr->width &&
                p->s.center.x <= cr->center.x +cr->width)
        {
            return true;
        }
        else
            return false;
    }
}
