
//Brandon Martinez 
//CMPS 3350 lab5
//
//UPDATES 
//***********************
//Start menu added PRESS A to turn on and off
//temp turned off on start
//more render functions added
//************************
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
#include "andyK.h"

#include <fcntl.h>
#include <sys/stat.h>
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif

using namespace std;

Ppmimage *StartMenu = NULL;
GLuint StartMenuTexture1;

Ppmimage *PauseMenu = NULL;
GLuint PauseMenuTexture1;

Ppmimage *HelpMenu = NULL;
GLuint HelpMenuTexture1;

Ppmimage *DefeatMenu = NULL;
GLuint DefeatMenuTexture1;

Ppmimage *VictoryMenu = NULL;
GLuint VictoryMenuTexture1;

Ppmimage *CreditMenu = NULL;
GLuint CreditMenuTexture1;

Ppmimage *LevelMenu = NULL;
GLuint LevelMenuTexture1;

#ifdef USE_OPENAL_SOUND
struct Global {
    ALuint alBufferBeep, alBufferButton, alBufferZone;
    ALuint alSourceBeep, alSourceButton, alSourceZone;
} b; 
#endif

extern "C" {
#include "fonts.h"
}
struct Vec {
    float x,y,z;
};
struct Shape {
    float width, height;
    float radius;
    Vec center;
};
struct Game {
    Shape box[5];
    int n;
    int mouse[2];
};

unsigned char *Transparent(Ppmimage *img, unsigned char col[3])
{
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
	*(ptr+3) = 1;
	if (	a == col[0] &&
		b == col[1] && 
		c == col[2]) {
	    * (ptr+3) = 0;
	}
	ptr += 4;
	data += 3;
    }
    return newdata;
}

void TitleScreen()
{
    unsigned char col[] = {0, 255, 0};
    StartMenu = ppm6GetImage("menu.ppm");
    glGenTextures(1, &StartMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, StartMenuTexture1);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *StartMenuData = Transparent(StartMenu, col);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	    StartMenu->width, StartMenu->height,
	    0, GL_RGBA, GL_UNSIGNED_BYTE, StartMenuData);
    free(StartMenuData);
	

#ifdef BOXES
    //Boxes to use for menu input
    Game game;
    game.n=0;

    //declare a box shape
    game.box[4].width = 100;
    game.box[4].height = 10;
    game.box[4].center.x = 120 + 5*65;
    game.box[4].center.y = 500 - 5*60;

    game.box[3].width = 100;
    game.box[3].height = 10;
    game.box[3].center.x = 120 + 4*65;
    game.box[3].center.y = 500 - 4*60;

    game.box[2].width = 100;
    game.box[2].height = 10;
    game.box[2].center.x = 120 + 3*65;
    game.box[2].center.y = 500 - 3*60;

    game.box[1].width = 100;
    game.box[1].height = 10;
    game.box[1].center.x = 120 + 2*65;
    game.box[1].center.y = 500 - 2*60;

    game.box[0].width = 100;
    game.box[0].height = 10;
    game.box[0].center.x = 120 + 1*65;
    game.box[0].center.y = 500 - 1*60;

    float w, h;

    for(int i=0; i<=5; i++)
    {
	Shape *s;
	glColor3ub(90,140,90);
	s = game.box[i];
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
#endif
}

void renderTitleScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, StartMenuTexture1);
    glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(768, 768);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(768, 0);
    glEnd();
    glPopMatrix();
}

void Help_Menu()
{
    unsigned char col[] = {0, 255, 0};
    HelpMenu = ppm6GetImage("menu_help.ppm");
    glGenTextures(1, &HelpMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, HelpMenuTexture1);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *HelpMenuData = Transparent(HelpMenu, col);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	    HelpMenu->width, HelpMenu->height,
	    0, GL_RGBA, GL_UNSIGNED_BYTE, HelpMenuData);
    free(HelpMenuData);
}

void renderHelpScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, HelpMenuTexture1);
    glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(768, 768);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(768, 0);
    glEnd();
    glPopMatrix();
}

void Victory_Menu()
{
    unsigned char col[] = {0, 255, 0};
    VictoryMenu = ppm6GetImage("menu_victory.ppm");
    glGenTextures(1, &VictoryMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, VictoryMenuTexture1);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *VictoryMenuData = Transparent(VictoryMenu, col);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	    VictoryMenu->width, VictoryMenu->height,
	    0, GL_RGBA, GL_UNSIGNED_BYTE, VictoryMenuData);
    free(VictoryMenuData);
}

void renderVictoryScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, VictoryMenuTexture1);
    glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(768, 768);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(768, 0);
    glEnd();
    glPopMatrix();
}

void Defeat_Menu() 
{	
    unsigned char col[] = {0, 255, 0};
    DefeatMenu = ppm6GetImage("menu_defeat.ppm");
    glGenTextures(1, &DefeatMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, DefeatMenuTexture1);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *DefeatMenuData = Transparent(DefeatMenu, col);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	    DefeatMenu->width, DefeatMenu->height,
	    0, GL_RGBA, GL_UNSIGNED_BYTE, DefeatMenuData);
    free(DefeatMenuData);

}

void renderDefeatScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, DefeatMenuTexture1);
    glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(768, 768);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(768, 0);
    glEnd();
    glPopMatrix();
}

void Pause_Menu() 
{	
    unsigned char col[] = {0, 255, 0};
    PauseMenu = ppm6GetImage("menu_pause.ppm");
    glGenTextures(1, &PauseMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, PauseMenuTexture1);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *PauseMenuData = Transparent(PauseMenu, col);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	    PauseMenu->width, PauseMenu->height,
	    0, GL_RGBA, GL_UNSIGNED_BYTE, PauseMenuData);
    free(PauseMenuData);

}

void renderPauseScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, PauseMenuTexture1);
    glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(768, 768);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(768, 0);
    glEnd();
    glPopMatrix();
}

void Credit_Menu() 
{	
    unsigned char col[] = {0, 255, 0};
    CreditMenu = ppm6GetImage("menu_credit.ppm");
    glGenTextures(1, &CreditMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, CreditMenuTexture1);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *CreditMenuData = Transparent(CreditMenu, col);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	    CreditMenu->width, CreditMenu->height,
	    0, GL_RGBA, GL_UNSIGNED_BYTE, CreditMenuData);
    free(CreditMenuData);

}

void renderCreditScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, CreditMenuTexture1);
    glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(768, 768);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(768, 0);
    glEnd();
}

void Level_Menu() 
{	
    unsigned char col[] = {0, 255, 0};
    LevelMenu = ppm6GetImage("menu_level.ppm");
    glGenTextures(1, &LevelMenuTexture1);
    glBindTexture(GL_TEXTURE_2D, LevelMenuTexture1);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *LevelMenuData = Transparent(LevelMenu, col);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	    LevelMenu->width, LevelMenu->height,
	    0, GL_RGBA, GL_UNSIGNED_BYTE, LevelMenuData);
    free(LevelMenuData);

}

void renderLevelScreen()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, LevelMenuTexture1);
    glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
    glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 768);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(768, 768);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(768, 0);
    glEnd();
}

#ifdef USE_OPENAL_SOUND
void initSound()
{
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR: alutInit()\n");
	return;
    }

    alGetError();

    float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);

    b.alBufferBeep = alutCreateBufferFromFile("./sounds/beep-08b.wav");
    b.alBufferButton = alutCreateBufferFromFile("./sounds/button-7.wav");
    b.alBufferZone = alutCreateBufferFromFile("./sounds/danger_zone.wav");

    alGenSources(1, &b.alSourceBeep);
    alSourcei(b.alSourceBeep, AL_BUFFER, b.alBufferBeep);

    alSourcef(b.alSourceBeep, AL_GAIN, 1.0f);
    alSourcef(b.alSourceBeep, AL_PITCH, 1.0f);
    alSourcei(b.alSourceBeep, AL_LOOPING, AL_FALSE);
    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR: setting source\n");
	return;
    }

    alGenSources(1, &b.alSourceButton);
    alSourcei(b.alSourceButton, AL_BUFFER, b.alBufferButton);

    alSourcef(b.alSourceButton, AL_GAIN, 1.0f);
    alSourcef(b.alSourceButton, AL_PITCH, 1.0f);
    alSourcei(b.alSourceButton, AL_LOOPING, AL_FALSE);
    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR: setting source\n");
	return;
    }

    alGenSources(1, &b.alSourceZone);
    alSourcei(b.alSourceZone, AL_BUFFER, b.alBufferZone);

    alSourcef(b.alSourceZone, AL_GAIN, 1.0f);
    alSourcef(b.alSourceZone, AL_PITCH, 1.0f);
    alSourcei(b.alSourceZone, AL_LOOPING, AL_TRUE);
    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR: setting source\n");
	return;
    }
}
#endif //USE_OPENAL_SOUND

#ifdef USE_OPENAL_SOUND
void cleanupSound()
{
    //First delete the source.
    alDeleteSources(1, &b.alSourceBeep);
    alDeleteSources(1, &b.alSourceButton);
    //Delete the buffer.
    alDeleteBuffers(1, &b.alBufferBeep);
    alDeleteBuffers(1, &b.alBufferButton);
    //Close out OpenAL itself.
    //Get active context.
    ALCcontext *Context = alcGetCurrentContext();
    //Get device for active context.
    ALCdevice *Device = alcGetContextsDevice(Context);
    //Disable context.
    alcMakeContextCurrent(NULL);
    //Release context(s).
    alcDestroyContext(Context);
    //Close device.
    alcCloseDevice(Device);
}

#endif //USE_OPENAL_SOUND
#ifdef USE_OPENAL_SOUND
void playSound(ALuint source)
{
    alSourcePlay(source);
}

#endif //USE_OPENAL_SOUND

