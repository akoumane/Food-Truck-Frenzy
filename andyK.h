void makeCustomers();
void makeFoods();
void renderCustomers();
void renderFoods();
void makeNumbers();

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
		struct timespec custCurrent;

		double waitTime, startTime, currentTime, pauseTotal;

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
		void addPauseTotal(double a);
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
		bool startTimer;
		bool addTime;
		
		struct timespec pauseStart;
		struct timespec pauseEnd;

		double pauseStartTime, pauseEndTime, pauseWaitTime;

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
		void setStartTimer(bool a);
		void addPauseTotal();
		void calcPauseTime();
		void renderNumbers();
};
