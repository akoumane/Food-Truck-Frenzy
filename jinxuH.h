#ifndef JINXUH_H
#define JINXUH_H
//JinH.h
//
struct JinVec {
    float x, y, z;
};

struct Shape {
    float width, height;
    float radius;
    JinVec center;
};

struct Box {
    Shape table[3];
    Shape stable[1];
    Shape circle;
    int n;
    int bubbler;
    int mouse[2];
    Box() {
	n=0;
	bubbler=0;

    }
};

void object(Box *box);
void drawbox(Box *box);
bool isCollision();
#endif

