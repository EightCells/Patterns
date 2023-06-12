#pragma once
#ifndef __MEDIATOR_H__
#define __MEDIATOR_H__
#include <vector>
class Colleague;
class Director
{
public:
	virtual ~Director() {}
	virtual void ColleagueChanged(Colleague*) = 0;
protected:
	Director() {}
};

class Colleague
{
public:
	Colleague(Director* ditr) :_director(ditr) {}
	virtual ~Colleague() { _director = nullptr; }
	virtual void Changed() = 0;
	virtual void display() const = 0;
protected:
	Director* _director;
};

class ConcreteColleague :public Colleague
{
public:
	ConcreteColleague(Director*, int);
	virtual bool is_flag_update() const = 0;
	virtual void display() const override;
	void add_flag();
	void minus_flag();
	void set_flag(int);
protected:
	int flag;
};

class ConcreteColleague1 :public ConcreteColleague
{
public:
	ConcreteColleague1(Director*, int);
	virtual void Changed() override;
	virtual bool is_flag_update() const override;
};

class ConcreteColleague2 :public ConcreteColleague
{
public:
	ConcreteColleague2(Director*, int);
	virtual void Changed() override;
	virtual bool is_flag_update() const override;
};

class ConcreteDirector :public Director
{
public:
	~ConcreteDirector();
	virtual void ColleagueChanged(Colleague*) override;
	void insert_colleague(Colleague*);
private:
	std::vector<Colleague*> _colleagues;
	Colleague* GetColleague(Colleague*);
};

void MediatorTest();

#endif // !__MEDIATOR_H__
