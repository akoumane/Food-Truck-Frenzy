//Andy Koumane
//andyK.cpp

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
using namespace std;

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius,
    GLint numSides)
{
	GLint numVertices = numSides + 2;
    GLfloat doublePi = 2.0f * M_PI;

    GLfloat circleVerticesX[numVertices];
    GLfloat circleVerticesY[numVertices];
    GLfloat circleVerticesZ[numVertices];

    circleVerticesX[0] = x;
    circleVerticesY[0] = y;
    circleVerticesZ[0] = z;
    
    for (int i = 1; i < numVertices; i++) {   
        circleVerticesX[i] = x + (radius * cos(i * doublePi / numSides));      
        circleVerticesY[i] = y + (radius * sin(i * doublePi / numSides));      
        circleVerticesZ[i] = z;
    }

    GLfloat allCircleVertices[numVertices * 3];

    for(int i = 0; i < numVertices; i++) {
        allCircleVertices[i * 3] = circleVerticesX[i];
        allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
        allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices);
    glDisableClientState(GL_VERTEX_ARRAY);
}
