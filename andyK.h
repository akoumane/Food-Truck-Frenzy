void makeCustomers();
void renderCustomers();
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
		double pauseStartTime, pauseEndTime, pauseWaitTime;
		double countdownStartTime, countdownEndTime;
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

		Customer *customers;

	public:
		Level();
		Customer getCustomer(int n);
		
		void makeNewLevel(int n);
		void startGame();
		void setCustomerLeave(int n);
		void renderCustomers();
		void renderFood();
		void increaseServeCount();
		void setLine(bool a);
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
		void setWin(bool a);
		
		bool checkLine();
		bool checkTables();
		bool getStart();
		bool getWin();
		bool getComplete();
		bool getGameOver();
		
		int getServeCount();
		int getCustomerGoal();
		int getSeatNum(int n);
		int getFoodId(int n);
};
