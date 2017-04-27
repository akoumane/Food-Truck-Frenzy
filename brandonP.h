void printName();
void imageConvert();
void cleanUp();
void makeWaiter();
void renderWaiter(int ypos, int xpos);

class Food
{
    private:
        int food_id;
        int ypos;
        int xpos;
        bool on_side;
        bool on_table;
        bool moving;
        Ppmimage *burgeronplateonside;
        Ppmimage *burgerontable;
        Ppmimage *hotdogonplateonside;
        Ppmimage *hotdogontable;
        Ppmimage *pizzaonplateonside;
        Ppmimage *pizzaontable;
        GLuint burgeronplateonside_texture;
        GLuint burgerontable_texture;
        GLuint hotdogonplateonside_texture;
        GLuint hotdogontable_texture;
        GLuint pizzaonplateonside_texture;
        GLuint pizzaontable_texture;
    public:
        Food();
        void renderFood(bool in_seat, int seat_num, int arr[]);
        void makeFood();
        void setPos(int y, int x);


};

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
    public:
    //private:
        int xpos, ypos;
    //public:
        Player(int y, int x);
        void moveLeft();
        void moveRight();
        void moveDown();
        void moveUp();
        int xPos();
        int yPos();
};
