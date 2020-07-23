#ifndef _QLCORE_
#define _QLCORE_

#include <vector>
#include <string>
#include "action.h"
//ALL states
/*
const std::vector<float> positions = {-1.0, -0.9f, -0.6f, -0.3f, 0.0f, 0.3f,0.6f, 0.9f,1.0};
const std::vector<float> angles = {-2.35f, -1.30f, -0.78f, -0.26f, 0.0f, 0.26f, 0.78f, 1.30f, 2.35f};
const std::vector<float> speeds = {-1.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
//ALL actions
const std::vector<float> accelaration = {0, 1};
const std::vector<float> steers = {-0.5, -0.2f, 0, 0.2f, 0,5};
const std::vector<float> brakes = {0, 1};
*/
class State
{
public:

	State():position(NULL),angle(NULL),speed(NULL){}

	State(float position, float angle, float speed)
		: position(position)
		, angle(angle)
		, speed(speed)

	{
	

	}

	float get_pos()
	{
		return position;
	}
	float get_ang()
	{
		return angle;
	}
	float get_spe()
	{
		return speed;
	}
 inline bool operator==(const State& other)
 {
 		
		if(position != other.position)
		{
			return false;
		}
		if(angle != other.angle)
		{
			return false;
		}
		if(speed != other.speed)
		{
			return false;
		}
		return true;
}


protected: 
	void set_pos(float& pos);
	void set_ang(float& angle);
	void set_spe(float& speed);

private:
	float position;
	float angle;
	float speed;
	
};

class Weights
{
public:
	Weights(){}
	Weights(int st)
	{
	this->pos=st;
	this->w0=0.2f;
	this->w1=0.2f;
	this->w2=0.2f;
	this->w3=0.2f;
	this->w4=0.2f;
	this->w5=0.2f;
	this->w6=0.2f;
	this->w7=0.2f;
	this->w8=0.2f;
	this->w9=0.2f;
	

	this->z1=0;
	this->z2=0;
	this->z3=0;
	this->z4=0;
	this->z5=0;
	this->z6=0;
	this->z7=0;
	this->z8=0;
	this->z9=0;
	}	
	Weights(float w0,float w1,float w2,float w3,float w4,float w5,float w6,float w7, float w8, float w9)
	{
	}
	int pos;
	float w0,w1,w2,w3,w4,w5,w6,w7,w8,w9;
	float z0,z1,z2,z3,z4,z5,z6,z7,z8,z9;


	inline bool operator==(const Weights& other)
	{
	 	if(pos != other.pos)
		{
			return false;
		}
		/*
		if(w0 != other.w0)
		{
			return false;
		}
		if(w1 != other.w1)
		{
			return false;
		}
		if(w2 != other.w2)
		{
			return false;
		}
		if(w3 != other.w3)
		{
			return false;
		}
		if(w4 != other.w5)
		{
			return false;
		}
		if(w5 != other.w5)
		{
			return false;
		}
		if(w6 != other.w6)
		{
			return false;
		}
		if(w7 != other.w7)
		{
			return false;
		}
		if(w8 != other.w8)
		{
			return false;
		}
		if(w9 != other.w9)
		{
			return false;
		}
		if(w10 != other.w10)
		{
			return false;
		}
		if(z1 != other.z1)
		{
			return false;
		}
		if(z2 != other.z2)
		{
			return false;
		}
		if(z3 != other.z3)
		{
			return false;
		}
 		if(z4 != other.z5)
		{
			return false;
		}
		if(z5 != other.z5)
		{
			return false;
		}
		if(z6 != other.z6)
		{
			return false;
		}
		if(z7 != other.z7)
		{
			return false;
		}
		if(z8 != other.z8)
		{
			return false;
		}
		if(z9 != other.z9)
		{
			return false;
		}
		*/
		return true;
	}
};

#endif
