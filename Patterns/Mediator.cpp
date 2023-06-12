#include "Mediator.h"
#include <iostream>

ConcreteColleague::ConcreteColleague(Director* ditr, int f):Colleague(ditr)
{
	flag = f;
}

void ConcreteColleague::display() const
{
	std::cout << "The flag is " << flag << ".\r\n";
}

void ConcreteColleague::add_flag()
{
	++flag;
}

void ConcreteColleague::minus_flag()
{
	--flag;
}

void ConcreteColleague::set_flag(int f)
{
	flag = f;
}

ConcreteColleague1::ConcreteColleague1(Director* ditr, int f) :ConcreteColleague(ditr, f) {}

void ConcreteColleague1::Changed()
{
	if (is_flag_update())
	{
		std::cout << "Concrete Colleague 1 update.\r\n";
		_director->ColleagueChanged(this);
	}
}

bool ConcreteColleague1::is_flag_update() const
{
	if (flag > 5 && flag <= 7)return true;
	else return false;
}

ConcreteColleague2::ConcreteColleague2(Director* ditr, int f) :ConcreteColleague(ditr, f) {}

void ConcreteColleague2::Changed()
{
	if (is_flag_update())
	{
		std::cout << "Concrete Colleague 2 update.\r\n";
		_director->ColleagueChanged(this);
	}
}

bool ConcreteColleague2::is_flag_update() const
{
	if (flag > 10 && flag <= 12)return true;
	else return false;
}

ConcreteDirector::~ConcreteDirector()
{
	for (auto c : _colleagues)
	{
		delete c;
	}
	_colleagues.clear();
}

void ConcreteDirector::insert_colleague(Colleague* c)
{
	if (GetColleague(c) != nullptr) return;
	_colleagues.push_back(c);
}

void ConcreteDirector::ColleagueChanged(Colleague* c)
{
	Colleague* col = GetColleague(c);
	if (col == nullptr) return;
	col->display();
}

Colleague* ConcreteDirector::GetColleague(Colleague* c)
{
	for (auto col : _colleagues)
	{
		if (c == col)return c;
	}
	return nullptr;
}

void MediatorTest()
{
	ConcreteDirector* cdir = new ConcreteDirector;
	ConcreteColleague* c1 = new ConcreteColleague1(cdir, 0);
	ConcreteColleague* c2 = new ConcreteColleague2(cdir, 0);
	cdir->insert_colleague(c1);
	cdir->insert_colleague(c2);
	cdir->insert_colleague(c1);

	int i = 20;
	while (--i)
	{
		c1->add_flag();
		c2->add_flag();
		c1->Changed();
		c2->Changed();
	}
	delete cdir;
	//delete c1;
	//delete c2; //cdir的析构中已删这俩
}
