#ifndef JINXUHN_H
#define JINXUHN_H
/*class Position
  {
  private:
  int xPos1, xPos2, yPos1, yPos2;
  public:
  int getposition(int x1, int x2, int y1, int y2);
  };*/
class Box
{
    private:
	int xPos1, xPos2, yPos1, yPos2;
    public:
	Box();
	//put all this into a class
	int tablexpos1[4];
	int tablexpos2[4];
	int tableypos1[4];
	int tableypos2[4];
	int stablexpos1[2];
	int stablexpos2[2];
	int stableypos1[2];
	int stableypos2[2];
	int wxpos1;
	int wypos1;
	bool col;
	//functions
	void makebox(int x1,int x2 ,int y1, int y2);
	void makewaiter(int x1, int y1);
	void drawtable(int x1, int x2, int y1, int y2);
	void drawwaiter(int x1, int y1);
	void gettable();
	void getwaiter();
	void showItem();
	bool colwithRight();
	bool colwithLeft();
	bool colwithUp();
	bool colwithDown();

	void gettableposition(int i, int x1, int x2, int y1, int y2);
	void getstableposition(int x1, int x2, int y1, int y2);
	void getwposition(int x1, int y1);
	void movewUp();
	void movewDown();
	void movewLeft();
	void movewRight();

	/*
	   int gettx1()
	   {
	   return *tablexpos1;
	   }
	   int gettx2()
	   {
	   return *tablexpos2;
	   }
	   int getty1()
	   {
	   return *tableypos1;
	   }
	   int getty2()
	   {
	   return *tableypos2;
	   }

	//
	int getstx1()
	{
	return *stablexpos1;
	}
	int getstx2()
	{
	return *stablexpos2;
	}
	int getsty1()
	{
	return *stableypos1;
	}
	int getsty2()
	{
	return *stableypos2;
	}
	//
	// int getwx1()
	{
	return wxpos1;
	}
	//int getwx2()
	//{
	//    return wxpos2;
	// }
	// int getwy1()
	// {
	//     return wypos1;
	// }
	// int getwy2()
	// {
	//     return wypos2;
	// }*/
};
#endif
