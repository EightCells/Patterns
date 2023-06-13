#include "Memeno.h"
#include <iostream>

Originator::Originator(std::string s)
{
	_state = s;
}

Memeno* Originator::CreateMemeno()
{
	return new Memeno(_state);
}

void Originator::SetMemeno(Memeno* m)
{
	_state = m->_state;
}

void Originator::display()
{
	std::cout << "state: " << _state << ".\r\n";
}

void Originator::set_state(std::string s)
{
	_state = s;
}

Memeno::Memeno(std::string s)
{
	_state = s;
};

Caretaker::Caretaker() :_memeno(nullptr) {}

Caretaker::~Caretaker()
{
	delete _memeno;
}

void Caretaker::setMemeno(Memeno* m)
{
	_memeno = m;
}

Memeno* Caretaker::getMemeno()
{
	return _memeno;
}

void MemenoTest()
{
	Caretaker ct;
	Originator otr("first");
	otr.display();

	ct.setMemeno(otr.CreateMemeno());
	otr.set_state("second");
	otr.display();

	otr.SetMemeno(ct.getMemeno());
	otr.display();
}
