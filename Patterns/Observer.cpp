#include "Observer.h"
#include <iostream>

void ConcreteObserver::Update(Subject* sub, STATE& st)
{
	State sub_s = sub->GetState();
	if (interested == STATE::all)
	{
		std::cout << "Update observer ALL state;" <<
			observer_state.state1 << " -> "
			<< sub_s.state1 << ", "
			<< observer_state.state2 << sub_s.state2 << ".\r\n";
		observer_state = sub_s;
	}
	else if (interested == st)
	{
		std::cout << "Update observer state;" <<
			
			<< observer_state.state2 << sub_s.state2 << ".\r\n";
		observer_state = sub_s;
	}
}

State ConcreteSubject::GetState()
{
	return sub_state;
}

void ConcreteSubject::Notify(STATE& st)
{
	std::vector<Observer*>& obs =
		_manager->GetObservers(this);
	for (auto ob : obs)
	{
		ob->Update(this, st);
	}
}

ChangeManager::~ChangeManager()
{
	for (auto s_o : *s_o_map)
	{

	}
}