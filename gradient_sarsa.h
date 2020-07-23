#ifndef _GRADIENT_
#define _GRADIENT_

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <math.h>
#include <float.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <iostream> 
#include <vector>
#include <iterator>
#include <cstddef>
#include <vector> 
#include <algorithm>
#include <sys/stat.h>
#include <iomanip>

#include <tgf.h>
#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robottools.h>
#include <robot.h>

#include "core.h"



using namespace std;

extern float xy;
unsigned int PRNG();


class Sarsa:virtual public State, virtual public Action,public Weights, public Agent {
	public:

		Sarsa();

		Sarsa(bool l, std::string load, std::string save);

		std::string loadpolicy; //load current policy
		std::string savepolicy; //save best policy 

		//fill the vectors with the values
		void create_states();
		void create_actions();
		
		//probability of greedy action
		float prob();

		//read state and do action and get reward
		int StateisNow (float s, float l, float a);
		Action doaction(int xy);
		float rewardfunction(State s);


		//open file 
		void LoadPolicy();
		void SavePolicy();
		
		//sarsa credentials
		void  greedy(float e );
		void learning(float a);
		void discount(float g);
		//combine state and action and weights 
		Action StateAndActions(int x);

		//from update or create Weight
		void updatez(int pos, int a);
		//best action selection

		bool Max(float max,float min);
		Action SelectMax( int StatePos);

		//get weights from vector States_Actions_Weights
		float getSteerWeights(int  a);
		float getAccelarationWeights(int a);
		float getSBreakWeights(int a);

		//get Zeta from vector States_Actions_Weights
		float getSteerZeta(int  a);
		float getAccelarationZeta(int a);
		float getSBreakZeta(int a);

		// Update weights
		float updateWeights(float rewards);

		void UpdateWeightst(float a);
		void UpdateWeightAcc(float a);
		void UpdateWeightBr(float a);



	protected:
		std::vector<State> all_states;
		std::vector<Action> all_actions;
		std::vector<Action> all_actions_done;
		std::vector<Weights> States_Actions_Weights;
	private:
		const float egreedy = 0.5f; //epsilon greedy
		const float alpha = 0.4f; //learning rate
		const float gamma = 0.3f; // discount rate
		const float lamda = 0.8f;

		float normspeed;//normilized speed
		float normlocation;//normimized location
		float normangle;//normilized angle
		
		int counter;

		float reward;
	

		//sensor for lap
		tCarRaceInfo time;
};




#endif