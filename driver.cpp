/***************************************************************************

    file                 : driver.cpp
    created              : Thu Dec 20 01:21:49 CET 2002
    copyright            : (C) 2002 Bernhard Wymann

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "driver.h"
#include "gradient_sarsa.h"

const float Driver::MAX_UNSTUCK_ANGLE = 15.0 / 180.0 * PI;		/* [radians] */
const float Driver::UNSTUCK_TIME_LIMIT = 2.0;				/* [s] */
const float Driver::MAX_UNSTUCK_SPEED = 5.0;				/* [m/s] */
const float Driver::MIN_UNSTUCK_DIST = 3.0;					/* [m] */
const float Driver::G = 9.81;								/* [m/(s*s)] */
const float Driver::FULL_ACCEL_MARGIN = 1.0;				/* [m/s] */
const float Driver::SHIFT = 0.9;							/* [-] (% of rpmredline) */
const float Driver::SHIFT_MARGIN = 4.0;						/* [m/s] */
const float Driver::ABS_SLIP = 0.9;							/* [-] range [0.95..0.3] */
const float Driver::ABS_MINSPEED = 3.0;						/* [m/s] */
const float Driver::TCL_SLIP = 0.9;							/* [-] range [0.95..0.3] */
const float Driver::TCL_MINSPEED = 3.0;						/* [m/s] */
const float Driver::LOOKAHEAD_CONST = 17.0;					/* [m] */
const float Driver::LOOKAHEAD_FACTOR = 0.33;				/* [-] */
const float Driver::WIDTHDIV = 4.0;							/* [-] */
float xy=0.001f;
//float xyc=0.001f;
//unsigned int PRNG();
int counter = 0;
Driver::Driver(int index)
{
	INDEX = index;
	
	/* Called for every track change or new race. */
}
 Driver::~Driver()
{
}
void Driver::initTrack(tTrack* t, void *carHandle, void **carParmHandle, tSituation *s)
{
	track = t;
	std::cout<<"The maps is : "<<t <<"\n";
	*carParmHandle = NULL;
	gr.create_states();
	gr.create_actions();
	gr.LoadPolicy();
	
}

/* Start a new race. */
void Driver::newRace(tCarElt* car, tSituation *s)
{
	MAX_UNSTUCK_COUNT = int(UNSTUCK_TIME_LIMIT / RCM_MAX_DT_ROBOTS);
	stuck = 0;
	this->car = car;
	

	//loader.initializer();
	
}


/* Drive during race. */
void Driver::drive(tSituation *s)
{
	doit = update(s);
	 xy= getDistToSegEnd();

	 counter++;

			car->ctrl.steer = doit.ste();//get steer;
			car->ctrl.gear = getGear();//gear chances autonomus  
			car->ctrl.brakeCmd = doit.bra();//get breaks;
			if (car->ctrl.brakeCmd == 0.0) {
				car->ctrl.accelCmd = doit.acc();//get accelaration;
			} else {
				car->ctrl.accelCmd = 0.0;
			}
			if (counter == 100)
			{
				gr.SavePolicy();
			}	
//		} 
}

/* Set pitstop commands. */
int Driver::pitCommand(tSituation *s)
{
	return ROB_PIT_IM; /* return immediately */
}


/* End of the current race */
void Driver::endRace(tSituation *s)
{
	gr.SavePolicy();
}


/***************************************************************************
 *
 * utility functions
 *
***************************************************************************/



/* Compute the length to the end of the segment */
float Driver::getDistToSegEnd()
{

		return car->_trkPos.seg->length - car->_trkPos.toStart;
	
}




/* Compute gear */
int Driver::getGear()
{
	if (car->_gear <= 0) return 1;
	float gr_up = car->_gearRatio[car->_gear + car->_gearOffset];
	float omega = car->_enginerpmRedLine / gr_up;
	float wr = car->_wheelRadius(2);

	if (omega * wr * SHIFT < car->_speed_x) {
		return car->_gear + 1;
	} else {
		float gr_down = car->_gearRatio[car->_gear + car->_gearOffset - 1];
		omega = car->_enginerpmRedLine / gr_down;
		if (car->_gear > 1 && omega * wr * SHIFT > car->_speed_x + SHIFT_MARGIN) {
			return car->_gear - 1;
		}
	}
	return car->_gear;
}





/* Update my private data every timestep */
Action Driver::update(tSituation *s)
{

	tTrackSeg* seg = car->_trkPos.seg;
	trackangle = RtTrackSideTgAngleL(&(car->_trkPos));
	angle = trackangle - car->_yaw;
	NORM_PI_PI(angle);
	int statess;
	float currentspeed = car->_speed_x * 3.5983f;//normilize to feet the descrite
	float w = seg->width;
	float pos =  car->_trkPos.toMiddle  * 0.20f;
	carangle = newlearn.getAngle(angle);
	carspeed = newlearn.getSpeed(currentspeed);
	carlocation = newlearn.getLocation(pos);
	statess = gr.StateisNow(carspeed, carlocation, carangle);
	Action act =gr.StateAndActions(statess);

	mass = CARMASS + car->_fuel;
	return act;
}
