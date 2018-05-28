// this whole approach is realy weird

#include <iostream>
using namespace std;

class LightSwitch;

struct State
{
	/// not a pure virtual function
	virtual void on(LightSwitch* ls)
	{
		cout << "Ligh is already on\n";
	}
	virtual void off(LightSwitch* ls)
	{
		cout << "Ligh is already off\n";
	}
};

struct OnState : State
{
	OnState()
	{
		cout << "Light is turned on\n";
	}

	void off(LightSwitch* ls) override;
};

struct OffState : State
{
	OffState()
	{
		cout << "Light is turned off\n";
	}

	void on(LightSwitch* ls) override;
};

class LightSwitch
{
	State* state;
public:
	LightSwitch()
	{
		state = new OffState();
	}
	void set_state(State* state)
	{
		this->state = state;
	}

	void on() 
	{
		state->on(this);
	}
	void off()
	{
		state->off(this);
	}
};

void OnState::off(LightSwitch* ls)
{
	cout << "Switching light off" << endl;
	ls->set_state(new OffState());
	delete this; // not a good code
}

void OffState::on(LightSwitch* ls)
{
	cout << "Switching light on" << endl;
	ls->set_state(new OnState());
	delete this; // not a good code
}

int main(int ac, char* av[])
{
	LightSwitch ls;
	ls.on();
	ls.off();
	ls.off();
	
	getchar();
	return 0;
}