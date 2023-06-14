#pragma once
#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <unordered_map>
#include <vector>

enum STATE { all, state1, state2, };

class State
{
public:
	State(int s1, int s2) :state1(s1), state2(s2) {}
	int state1;
	int state2;

	State& operator= (const State& rhs)
	{
		state1 = rhs.state1;
		state2 = rhs.state2;
		return *this;
	}

	int get_one_state(STATE st)
	{
		switch (st)
		{
		case STATE::state1:
			return state1;
		case STATE::state2:
			return state2;
		default:
			return -1;
		}
	}

	void set_one_state(STATE st, int n1)
	{
		switch (st)
		{
		case STATE::state1:
			state1 = n1;
			break;
		case STATE::state2:
			state2 = n1;
			break;
		default:
			break;
		}
	}

};

class Subject;
class ChangeManager;

class Observer
{
public:
	Observer(STATE st) :interested(st) {} 
	virtual void Update(Subject*, STATE&) = 0;
protected:
	STATE interested;
};

class ConcreteObserver :public Observer
{
public:
	ConcreteObserver(STATE st, State& s)
		:Observer(st), observer_state(s) {}
	virtual void Update(Subject*, STATE&) override;
private:
	State observer_state;
};

class ChangeManager
{
public:
	ChangeManager() :
		s_o_map(new std::unordered_map<Subject*, std::vector<Observer*>>) {}
	~ChangeManager();
	std::vector<Observer*>& GetObservers(Subject*);
	void Register(Subject*, Observer*);
	void Unregister(Subject*, Observer*);
protected:
	friend class Subject;


	std::unordered_map<Subject*, std::vector<Observer*>>* s_o_map;
};

class Subject
{
public:
	Subject(ChangeManager* cm) :_manager(cm) {}
	void Attach(Observer* ob)
	{
		_manager->Register(this, ob);
	}
	void Dettach(Observer* ob)
	{
		_manager->Unregister(this, ob);
	}
	virtual void Notify(STATE) = 0;
	virtual State GetState() = 0;
protected:
	ChangeManager* _manager;
};

class ConcreteSubject :public Subject
{
public:
	ConcreteSubject(State& s, ChangeManager* cm)
		:sub_state(s), Subject(cm) {}
	virtual void Notify(STATE) override;
	void set_state(int a, int b)
	{
		if (a != -1)
			sub_state.state1 = a;
		if (b != -1)
			sub_state.state2 = b;
	}
	virtual State GetState() override;
private:
	State sub_state;
};

void ObserverTest();

#endif // !__OBSERVER_H__

