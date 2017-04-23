void printName();
void imageConvert();
void cleanUp();

class Grid
{
    // ID Guide
    // 0 = blank space
    // 1 = Player
    // 2-6 = customers
    // 7 = restriced space
    // 8 = chair
    // 9 = table
    private:
        int grid[20][20];
        int xres, yres;
    public:
        Grid(int y, int x);
        void printGrid();
        int xdem();
        int ydem();
        void gridItem(int y, int x, int id);
};

class Player
{
    private:
        int xpos, ypos;
    public:
        Player(int y, int x);
        void moveLeft();
        void moveRight(int x);
        void moveDown(int y);
        void moveUp();
        int xPos();
        int yPos();
};
