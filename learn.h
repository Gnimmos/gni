#ifndef _LEARN_
#define _LEARN_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#ifdef USE_GNI_NAMESPACE
namespace gni
{
#endif

using namespace std;

class Learn {
public:
	//~Learn();
	float getLocation(float pos);
	float getAngle(float r);
	float getSpeed(float x);

private:
	//float  location [10] = { -1.5, -0.9, -0.7, -0.5, -0.3, 0.0, 0.3, 0.5, 0.7, 0.9, 1.5};
	//float  radius [11] = {0.0 , 30.0, 60.0, 90.0, 120.0, 150.0, 180.0, 210.0, 240.0, 270.0, 300.0, 330.0};
	//float  speed [8] = { -10.0, 0.0, 30.0, 90.0, 150.0, 210.0, 270.0, 330.0, 360.0};

	void normLocation(float &x);
	void normAngle(float &r);
	void normLongx(float &x);
};


#ifdef USE_GNI_NAMESPACE
}
#endif

#endif //_SEGLEARN_H_