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
			<< observer_state.state2 << " -> "
			<< sub_s.state2 << ".\r\n";
		observer_state = sub_s;
	}
	else if (interested == st || st == STATE::all)
	{
		int origin = observer_state.get_one_state(interested);
		int other = sub_s.get_one_state(interested);
		std::cout << "Update observer state;" 
			<< interested
			<< ": "
			<< origin << " -> "
			<< other << ".\r\n";
		observer_state.set_one_state(interested, other);
	}
}

State ConcreteSubject::GetState()
{
	return sub_state;
}

void ConcreteSubject::Notify(STATE st)
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
	for (auto& s_o : *s_o_map)
	{
		s_o.second.clear();
	}
	s_o_map->clear();
	delete s_o_map;
}

std::vector<Observer*>& ChangeManager::GetObservers(Subject* sub)
{
	return (*s_o_map)[sub];
}

void ChangeManager::Register(Subject* sub, Observer* ob)
{
	auto it = s_o_map->find(sub);
	if (it != s_o_map->end())
	{
		for (auto o : it->second)
		{
			if (o == ob)return;
		}
		it->second.push_back(ob);
	}
	else
	{
		(*s_o_map)[sub] = {ob};
	}
}

void ChangeManager::Unregister(Subject* sub, Observer* ob)
{
	auto it = s_o_map->find(sub);
	if (it != s_o_map->end())
	{
		auto o = std::find(it->second.begin(), it->second.end(), ob);
		if (o != it->second.end()) {
			it->second.erase(o);
		}
	}
}

void ObserverTest()
{
	State s(0, 0);
	ChangeManager* cm = new ChangeManager;

	ConcreteSubject* sub1 = new ConcreteSubject(s, cm);
	s.state1 = 5;
	s.state2 = 5;
	ConcreteSubject* sub2 = new ConcreteSubject(s, cm);

	s.state1 = 10;
	s.state2 = 10;
	Observer* ob1 = new ConcreteObserver(STATE::all, s);
	s.state1 = 15;
	s.state2 = 15;
	Observer* ob2 = new ConcreteObserver(STATE::state1, s);

	//ob1关心sub1全部，ob2关心sub2的state1
	sub1->Attach(ob1);
	sub1->Attach(ob2);

	sub2->Attach(ob2);
	sub2->Attach(ob2); //测试重复注册

	sub1->set_state(1, 1);
	sub1->Notify(STATE::all);
	std::cout << "\r\n";
	sub2->set_state(6, -1);
	sub2->Notify(STATE::state1);

	sub2->Dettach(ob2);
	sub2->Dettach(ob2); //测试重复注销
	/*sub1->Dettach(ob1);
	sub1->Dettach(ob2);*/

	delete cm;
	delete sub1;
	delete sub2;
	delete ob1;
	delete ob2;
}