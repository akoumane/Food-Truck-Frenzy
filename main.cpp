// CMPS 3350 Project
// Food Truck Frenzy
// Group 8

// Abdulelah A
// Andy K
// Brandon M
// Brandon P
// Jin H

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
#include "andyK.h"
#include "brandonM.h"
#include "brandonP.h"
#include "jinxuH.h"
#include "abdulelahA.h"
using namespace std;

extern "C" {
#include "fonts.h"
}

//defined types
typedef double Flt;
typedef double Vec[3];

//macros
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)
#define random(a) (rand()%a)
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
			     (c)[1]=(a)[1]-(b)[1]; \
(c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define ALPHA 1

//X Windows variables
Display *dpy;
Window win;

//function prototypes
void initXWindows(void);
void initOpengl(void);
void cleanupXWindows(void);
void checkResize(XEvent *e);
void checkMouse(XEvent *e);
void checkKeys(XEvent *e);
void physics(void);
void render(void);
GLuint png_texture_load(const char * file_name, int * width, int * height);

//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 30.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
unsigned int upause=0;
double timeDiff(struct timespec *start, struct timespec *end) {
    return (double)(end->tv_sec - start->tv_sec ) +
	(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) {
    memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------






//global variables

int done=0;
int xres=768, yres=768;
int state_menu=0;
int title_screen=0;
const int X_Dem = 7;	// Dimension for Grid
const int Y_Dem = 4;	// Dimension for Grid

Customer *customer;
Ppmimage *backgroundImage = NULL;
Grid *grid;
Player *p1;
//customer spawn testing
/*Ppmimage *customerStanding1 = NULL;
Ppmimage *customerSitting1 = NULL;
Ppmimage *customerSitting2 = NULL;
Ppmimage *customerSitting3 = NULL;
Ppmimage *customerSitting4 = NULL;
GLuint customerStandingTexture1;
GLuint customerSittingTexture1;
GLuint customerSittingTexture2;
GLuint customerSittingTexture3;
GLuint customerSittingTexture4;*/
GLuint backgroundTexture;
int background=1;

int main(void)
{
	// Clear terminal
	system("clear");
    //Box box;
    logOpen();
    imageConvert();
    initXWindows();
    initOpengl();
    customer = new Customer();
	grid = new Grid(Y_Dem,X_Dem);
	p1 = new Player(grid->ydem()/2, grid->xdem()/2);
	
    clock_gettime(CLOCK_REALTIME, &timePause);
    clock_gettime(CLOCK_REALTIME, &timeStart);

    //object(box);
    //drawbox(&box);
    while (!done) {
	while (XPending(dpy)) {
	    XEvent e;
	    XNextEvent(dpy, &e);
	    checkResize(&e);
	    checkMouse(&e);
	    checkKeys(&e);
	}
	//
	//Below is a process to apply physics at a consistent rate.
	//1. Get the time right now.
	clock_gettime(CLOCK_REALTIME, &timeCurrent);
	//2. How long since we were here last?
	timeSpan = timeDiff(&timeStart, &timeCurrent);
	//3. Save the current time as our new starting time.
	timeCopy(&timeStart, &timeCurrent);
	//4. Add time-span to our countdown amount.
	physicsCountdown += timeSpan;
	//5. Has countdown gone beyond our physics rate?
	//       if yes,
	//           In a loop...
	//              Apply physics
	//              Reducing countdown by physics-rate.
	//              Break when countdown < physics-rate.
	//       if no,

	//Apply no physics this frame.
	while (physicsCountdown >= physicsRate) {
	    //6. Apply physics
	    physics();
	    //7. Reduce the countdown by our physics-rate
	    physicsCountdown -= physicsRate;
	}
	//Always render every frame.

	render();
	glXSwapBuffers(dpy, win);
    }
    cleanupXWindows();
    cleanup_fonts();
    cleanUp();
    logClose();

    // 	DEBUGGING FOR GRID
    /*
       Game *g = new Game(40,40);
       g->printGrid();
       */
    return 0;
}

void cleanupXWindows(void)
{
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}

void setTitle(void)
{
    //Set the window title bar.
    XMapWindow(dpy, win);
    XStoreName(dpy, win, "Food Truck Frenzy");
}

void setupScreenRes(const int w, const int h)
{
    xres = w;
    yres = h;
}

void initXWindows(void)
{
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    //GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
    XSetWindowAttributes swa;

    setupScreenRes(xres, yres);
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

unsigned char *buildAlphaData(Ppmimage *img)
{
    //add 4th component to RGB stream...
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
	//get largest color component...
	//*(ptr+3) = (unsigned char)((
	//		(int)*(ptr+0) +
	//		(int)*(ptr+1) +
	//		(int)*(ptr+2)) / 3);
	//d = a;
	//if (b >= a && b >= c) d = b;
	//if (c >= a && c >= b) d = c;
	//*(ptr+3) = d;
	*(ptr+3) = (a|b|c);
	ptr += 4;
	data += 3;
    }
    return newdata;
}

void initOpengl(void)
{
    //OpenGL initialization
    glViewport(0, 0, xres, yres);
    //Initialize matrices
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    //This sets 2D mode (no perspective)
    glOrtho(0, xres, 0, yres, -1, 1);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FOG);
    glDisable(GL_CULL_FACE);

    //Clear the screen
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    //Do this to allow fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();
    backgroundImage = ppm6GetImage("background.ppm");
    glGenTextures(1, &backgroundTexture);
    //background
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    backgroundImage->width, backgroundImage->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, backgroundImage->data);

    makeCustomers();
    makeFoods();

}

void checkResize(XEvent *e)
{
    //The ConfigureNotify is sent by the
    //server if the window is resized.
    if (e->type != ConfigureNotify)
	return;
    XConfigureEvent xce = e->xconfigure;
    if (xce.width != xres || xce.height != yres) {
	//Window size did change.
	reshapeWindow(xres, yres);
    }
}

void initSounds(void)
{
    //You may add sound here for some extra credit.
    //Fmod is not allowed.
    //OpenAL sound only.
    //Look for the openalTest folder under /code.

}


void checkMouse(XEvent *e)
{
    //Did the mouse move?
    //Was a mouse button clicked?
    static int savex = 0;
    static int savey = 0;
    //
    if (e->type == ButtonRelease) {
	return;
    }
    if (e->type == ButtonPress) {
	if (e->xbutton.button==1) {
	    //Left button is down
	}
	if (e->xbutton.button==3) {
	    //Right button is down
	}
    }
    if (savex != e->xbutton.x || savey != e->xbutton.y) {
	//Mouse moved
	savex = e->xbutton.x;
	savey = e->xbutton.y;
    }
}

void checkKeys(XEvent *e)
{
    //keyboard input?
    static int shift=0;
    int key = XLookupKeysym(&e->xkey, 0);
    if (e->type == KeyRelease) {
	if (key == XK_Shift_L || key == XK_Shift_R)
	    shift=0;
	return;
    }
    if (e->type == KeyPress) {
	if (key == XK_Shift_L || key == XK_Shift_R) {
	    shift=1;
	    return;
	}
    } else {
		return;
    }
    switch(key) {
		case XK_m:
		    //optimized below
		    //if(state_menu == 0)
		    //	state_menu = 1;
		    //  else
		    //	state_menu = 0;
		    state_menu ^= 1;
		    break;

		case XK_a:
		    title_screen ^= 1;
		    //input_title_screen();
		    break;
		    //add if state_menu disable or rebind the keys
		case XK_Left:
		    break;
		case XK_Right:
		    break;
		case XK_Up:
		    break;
		case XK_Down:
		    break;
		case XK_g:
			grid->printGrid();
			break;
	#ifdef RENDERTEST
	case XK_q:
		clock_gettime(CLOCK_REALTIME, &timeStart);
		clock_gettime(CLOCK_REALTIME, &timePause);
		while(timeDiff(&timeStart, &timePause) < 1.0)
			clock_gettime(CLOCK_REALTIME, &timePause);
		customer->setInLine(false);
	    break;
	#endif
	case XK_Escape:
	    done=1;
	    break;
    }
}

Flt VecNormalize(Vec vec)
{
    Flt len, tlen;
    Flt xlen = vec[0];
    Flt ylen = vec[1];
    Flt zlen = vec[2];
    len = xlen*xlen + ylen*ylen + zlen*zlen;
    if (len == 0.0) {
	MakeVector(0.0,0.0,1.0,vec);
	return 1.0;
    }
    len = sqrt(len);
    tlen = 1.0 / len;
    vec[0] = xlen * tlen;
    vec[1] = ylen * tlen;
    vec[2] = zlen * tlen;
    return(len);
}

void physics(void)
{
    if (state_menu)
	return;
}


void render(void)
{
    Box box;

    //Clear the screen
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //
    //
    //Box box;
    //drawbox(&box);
    //draw a quad with texture
    //float wid = 120.0f;
    //glColor3f(1.0, 1.0, 1.0);
    if (background) {
		glBindTexture(GL_TEXTURE_2D, backgroundTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
		glEnd();
    }
	#ifdef RENDERTEST
	//renderCustomers();
	//renderFoods();
	customer->renderModel();
	#endif
	//object(&box);
	//drawbox(&box);


    if(title_screen == 1) {
	    	renderTitleScreen();
		TitleScreen();
    }
    if(title_screen == 0) {

	glDisable(GL_TEXTURE_2D);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glBegin(GL_QUADS);
	//	glVertex2i(10,10);
	//	glVertex2i(10,60);
	//	glVertex2i(60,60);
	//	glVertex2i(60,10);
	//glEnd();
	//return;
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	/*if (state_menu == 1) {
	  Pause_Menu();
	  }*/

	glEnable(GL_TEXTURE_2D);
	/*r.bot = yres - 20;
	  r.left = 10;
	  r.center = 0;*/
    }
}
