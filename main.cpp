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
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif

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
//void makeWaiter();
GLuint png_texture_load(const char * file_name, int * width, int * height);



//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
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
#ifdef USE_OPENAL_SOUND

extern void initSound();
extern void cleanupSound();
extern void playSound(ALuint source);
extern struct Global {
    ALuint alBufferBeep, alBufferButton, alBufferZone;
    ALuint alSourceBeep, alSourceButton, alSourceZone;
} b;

#endif

//-----------------------------------------------------------------------------


//global variables

int done=0;
int xres=768, yres=768;
int state_menu=0;
int help_menu=0;
bool title_screen=true;
const int X_Dem = 7;	// Dimension for Grid
const int Y_Dem = 5;	// Dimension for Grid
bool boo = false;

//Customer *customer;
Level *level;
Ppmimage *backgroundImage = NULL;
Grid *grid;
Player *p1;
Box *b1;
Table *t1;
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
    logOpen();
    imageConvert();
    initXWindows();
    initOpengl();
#ifdef USE_OPENAL_SOUND
    initSound();
#endif
#ifdef USE_OPENAL_SOUND
    playSound(b.alSourceZone);
#endif


    //customer = new Customer();
    level = new Level();
    level->makeNewLevel(1);
    grid = new Grid(Y_Dem,X_Dem);
    p1 = new Player(4, 253, 4);
	b1= new Box();
	t1 = new Table();
    clock_gettime(CLOCK_REALTIME, &timePause);
    clock_gettime(CLOCK_REALTIME, &timeStart);

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
	    //renderWaiter(p1->ypos, p1->xpos);
	    //7. Reduce the countdown by our physics-rate
	    physicsCountdown -= physicsRate;
	}
	//Always render every frame.

	if(title_screen == true) {
	    renderTitleScreen();
	    TitleScreen();
	    if (help_menu == 1) {
			renderHelpScreen();
			Help_Menu();
	    }
	}
	if(title_screen == false) {
	    if (state_menu == 1) {
			renderPauseScreen();
			Pause_Menu();
			level->calcPauseTime();
	    }
	    else {
			level->addPauseTotal();
			render();
			renderWaiter(p1->ypos, p1->xpos);
			if (boo) {


			}

			//b1->getwaiter(); //need it when acture use
			#ifdef RENDERTEST

			if (level->getStart()) {
		    	level->startGame();
			}

			//b1->showItem();

			//renderCustomers();
			#endif

	    }
	}

	glXSwapBuffers(dpy, win);
    }
#ifdef USE_OPENAL_SOUND
	cleanupSound();
#endif
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

	makeNumbers();
	makeCustomers();
    //makeFoods();
	makeWaiter(3);
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
		    if (title_screen == false)
		    	state_menu ^= 1;
		    break;

		case XK_a:
		    if (title_screen == true) {
		#ifdef USE_OPENAL_SOUND
		    playSound(b.alSourceBeep);
		#endif
		    }
		    title_screen = false;
		    break;

		case XK_h:
		    if (title_screen == true) {
		#ifdef USE_OPENAL_SOUND
		    playSound(b.alSourceBeep);
		#endif
		    help_menu ^= 1;
		    }
		    break;
		case XK_Return:
			interaction(p1, t1, level);
			break;
		case XK_Left:
			b1->movewLeft();
		    if  (b1->colwithRight()==false) {
			p1->moveLeft();
		    }
			cout << "Move Left\n";
			cout << "xpos: " << p1->xpos;
			cout <<"\nypos: " << p1->ypos << "\n\n";
			break;
		case XK_Right:
			b1->movewRight();
			if (b1->colwithLeft()==false) {
			p1->moveRight();
			}
			cout << "Move Right\n";
			cout << "xpos: " << p1->xpos;
			cout <<"\nypos: " << p1->ypos << "\n\n";
			break;
		case XK_Up:
			b1->movewUp();
			if (b1->colwithDown()==false) {
			p1->moveUp();
			}
			cout << "Move Down\n";
			cout << "xpos: " << p1->xpos;
			cout <<"\nypos: " << p1->ypos << "\n\n";
			break;
		case XK_Down:
			b1->movewDown();
			if (b1->colwithUp() == false) {
			p1->moveDown();
			}
			//swapped down with Up
			cout << "Move Down\n";
			cout << "xpos: " << p1->xpos;
			cout <<"\nypos: " << p1->ypos << "\n\n";
			break;
		case XK_g:
			grid->printGrid();
			break;
		case XK_f:				// ******************************************
			boo = !boo;
			break;
		case XK_k:
			t1->f1->set_moving();
			break;
		#ifdef RENDERTEST
		case XK_q:
			level->startGame(true);
       		break;
    	case XK_w:
			level->printLine();
			break;
		case XK_e:
			level->printSeat();
			break;
		case XK_r:
			level->setCustomerLeave(0);
			break;
		case XK_t:
			level->setCustomerLeave(1);
			break;
		case XK_y:
			level->setCustomerLeave(2);
			break;
		case XK_u:
			level->setCustomerLeave(3);
			break;
		case XK_i:
			level->setCustomerLeave(4);
			break;
		case XK_o:
			cout << title_screen << endl;
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

    //Clear the screen
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //
    //
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
	if (t1->food1 == true) {
		//cout << "Food ID: " << t1->tableID[0] << endl;
		t1->f1->renderFood(1, 1, t1->tableID[0]);
		if (p1->resetWaiter == true) {
			p1->foodChoice = 0;
			makeWaiter(p1->foodChoice);
			p1->resetWaiter = false;
		}
		//t1->f1->renderFood(1, 1, 3);
	}
	if (t1->food2) {

	}
	if (t1->food3) {

	}
	if (t1->food4) {

	}
	if (t1->food5) {

	}
	if (t1->food6) {

	}

	//b1->gettable(); //need it when acture use

/*
    if(title_screen == true) {
	    	renderTitleScreen();
		TitleScreen();
	if (help_menu == 1) {
	  renderHelpScreen();
	  Help_Menu();
	  }
    }
    */
    /*
    if(title_screen == false) {
	if (state_menu == 1) {
	  renderPauseScreen();
	  Pause_Menu();
	  }
    }
    */
}
