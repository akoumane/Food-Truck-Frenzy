void makeFoods();
void makeCustomers();
void renderCustomers();
void renderFoods();
void makeNumbers();
unsigned char *buildAlphaData2(Ppmimage *img, unsigned char col[3]);

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
		bool startTimer;

	public:
		Customer();
		void reset();
		void setInLine(bool a);
		void setInSeat (bool a);
		void setHasFood (bool a);
		void setIsEating (bool a);
		void setFinishFood (bool a);
		void addPauseTotal(double a);
		void renderModel(bool &line, bool seat[], int &count);
		void renderThoughtBox();
		int returnSeat();
		int returnFood();
};

class Level
{
	private:
		int levelNum;
		int customerGoal;
		int serveCount;
		int custCount;
		double custMultiplier;
		double gameLength;
		double pauseTotal;
		bool start;
		bool complete;
		bool gameOver;
		bool win;
		bool lineOccupied;
		bool seatOccupied[4];
		bool startPauseTimer;
		bool startCountdownTimer;
		bool addTime;

		struct timespec pauseStart;
		struct timespec pauseEnd;
		struct timespec countdownStart;
		struct timespec countdownEnd;

		double pauseStartTime, pauseEndTime, pauseWaitTime;
		double countdownStartTime, countdownEndTime;

		Customer *customers;

	public:
		Level();
		void makeNewLevel(int n);
		void startGame();
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
		void renderCountdown();
		void renderServeCounter();
		void setHasFood(int n);
		void setComplete(bool a);
		void setGameOver(bool a);
		int getServeCount();
		void setWin(bool a);
		bool getWin();
		int getCustomerGoal();
		bool getComplete();
		bool getGameOver();
		int getSeatNum(int n);
		int getFoodId(int n);
};
