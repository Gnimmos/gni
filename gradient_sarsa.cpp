#include "gradient_sarsa.h"


const std::vector<float> positions = {-1.0, -0.9f, -0.6f ,-0.3f, 0.0f, 0.3f,0.6f, 0.9f, 1.0};
const std::vector<float> angles = {-2.35f, -1.30f, -0.78f, -0.26f, 0.0f, 0.26f, 0.78f, 1.30f, 2.35f};
const std::vector<float> speeds = {-1.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};

const std::vector<float> accelaration = {0, 1};
const std::vector<float> steers = {-0.5, -0.2f, 0, 0.2f, 0.5};
const std::vector<float> brakes = {0, 1};

Sarsa::Sarsa()		
{
	State();
	Agent();
	Action();
	Weights();
	this->loadpolicy="Q.txt";
	this->savepolicy="Q.txt";

	this->counter = 0;

	
	std::cout<<"Sarsa initialized \n";

	
}
void Sarsa::create_states()
{
	std::vector<State> response;
	for(auto pos = positions.begin(); pos < positions.end(); ++pos)
	{
		for(auto ang = angles.begin(); ang < angles.end(); ++ang)
		{
			for(auto s = speeds.begin(); s < speeds.end(); ++s)
			{
				try
				{
					response.push_back(State(*pos, *ang, *s));
					std::cout<<"States are created:"<<*pos<<", "<<*ang<<", "<<*s<<", "<<response.size()<<" "<<"\n";
				}
				catch(const std::exception&)
				{

				}
			}
		}
	}
	this->all_states = response;

}
int Sarsa::StateisNow (float s, float l, float a)//return action to be tacen by gradient
{ 
	std::vector<State>::iterator find;
	find = std::find(all_states.begin(), all_states.end(), State(l, a, s));
	if (find != all_states.end())
		{   int x = find - all_states.begin() ;

			rewardfunction( all_states.at(x));
			return x;		
		}
		else
		{	
			std::cout<<"State not fount.\n";
			std::cout<<"Out of bounts\n";
			return 0;
		}

	}

	void Sarsa::create_actions()
	{
		std::vector<Action> response;
		for(auto st = steers.begin(); st < steers.end(); ++st)
		{
			for(auto acc = accelaration.begin(); acc < accelaration.end(); ++acc)
			{
				for(auto br = brakes.begin(); br < brakes.end(); ++br)
				{
					try
					{
						response.push_back(Action(*st, *acc, *br));
						std::cout<<"Actions are created:"<<*st<<", "<<*acc<<", "<<*br<<", "<<response.size()<<" "<<"\n";
					}
					catch(const std::exception&)
					{

					}
				}
			}
		}
		this->all_actions = response;
	}
//the action class will be proccessed in gradient for the action taken and furutre action and then go to the driver.
	Action Sarsa::doaction(int x)
	{
		int pos = PRNG();
		int vecpos;
		Weights w;
		Action tobetaken;
		float greedy = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if (greedy > egreedy)
		{
			std::vector<Weights>::iterator find;
			find = std::find(States_Actions_Weights.begin(), States_Actions_Weights.end(),Weights(x));
			vecpos = find - States_Actions_Weights.begin();
			if (find != States_Actions_Weights.end())
			{	


				std::cout<<"Exploiting =! \n";
				tobetaken = Sarsa::SelectMax(vecpos);
			}
			else
			{
				std::cout<<"Pair was not fount for some reason \n";
				tobetaken = all_actions.at(pos);

			}
		}

		else
		{
			std::cout<<"Exploring  =! \n";
			tobetaken = all_actions.at(pos);

		}


		all_actions_done.insert(all_actions_done.begin(),tobetaken);
		std::cout<<"inserting all_actions_done \n";
		return tobetaken;

	}
//need to impliment epsilon greedy to choose the wright actions.
	unsigned int PRNG()
	{
		static unsigned int seed = 5323;
		seed = (8253729 * seed + 2396403);
		return seed % 20;
	}

	void Sarsa::LoadPolicy()
	{
		std::string line;
		std::ifstream policy;
		std::cout<<"loadpolicy \n";
		policy.open(loadpolicy, ios_base::app);
		std::vector<float> State_action;
		if(!policy)
		{
			std::cout<<"Could not load policy\n";
		}
		else
		{
			if(policy.good())
			{
				Weights loadthem;
				std::istringstream in(line); 
				while(!policy.eof())
				{
					while(getline (policy,line,','))
					{
						std::string value;
						value = line;
					}

				}
			}
			else
			{
				std::cout<<"Cant access the file\n";
			}
		}
		policy.close();
	}

	void Sarsa::SavePolicy()
	{
		std::ofstream savepolicy;
		std::ifstream policy;
		std::cout<<"SavePolicy \n";
		savepolicy.open("Q.txt", ios_base::app);

		if(!savepolicy)
		{
			std::cout<<"Could not load policy\n";
		}
		else
		{
			if(savepolicy.good())
			{
				for ( auto i = 0 ; i <  States_Actions_Weights.size() ; i++ ) 
				{
					Weights savethem = States_Actions_Weights.at(i);
					savepolicy << std::fixed;
					savepolicy << std::setprecision(4);
					savepolicy<< savethem.pos <<"," << savethem.w0 <<"," << savethem.w1 <<"," << savethem.w2 <<"," << savethem.w3
					<<"," << savethem.w4 <<"," << savethem.w5 <<"," << savethem.w6 <<"," << savethem.w7 <<"," << savethem.w8 
					<<"," << savethem.w9;
					savepolicy<<"\n";
				}
			}
			else
			{
				std::cout<<"Cant access the file\n";
			}
		}


		savepolicy.close();

	}

	float Sarsa::rewardfunction(State s)
	{/*
		int laptime =  time.lastLapTime;
		if(laptime <= 60.0)
		{
			return 100.0f;
		}
		else{*/
	//if position out of bounts then exit gmae with reward -1
			if((s.get_pos()>=1.0)||(s.get_pos()<=-1.0))
			{
				return -50.0f;
			}
			else if (xy==0.0000f)
			{
				return 30.0f;
			}
			else
			{
		std::cout<<"xy: "<<xy<<std::endl;
		return 0.0f;
	}

}

//gets the possition of state and action, if its seen insert weights, else insert it
Action Sarsa::StateAndActions(int x)
{	Action tobedone = Sarsa::doaction(x);
	reward =  rewardfunction( all_states.at(x));
	//position of the state in the vector
	int a;
	float y = (float)(x);
	std::vector<Action>::iterator find;
	find = std::find(all_actions.begin(), all_actions.end(), Action(tobedone.ste(), tobedone.acc(), tobedone.bra()));
	if (find != all_actions.end())
	{	
		a = find - all_actions.begin();
	}
	Sarsa::updatez(x, a);
	std::cout<<"Size of ws "<<States_Actions_Weights.size()<<" Size of actions "<<all_actions_done.size()<<"\n";
	if (reward < 0.0f)
	{
		Sarsa::updateWeights(reward);
		Sarsa::SavePolicy();
		exit(1);
	}
	else if (reward > 0.0f)
	{
		Sarsa::updateWeights(reward);
	}
	else
	{
		std::cout<<"No reward found \n ";
	}
	return tobedone;
}

void Sarsa::updatez(int pos, int a)
{
	int vecpos;
	Weights f,w;
	Action Act_on = all_actions.at(a);
	std::cout<<" A for actions is "<<a<<" it should have been 0-19\n";

	f.pos = pos;
	std::vector<Weights>::iterator find;
	find = std::find(States_Actions_Weights.begin(), States_Actions_Weights.end(),f.pos);
	if (find != States_Actions_Weights.end())
	{	
		std::cout<<"Found it!!! \n";
		vecpos=find - States_Actions_Weights.begin();
		w = States_Actions_Weights.at(vecpos);
		if (Act_on.ste()==-0.5)
		{
			w.z1=w.z1+1;
			if (Act_on.acc()==0)
			{
				w.z6=w.z6+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z1,z6,z8  "<<w.z1<<" \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z1,z6,z9 \n";
				}
			}
			else if (Act_on.acc()==1)
			{
				w.z7=w.z7+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z1,z7,z8 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z1,z7,z9 \n";
				}
			}
		}
		else if (Act_on.ste()== -0.2f)
		{
			w.z2=w.z2+1;
			if (Act_on.acc()==0)
			{
				w.z6=w.z6+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z2,z6,z8 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z2,z6,z9 \n";

				}
			}
			else if (Act_on.acc()==1)
			{
				w.z7=w.z7+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z2,z7,z8 \n";

				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z2,z7,z9 \n";

				}
			}
		}
		else if (Act_on.ste()==0)
		{
			w.z3=w.z3+1;
			if (Act_on.acc()==0)
			{
				w.z6=w.z6+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z3,z6,z8 \n";

				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z3,z6,z9 \n";
				}
			}
			else if (Act_on.acc()==1)
			{
				w.z7=w.z7+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z3,z7,z8 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z3,z7,z9 \n";
				}
			}
		}
		else if (Act_on.ste()== 0.2f)
		{
			w.z4=w.z4+1;
			if (Act_on.acc()==0)
			{
				w.z6=w.z6+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z4,z6,z8 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z4,z6,z9 \n";
				}
			}
			else if (Act_on.acc()==1)
			{
				w.z7=w.z7+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z4,z7,z8 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z4,z7,z9 \n";
				}
			}
		}
		else if (Act_on.ste()==0.5)
		{
			w.z5=w.z5+1;
			if (Act_on.acc()==0)
			{
				w.z6=w.z6+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z5 1 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z5 2 \n";
				}
			}
			else if (Act_on.acc()==1)
			{
				w.z7=w.z7+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z5 3 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z5 4\n";
				}
				else
				{	
					std::cout<<"Did not found it in vector \n \n \n ";

				}
			}



			States_Actions_Weights.erase(States_Actions_Weights.begin() + vecpos);
			States_Actions_Weights.insert(States_Actions_Weights.begin(),w);
		}
		else
		{
			std::cout<<"Something went wrong \n \n \n ";

		}
		std::cout<<"End of  \n \n \n ";
	}
	else
	{
		std::cout<<"Inserting !!! \n";
		Act_on = all_actions.at(a);
		w.pos = pos;
		if (Act_on.ste()==-0.5)
		{
			w.z1=w.z1+1;
			if (Act_on.acc()==0)
			{
				w.z6=w.z6+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z1 : "<<w.z1<<" \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z1 \n";
				}
			}
			else if (Act_on.acc()==1)
			{
				w.z7=w.z7+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z1 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z1 \n";
				}
			}
		}
		else if (Act_on.ste()==-0.2f)
		{
			w.z2=w.z2+1;
			if (Act_on.acc()==0)
			{
				w.z6=w.z6+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z2 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z2 \n";

				}
			}
			else if (Act_on.acc()==1)
			{
				w.z7=w.z7+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z2 \n";

				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z2 \n";

				}
			}
		}
		else if (Act_on.ste()==0)
		{
			w.z3=w.z3+1;
			if (Act_on.acc()==0)
			{
				w.z6=w.z6+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z3 \n";

				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z3 \n";
				}
			}
			else if (Act_on.acc()==1)
			{
				w.z7=w.z7+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z3 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z3 \n";
				}
			}
		}
		else if (Act_on.ste()==0.2f)
		{
			w.z4=w.z4+1;
			if (Act_on.acc()==0)
			{
				w.z6=w.z6+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z4 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z4 \n";
				}
			}
			else if (Act_on.acc()==1)
			{
				w.z7=w.z7+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z4 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z4 \n";
				}
			}
		}
		else if (Act_on.ste()==0.5)
		{
			w.z5=w.z5+1;
			if (Act_on.acc()==0)
			{
				w.z6=w.z6+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z5 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z5 \n";
				}
			}
			else if (Act_on.acc()==1)
			{
				w.z7=w.z7+1;
				if (Act_on.bra()==0)
				{
					w.z8=w.z8+1;
					std::cout<<"I am z5 \n";
				}
				else if (Act_on.bra()==1)
				{
					w.z9=w.z9+1;
					std::cout<<"I am z5 \n";
				}
			}

			States_Actions_Weights.insert(States_Actions_Weights.begin(),w);
		}
	}
	std::cout<<"End of checking z \n"<<"\n"<<"\n";
}


Action Sarsa::SelectMax( int StatePos)
{
	Weights w = States_Actions_Weights.at(StatePos);
	float bestste=w.w1;
	float lowste=w.w2;
	if (Sarsa::Max(bestste, lowste))
	{
		lowste = w.w3;
		if(Sarsa::Max(bestste, lowste))
		{
			lowste = w.w4;
			if(Sarsa::Max(bestste, lowste))
			{
				lowste =w.w5;
				if(Sarsa::Max(bestste, lowste))
				{
					bestste = w.w1;
				}
				else
				{
					bestste = w.w5;
				}
			}
			else
			{
				bestste = w.w4;
			}
		}
		else
		{
			bestste = w.w3;
		}
	}
	else
	{
		bestste = w.w2;
	}
	float bestacc=w.w6;
	float lowacc=w.w7;
	if(Max(bestacc,lowacc))
	{
		bestacc = w.w6;
	}
	else
	{
		bestacc = w.w7;
	}
	float bestbr=w.w8;
	float lowbr=w.w9;
	if(Max(bestacc,lowacc))
	{
		bestbr = w.w8;
	}
	else
	{
		lowbr = w.w9;
	}

	std::vector<Action>::iterator find;
	find = std::find(all_actions.begin(), all_actions.end(), Action(bestste, bestacc, bestbr));
	if (find != all_actions.end())
		{   int x = find - all_actions.begin();
			Action best;
			best = all_actions.at(x);
			std::cout<<"I am in best action \n";
			return best;
		}
}

	bool Sarsa::Max(float max,float min)
	{
		if (max>=min)
		{
			return  true; 
		}
		else
		{
			return false;
		}
	}

	float Sarsa::getSteerWeights(int a)
	{	
		std::cout<<"I am in getSteerWeights \n";

		Action steerweight = all_actions_done.at(a);
		Weights wsteer = States_Actions_Weights.at(a);
		if (steerweight.ste() == -0.5)
		{
			return wsteer.w1;
		}
		else if (steerweight.ste() == -0.2f)
		{
			return wsteer.w2;
		}
		else 	if (steerweight.ste() == 0.0)
		{
			return wsteer.w3;
		}
		else if (steerweight.ste() == 0.2f)
		{
			return wsteer.w4;
		}
		else 	if (steerweight.ste() == 0.5)
		{
			return wsteer.w5;
		}
		else 
		{
			std::runtime_error("unexpected end of action");
		}

	}

	float Sarsa::getAccelarationWeights(int a)
	{	
		std::cout<<"I am in getAccelarationWeights \n";

		Action steerweight = all_actions_done.at(a);
		Weights wsteer = States_Actions_Weights.at(a);
		if (steerweight.acc() == 0)
		{
			return wsteer.w6;
		}
		else if (steerweight.acc() == 1)
		{
			return wsteer.w7;
		}
		else 
		{
			std::runtime_error("unexpected end of action");
		}
	}
	float Sarsa::getSBreakWeights(int a)
	{	
		std::cout<<"I am in getSBreakWeights \n";

		Action steerweight = all_actions_done.at(a);
		Weights wsteer = States_Actions_Weights.at(a);
		if (steerweight.bra() == 0)
		{
			return wsteer.w8;
		}
		else if (steerweight.bra() == 1)
		{
			return wsteer.w9;
		}
		else 
		{
			std::runtime_error("unexpected end of action");
		}

	}
	float Sarsa::getSteerZeta(int a)
	{	
		std::cout<<"I am in getSteerZetass \n";

		Action steerzt = all_actions_done.at(a);
		Weights zsteer = States_Actions_Weights.at(a);
		if (steerzt.ste() == -0.5)
		{
			return zsteer.z1;
		}
		else if (steerzt.ste() == -0.2f)
		{
			return zsteer.z2;
		}
		else 	if (steerzt.ste() == 0.0)
		{
			return zsteer.z3;
		}
		else if (steerzt.ste() == 0.2f)
		{
			return zsteer.z4;
		}
		else 	if (steerzt.ste() == 0.5)
		{
			return zsteer.z5;
		}
		else 
		{
			std::runtime_error("unexpected end of action");
		}

	}

	float Sarsa::getAccelarationZeta(int a)
	{	
		std::cout<<"I am in getAccelarationZetas \n";

		Action steerzt = all_actions_done.at(a);
		Weights zsteer = States_Actions_Weights.at(a);
		if (steerzt.acc() == 0)
		{
			return zsteer.z6;
		}
		else if (steerzt.acc() == 1)
		{
			return zsteer.z7;
		}
		else 
		{
			std::runtime_error("unexpected end of action");
		}
	}
	float Sarsa::getSBreakZeta(int a)
	{	
		std::cout<<"I am in getSBreakZetas \n";

		Action zsteer = all_actions_done.at(a);
		Weights steerzt = States_Actions_Weights.at(a);
		if (zsteer.bra() == 0)
		{
			return steerzt.z8;
		}
		else if (zsteer.bra() == 1)
		{
			return steerzt.z9;
		}
		else 
		{
			std::runtime_error("unexpected end of action");
		}

	}
	void Sarsa::UpdateWeightst(float up)
	{
		std::cout<<"I am UpdatingSteeringweight \n";

		Action steerzt = all_actions_done.at(counter);
		Weights wsteer = States_Actions_Weights.at(counter);
		if (steerzt.ste() == -0.5)
		{
			if(wsteer.w1 <= up)
			{
				wsteer.w1 = up;
			}
		}
		else if (steerzt.ste() == -0.2f)
		{
			if(wsteer.w2 <= up)
			{
				wsteer.w2 = up;
			}
		}
		else if (steerzt.ste() == 0.0)
		{
			if(wsteer.w3 <= up)
			{
				wsteer.w3 = up;
			}
		}
		else if (steerzt.ste() == 0.2f)
		{
			if(wsteer.w4 <= up)
			{
				wsteer.w4 = up;
			}
		}
		else if (steerzt.ste() == 0.5)
		{
			if(wsteer.w5 <= up)
			{
				wsteer.w5 = up;
			}
		}
		else 
		{
			std::runtime_error("unexpected end of action");
		}
		States_Actions_Weights.at(counter) = wsteer;

	}
	void Sarsa::UpdateWeightAcc(float up)
	{
		std::cout<<"I am in getAccelarationZetas \n";

		Action steerzt = all_actions_done.at(counter);
		Weights wsteer = States_Actions_Weights.at(counter);
		if (steerzt.acc() == 0)
		{
			if(wsteer.w6 <= up)
			{
				wsteer.w6 = up;
			}
		}
		else if (steerzt.acc() == 1)
		{
			if(wsteer.w7 <= up)
			{
				wsteer.w7 = up;
			}
		}
		else 
		{
			std::runtime_error("unexpected end of action");
		}	
		States_Actions_Weights.at(counter) = wsteer;

	}
	void Sarsa::UpdateWeightBr(float up)
	{
		std::cout<<"I am in getSBreakZetas \n";

		
		Action steerzt = all_actions_done.at(counter);
		Weights wsteer = States_Actions_Weights.at(counter);
		if (steerzt.bra() == 0)
		{
			if(wsteer.w8 <= up)
			{
				wsteer.w8 = up;
			}
		}
		else if (steerzt.bra() == 1)
		{
			if(wsteer.w9 <= up)
			{
				wsteer.w9 = up;
			}
		}
		else 
		{
			std::runtime_error("unexpected end of action");
		}
		States_Actions_Weights.at(counter) = wsteer;

	}

	/*****************************************************************************************************************************
	******************************************************RECURTION HERE**********************************************************
	******************************************************************************************************************************/
	float Sarsa::updateWeights(float rewards)
	{
		
		std::cout<<"I am in update \n";
		float delta;
		float w0count, w1count, w2count, w3count, z1count, z2count, z3count;
		float zetaena;
		float Qvalue;
		Weights weight;
		Action done;
		done = all_actions_done.at(counter);
		weight = States_Actions_Weights.at(counter);

		std::cout<<"weights and zeta from actions.\n"; 
		w0count = weight.w0;
		w1count = Sarsa::getSteerWeights(counter);
		w2count = Sarsa::getAccelarationWeights(counter);
		w3count = Sarsa::getSBreakWeights(counter);
		z1count = Sarsa::getSteerZeta(counter);
		z2count = Sarsa::getAccelarationZeta(counter);
		z3count = Sarsa::getSBreakZeta(counter);

		z1count = z1count * gamma * lamda;
		z2count = z2count * gamma * lamda;
		z3count = z3count * gamma * lamda;
		std::cout<<" Counter "<<counter<<" \n ";
		Qvalue = (w0count + w1count*done.ste() + w2count*done.acc() + w3count*done.bra());
		delta = rewards - Qvalue;
		if((States_Actions_Weights.size()-1>counter))//&&(counter<50))
		{
			counter++;
			
			delta = delta + gamma * Sarsa::updateWeights(rewards);
		}
		std::cout<<"Out of recursion \n"; 
		w1count = w1count + alpha * delta * z1count;
		w2count = w2count + alpha * delta * z2count;
		w3count = w3count + alpha * delta * z3count;
		Sarsa::UpdateWeightst(w1count);
		Sarsa::UpdateWeightAcc(w2count);
		Sarsa::UpdateWeightBr(w3count);
		counter--;
		return Qvalue;

	}
	




// as the algorithm progresses states and actions are insterted in vector State_Action now  the weights need to be added







/*--------------------------------------------------FAILED-----------------------------------------
//returns the possition and the values of action in floationg points
std::vector<float> Sarsa::ActionWeights(Action a)
{
	int x;
	std::vector<Action>::iterator find;
	find = std::find(all_actions.begin(), all_actions.end(), Action(a.ste(), a.acc(), a.bra()));
		if (find != all_actions.end())
		{	
			x = find - all_actions.begin();
			std::cout<<"Action found: "<<x<<"\n";
		}
		else
		{
			std::cout<<"Action not fount.\n";
		}
	float y = (float)(x);
	std::vector<float> ActionW;
	ActionW = {y, a.ste(), a.acc(), a.bra()};
	std::cout<<"The Action is: "<<ActionW.at(0)<<" "<<ActionW.at(1)<<" "<<ActionW.at(2)<<" "<<ActionW.at(3)<<std::endl;
	ActionsPos.insert( ActionsPos.end(), ActionW.begin(), ActionW.end());
	return ActionW;   

}


void Sarsa::AddStateAction(std::vector<float> statess)
{

Action tobedone = Sarsa::doaction();
std::vector<float> act = Sarsa::ActionWeights(tobedone);
std::vector<float> st = statess;
std::vector<float> response;
for(auto sta = st.begin(); sta < st.end(); ++sta)
	{
		for(auto ac = act.begin(); ac < act.end(); ++ac)
			{
				for(auto w = weights.begin(); w < weights.end(); ++w)
					{
						response.push_back(std::vector<float> (sta,ac, w));
					}
			}
	}
this->state_action_weights = response;

}
*/
/*
typedef std::vector< std::vector<float> >::iterator iter;
  for ( iter it = States_Actions.begin(), end = States_Actions.end(); it != end ; ++it )
  {
  	  typedef std::vector<int>::iterator iter2;
        inline iter2 found = std::find((*it).begin(), (*it).end(), ToFind);
        if ( found != it->end()) 
        {
            std::cout << "row "   << (it - States_Actions.begin())  << ", col " << (found - (*it).begin()) << '\n';
        }
        else
        {
			std::cout << "Not found \n";
			States_Actions.insert(States_Actions.end(),State_action.begin(),State_action.end());
        }
  }
*/   

/*
	if(Sarsa::IsStateActionSeen(x,a))
	{
		std::cout<<"Action found: "<<"\n";
	}
	else
	{
		StateA= {(float)(x),(float)(a)};
		States_Actions.insert(States_Actions.end(),StateA.begin(), StateA.end());
		std::cout<<"Inserting state: "<<x<<" and action "<<a<<" \n";
		State_action={(float)(x),(float)(a),w0,w1,w2,w3,w4,w5,w6};
		//this->state_action_weights = State_action;
	//	S_A_W.push_back(state_action_weights);
	}
	StateA= {(float)(x),(float)(a)};
	if (does_exist(S_A_W,(float)(x),(float)(a)))
	{
		cout<<"FOUND IT!!!!! \n";
	}
	else
	{
		this->state_action_weights = State_action;
		S_A_W.push_back(state_action_weights);
	}



return tobedone;
}
//checks is the values exists in the vector of seen state and actions
bool Sarsa::IsStateActionSeen(int st, int y)//x is state and y is action too many abriviations..
{	
//The position of state and action in their respected vectors
State IsNow = all_states.at(st);
Action ToBeDone = all_actions.at(y);
std::cout<<"The State is: "<<IsNow.get_pos()<<" "<<IsNow.get_ang()<<" "<<IsNow.get_spe()<<std::endl;
std::cout<<"The Action is: "<<ToBeDone.ste()<<" "<<ToBeDone.acc()<<" "<<ToBeDone.bra()<<std::endl;
//create a vector with values of both current state and action

std::vector<float> ToFind;

ToFind={(float)(st),(float)(y)};
 
//read the state actions from vector and check if they are seen, if not insert them.
	auto it = std::search(States_Actions.begin(), States_Actions.end(), ToFind.begin(), ToFind.end());
		if (it != States_Actions.end())
		{		
			return true;
		}
		else
		{
			std::cout<<"Action not fount.\n";
			return false;
			// Sarsa::LoadPolicy();
		}
}
bool Sarsa::does_exist(const vector< vector<float> >&  v, float item, float item2){

     vector< vector<float> >::const_iterator row;

    for (row = v.begin(); row != v.end(); row++) 
    {
        if((find(row->begin(), row->end(), item) != row->end() )&& (find(row->begin(), row->end(), item2) != row->end()))

        {
        	//std::cout<<row; 
        	return true;
        }
    }

    return false;
}
*/

