void printName();
void imageConvert();
void cleanUp();

class Grid
{
    private:
        int grid[100][100];
        int xres, yres;
    public:
        Grid(int y, int x);
        void printGrid();
        int xdem();
        int ydem();
};

class Player
{
    private:
        int xpos, ypos;
    public:
        Player(int y, int x);
        void moveLeft();
        void moveRight();
        void moveDown();
        void moveUp();
        int xPos();
        int yPos();
};
