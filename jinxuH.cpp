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

using namespace std;

void printNameJ()
{
    Rect r;
    r.bot =200;
    r.center = 300;
    r.left = 200;
    unsigned int color = 0x80B7EE;
    ggprint8b(&r, 16, color, "Jinxu Han");
}
