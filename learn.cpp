#include "learn.h"


float Learn::getLocation(float pos)
{
	float possition = pos;
	normLocation(possition);
	return possition;
}
float Learn::getAngle(float r)
{
	float angleinr = r;
	normAngle(angleinr);
	return angleinr;
}
float Learn::getSpeed(float x)
{	float speed = x;
	normLongx(speed);
	return speed;
}
void Learn::normLocation(float &x)
{
	if ((x >= -1.0f) && (x < -0.8f))
	{

		x = -0.9f;
	} else if ((x >= -0.80f) && (x < -0.50f))
	{
		x = -0.6f;

	} else if ((x >= -0.50f) && (x < -0.20f))
	{
		x = -0.3f;

	} else if ((x >= -0.20f) && (x <= 0.20f))
	{
		x = 0.0f;

	} else if ((x > 0.20f) && (x <= 0.50f))
	{
		x = 0.3f;

	} else if ((x > 0.50f) && (x <= 0.80f))
	{
		x = 0.6f;

	} else if ((x > 0.80f) && (x <= 1.00f))
	{
		x = 0.9f;

	} else if (x < -1.00f)
	{
		x = -1.5f;

	} else if (x>1.00f)
	{
		x = 1.5f;

	}

}


void Learn::normAngle(float &r)
{
	if ((r <= 0.01f) && (r >= -0.1f))
	{
		r = 0.00f;

	} else if ((r > 0.01f) && (r <= 0.523f)) //between 0,30 degrees
	{
		r = 0.26f;

	} else if ((r > 0.523f) && (r <= 1.047f)) //between 30,60 degrees
	{
		r = 0.78f;

	} else if ((r > 1.047f) && (r <= 1.570f)) //between 60,90
	{
		r = 1.30f;

	} else if ((r > 1.570f) && (r <= 3.141f)) //between 90,180
	{
		r = 2.35f;

	} else if ((r < -0.1f) && (r >= -0.523f))
	{
		r = -0.26f;

	} else if ((r < -0.523f) && (r >= -1.047f))
	{
		r = -0.78f;

	} else if ((r < -1.047f) && (r >= -1.570f))
	{
		r = -1.30f;

	} else if ((r < -1.570f) && (r >= -3.141f))
	{
		r = -2.35f;

	}

}
void Learn::normLongx(float &x)
{
	if (x < 0.0f)
	{
		x = -1.0f;
	} else if (x == 0.0f)
	{
		x = 0.0f;
	} else if ((x > 0.00f) && (x <= 60.00f))
	{
		x = 1.0f;
	} else if ((x > 60.00f) && (x <= 120.00f))
	{
		x = 2.0f;
	} else if ((x > 120.00f) && (x <= 180.00f))
	{
		x = 3.0f;
	} else if ((x > 180.00f) && (x <= 240.00f))
	{
		x = 4.0f;
	} else if ((x > 240.00f) && (x <= 300.00f))
	{
		x = 5.0f;
	} else
	{
		x = 6.0f;
	}
}