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
	ConcreteObserver(STATE st, State s)
		:Observer(st), observer_state(s) {}
	virtual void Update(Subject*, STATE&) override;
private:
	State observer_state;
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
	virtual void Notify(STATE&) = 0;
	virtual State GetState() = 0;
protected:
	ChangeManager* _manager;
};

class ConcreteSubject :public Subject
{
public:
	ConcreteSubject(State s, ChangeManager* cm)
		:sub_state(s), Subject(cm) {}
	virtual void Notify(STATE&) override;
	virtual State GetState() override;
private:
	State sub_state;
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

#endif // !__OBSERVER_H__

