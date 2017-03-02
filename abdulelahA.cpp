// Abdul
//

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
#include "abdulelahA.h"

extern "C" {
#include "fonts.h"
}


void drawRect(void)
{

    glBegin(GL_LINE_LOOP);
    	glVertex2i(50,90);
    	glVertex2i(100,90);
    	glVertex2i(100,150);
    	glVertex2i(50,150);
    glEnd();
}
