void makeCustomers();
void makeFoods();
void renderCustomers();
void renderFoods();

class Customer
{
    private:
        int xPos1, xPos2, yPos1, yPos2;
        //random number will be chosen for foodChoice
        int foodChoice;

        //random number will be chosen for model
        int modelNum;

		//random number will be chosen for seat
		int seatNum;

		struct timespec custStart;
		struct timespec custPause;

		double startTime, pauseTime;

        bool inLine;
        bool inSeat;
        bool hasFood;
        bool isEating;
        bool finishFood;
		bool leave;
		bool assignSeat;
		bool moveToSeat;

	public:
		Customer();
		void reset();
		void setInLine(bool a);
		void setInSeat (bool a);
		void setHasFood (bool a);
		void setIsEating (bool a);
		void setFinishFood (bool a);
		void renderModel(bool &line, bool seat[]);
};

class Level
{
    private:
        int levelNum;
		int customerGoal;
        int serveCount;
		int custCount;
		double custMultiplier;
        bool start;
		bool complete;
		bool lineOccupied;
		bool seatOccupied[4];
		Customer *customers;

    public:
        Level();
		void makeNewLevel(int n);
		Customer getCustomer(int n);
		void setCustomerLeave(int n);
		bool checkLine();
		bool checkTables();
		void renderCustomers();
        void renderFood();
		void increaseServeCount();
		void setLine(bool a);
		bool getStart();
		void startGame(bool a);
		void printLine();
		void printSeat();
};
