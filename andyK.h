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

        bool inLine;
        bool inSeat;
        bool hasFood;
        bool isEating;
        bool finishFood;

	public:
		Customer();
		void setInLine(bool a); 
		void setInSeat (bool a); 
		void setHasFood (bool a);
		void setIsEating (bool a);
		void setFinishFood (bool a);
		void renderModel();
};
