#ifndef JINXUHN_H
#define JINXUHN_H
class Box 
{
    private:
	int xPos1, xPos2, yPos1, yPos2;
    public:
	Box();
	void makebox(int x1,int x2 ,int y1, int y2);
	void gettable();
	void drawtable(int x1, int x2, int y1, int y2);
};
//class {
//    private:


//}
//#include "jinxuHN.cpp"
#endif
