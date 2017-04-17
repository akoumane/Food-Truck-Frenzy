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
int xres=800, yres=600;
int state_menu=0;
int title_screen=0;


Ppmimage *backgroundImage = NULL;

//customer spawn testing
Ppmimage *customerImage1 = NULL;
Ppmimage *customerImage2 = NULL;
Ppmimage *customerImage3 = NULL;
Ppmimage *customerImage4 = NULL;
GLuint customerTexture1;
GLuint customerTexture2;
GLuint customerTexture3;
GLuint customerTexture4;

GLuint backgroundTexture;
int background=1;

int main(void)
{
    //Box box;
    logOpen();
    imageConvert();
    initXWindows();
    initOpengl();
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
    //
    //load the images file into a ppm structure.
    //
    backgroundImage = ppm6GetImage("background.ppm");
    customerImage1 = ppm6GetImage("customer1.ppm");
    customerImage2 = ppm6GetImage("customer2.ppm");
    customerImage3 = ppm6GetImage("customer3.ppm");
    customerImage4 = ppm6GetImage("customer4.ppm");
    //
    //create opengl texture elements
    glGenTextures(1, &backgroundTexture);
    glGenTextures(1, &customerTexture1);
    glGenTextures(1, &customerTexture2);
    glGenTextures(1, &customerTexture3);
    glGenTextures(1, &customerTexture4);
    //background
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    backgroundImage->width, backgroundImage->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, backgroundImage->data);
    //customer1
    glBindTexture(GL_TEXTURE_2D, customerTexture1);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerImage1->width, customerImage1->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerImage1->data);
    //customer2
    glBindTexture(GL_TEXTURE_2D, customerTexture2);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerImage2->width, customerImage2->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerImage2->data);
    //customer3
    glBindTexture(GL_TEXTURE_2D, customerTexture3);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerImage3->width, customerImage3->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerImage3->data);
    //customer4
    glBindTexture(GL_TEXTURE_2D, customerTexture4);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    customerImage4->width, customerImage4->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, customerImage4->data);
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
	reshapeWindow(xce.width, xce.height);
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
    //Rect r;
    float custSizeY = 90/yres;
    float custSizeX = 63/xres;

    //Clear the screen
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //
    //
    //Box box;
    //drawbox(&box);
    //draw a quad with texture
    float wid = 120.0f;
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

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, customerTexture1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(70, 170);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(70, 260);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(133, 260);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(133, 170);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, customerTexture2);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(375, 170);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(375, 267);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(430, 267);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(430, 170);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, customerTexture3);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(70, 40);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(70, 136);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(130, 136);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(130, 40);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, customerTexture4);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(373, 40);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(373, 130);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(430, 130);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(430, 40);
    glEnd();
    glPopMatrix();

    //drawbox(&box);

    if(title_screen == 1) {
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

/*GLuint png_texture_load(const char * file_name, int * width, int * height)
  {
// This function was originally written by David Grayson for
// https://github.com/DavidEGrayson/ahrs-visualizer

png_byte header[8];

FILE *fp = fopen(file_name, "rb");
if (fp == 0)
{
perror(file_name);
return 0;
}

// read the header
fread(header, 1, 8, fp);

if (png_sig_cmp(header, 0, 8))
{
fprintf(stderr, "error: %s is not a PNG.\n", file_name);
fclose(fp);
return 0;
}

png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
if (!png_ptr)
{
fprintf(stderr, "error: png_create_read_struct returned 0.\n");
fclose(fp);
return 0;
}

// create png info struct
png_infop info_ptr = png_create_info_struct(png_ptr);
if (!info_ptr)
{
fprintf(stderr, "error: png_create_info_struct returned 0.\n");
png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
fclose(fp);
return 0;
}

// create png info struct
png_infop end_info = png_create_info_struct(png_ptr);
if (!end_info)
{
fprintf(stderr, "error: png_create_info_struct returned 0.\n");
png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
fclose(fp);
return 0;
}

// the code in this if statement gets called if libpng encounters an error
if (setjmp(png_jmpbuf(png_ptr))) {
fprintf(stderr, "error from libpng\n");
png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
fclose(fp);
return 0;
}

// init png reading
png_init_io(png_ptr, fp);

// let libpng know you already read the first 8 bytes
png_set_sig_bytes(png_ptr, 8);

// read all the info up to the image data
png_read_info(png_ptr, info_ptr);

// variables to pass to get info
int bit_depth, color_type;
png_uint_32 temp_width, temp_height;

// get info about png
png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
	NULL, NULL, NULL);

if (width){ *width = temp_width; }
if (height){ *height = temp_height; }

//printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);

if (bit_depth != 8)
{
    fprintf(stderr, "%s: Unsupported bit depth %d.  Must be 8.\n", file_name, bit_depth);
    return 0;
}

GLint format;
switch(color_type)
{
    case PNG_COLOR_TYPE_RGB:
	format = GL_RGB;
	break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
	format = GL_RGBA;
	break;
    default:
	fprintf(stderr, "%s: Unknown libpng color type %d.\n", file_name, color_type);
	return 0;
}

// Update the png info struct.
png_read_update_info(png_ptr, info_ptr);

// Row size in bytes.
int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

// glTexImage2d requires rows to be 4-byte aligned
rowbytes += 3 - ((rowbytes-1) % 4);

// Allocate the image_data as a big block, to be given to opengl
png_byte * image_data = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
if (image_data == NULL)
{
    fprintf(stderr, "error: could not allocate memory for PNG image data\n");
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
    return 0;
}

// row_pointers is for pointing to image_data for reading the png with libpng
png_byte ** row_pointers = (png_byte **)malloc(temp_height * sizeof(png_byte *));
if (row_pointers == NULL)
{
    fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    fclose(fp);
    return 0;
}

// set the individual row_pointers to point at the correct offsets of image_data
for (unsigned int i = 0; i < temp_height; i++)
{
    row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
}

// read the png into image_data through row_pointers
png_read_image(png_ptr, row_pointers);

// Generate the OpenGL texture object
GLuint texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
glTexImage2D(GL_TEXTURE_2D, 0, format, temp_width, temp_height, 0, format, GL_UNSIGNED_BYTE, image_data);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

// clean up
png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
free(image_data);
free(row_pointers);
fclose(fp);
return texture;
}*/
