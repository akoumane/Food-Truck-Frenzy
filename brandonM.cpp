//modified by: Brandon Martinez
//date:
//purpose:
//
//3350
//program: rainforest
//author:  Gordon Griesel
//date:    2013 to present

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "ppm.h"
extern "C" {
#include "fonts.h"
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
//add if state_menu disable or rebind the keys
	case XK_b:
	    showBigfoot ^= 1;
	    if (showBigfoot) {
		bigfoot.pos[0] = -250.0;
	    }
	    break;
	case XK_d:
	    deflection ^= 1;
	    break;
	case XK_f:
	    forest ^= 1;
	    break;
	case XK_s:
	    silhouette ^= 1;
	    printf("silhouette: %i\n",silhouette);
	    break;
	case XK_t:
	    trees ^= 1;
	    break;
	case XK_u:
	    showUmbrella ^= 1;
	    break;
	case XK_p:
	    umbrella.shape ^= 1;
	    break;
	case XK_r:
	    showRain ^= 1;
	    //if (!show_rain)
	    //	cleanup_raindrops();
	    break;
	case XK_Left:
	    VecCopy(umbrella.pos, umbrella.lastpos);
	    umbrella.pos[0] -= 10.0;
	    break;
	case XK_Right:
	    VecCopy(umbrella.pos, umbrella.lastpos);
	    umbrella.pos[0] += 10.0;
	    break;
	case XK_Up:
	    VecCopy(umbrella.pos, umbrella.lastpos);
	    umbrella.pos[1] += 10.0;
	    break;
	case XK_Down:
	    VecCopy(umbrella.pos, umbrella.lastpos);
	    umbrella.pos[1] -= 10.0;
	    break;
	case XK_equal:
	    if (++ndrops > 40)
		ndrops=40;
	    break;
	case XK_minus:
	    if (--ndrops < 0)
		ndrops = 0;
	    break;
	case XK_n:
	    break;
	case XK_w:
	    if (shift) {
		//shrink the umbrella
		umbrella.width *= (1.0 / 1.05);
	    } else {
		//enlarge the umbrella
		umbrella.width *= 1.05;
	    }
	    //half the width
	    umbrella.width2 = umbrella.width * 0.5;
	    umbrella.radius = (float)umbrella.width2;
	    break;
	case XK_Escape:
	    done=1;
	    break;
    }
}


