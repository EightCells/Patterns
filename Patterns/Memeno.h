#pragma once
#ifndef __MEMENO_H__
#define __MEMENO_H__

#include <string>

class Originator;
class Memeno;
class Caretaker;

class Originator
{
public:
	Originator(std::string);
	Memeno* CreateMemeno();
	void SetMemeno(Memeno*);
	void display();
	void set_state(std::string);
private:
	std::string _state;
};

class Memeno
{
public:

private:
	friend class Originator;
	Memeno(std::string);
	std::string _state;
};

class Caretaker
{
public:
	Caretaker();
	~Caretaker();
	void setMemeno(Memeno*);
	Memeno* getMemeno();
private:
	Memeno* _memeno;
};

void MemenoTest();


#endif // !__MEMENO_H__

