// Brandon Pitcher
// CMPS 3350 Lab 5
// Created: 23 February 2017
#include <iostream>
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
#include "fonts.h"

using namespace std;

void initXWindows(void)
{
        GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        //GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
        XSetWindowAttributes swa;

        setupScreenRes(640, 480);
        dpy = XOpenDisplay(NULL);
        if (dpy == NULL) {
                printf("\n\tcannot connect to X server\n\n");
                exit(EXIT_FAILURE);
        }
        Window root = DefaultRootWindow(dpy);
        XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
        if (vi == NULL) {
                printf("\n\tno appropriate visual found\n\n");
                exit(EXIT_FAILURE);
        }
        Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
        swa.colormap = cmap;
        swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
                                                StructureNotifyMask | SubstructureNotifyMask;
        win = XCreateWindow(dpy, root, 0, 0, xres, yres, 0,
                                                        vi->depth, InputOutput, vi->visual,
                                                        CWColormap | CWEventMask, &swa);
        GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
        glXMakeCurrent(dpy, win, glc);
        setTitle();
}

void reshapeWindow(int width, int height)
{
        //window has been resized.
        setupScreenRes(width, height);
        //
        glViewport(0, 0, (GLint)width, (GLint)height);
        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        glOrtho(0, xres, 0, yres, -1, 1);
        setTitle();
}

void reshapeWindow(int width, int height)
{
        //window has been resized.
        setupScreenRes(width, height);
        //
        glViewport(0, 0, (GLint)width, (GLint)height);
        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        glOrtho(0, xres, 0, yres, -1, 1);
        setTitle();
}

