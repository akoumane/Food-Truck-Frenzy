void printName();
void imageConvert();
void cleanUp();
void makeWaiter();
void renderWaiter(int ypos, int xpos);
void waiterBurger();
void interaction(Player& p, Food& f1, Food& f2, Food& f3, Food& f4, Food& f5
    Food& f6);

class Table
{
    public:
        int arr[6];
        Food* f1;
        Food* f2;
        Food* f3;
        Food* f4;
        Food* f5;
        Food* f6;
        Table();
};

class Food
{
    private:
        int food_id;
        int ypos;
        int xpos;
        bool on_side;
        bool on_table;
        bool moving;
        Ppmimage *burgeronplate;
        Ppmimage *hotdogonplate;
        Ppmimage *pizzaonplate;
        GLuint burgeronplate_texture;
        GLuint hotdogonplate_texture;
        GLuint pizzaonplate_texture;

    public:
        Food();
        void renderFood(bool in_seat, int seat_num, int food_id);
        void makeFood();
        void setPos(int y, int x);
        void setPos(int table);
        void set_on_side();
        void set_on_table();
        void set_moving();
        bool check_on_side();
        bool check_on_table();
        bool check_moving();


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
