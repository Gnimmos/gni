#ifndef _Action_
#define _Action_



class Action
{
public:
	Action(){}
	Action(float steer, float acceletate, float brake):steer(steer), acceletate(acceletate),brake(brake)

	{

	}
	void set_ste(float& steer);
	void set_acc(float& accel);
	void set_bra(float& brake);


	float ste()
	{
		return steer;
	}
	float acc()
	{
		return acceletate;
	}
	float bra()
	{
		return brake;
	}

	inline bool operator==(const Action& other)
 	{
 		
		if(steer != other.steer)
		{
			return false;
		}
		if(acceletate != other.acceletate)
		{
			return false;
		}
		if(brake != other.brake)
		{
			return false;
		}
		return true;
	}


protected:

private:
	float steer;
	float acceletate;
	float brake;
	 
};

class Agent
{
public:
	Agent(){}
	~Agent(){}
	//void loadpolicy();
	//void savepolicy();

};


#endif