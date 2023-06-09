#pragma once
#ifndef __DECORATOR_H__
#define __DECORATOR_H__

#include <iostream>
#include <string>

class Component
{
public:
	virtual void Operation() = 0;
	virtual ~Component() {}
};

class ConcreteComponent :public Component
{
public:
	~ConcreteComponent() { std::cout << "conrete component delete."; }
	virtual void Operation() override
	{
		std::cout << "Concrete Component: do something.\r\n";
	}
};

class Decorator :public Component
{
public:
	Decorator(Component* c) :comp_(c) {}
	~Decorator()
	{
		std::cout << "decorator comp_ delete.\r\n";
		delete comp_;
	}
	virtual void Operation() override
	{
		comp_->Operation();
	}
protected:
	Component* comp_;
};

class BeforeDecorator :public Decorator
{
public:
	BeforeDecorator(Component* c) :Decorator(c) {}
	/*~BeforeDecorator()
	{
		std::cout << "before decorator: delete comp_.\r\n";
		delete comp_;
	}*/
	virtual void Operation() override
	{
		std::cout << "Before: do something else...\r\n";
		Decorator::Operation();
	}
};

class AfterDecorator :public Decorator
{
public:
	AfterDecorator(Component* c) :Decorator(c) {}
	/*~AfterDecorator()
	{
		std::cout << "after decorator: delete comp_.\r\n";
		delete comp_;
	}*/
	virtual void Operation() override
	{
		Decorator::Operation();
		std::cout << "After: do something else...\r\n";
	}
};

Component* DecoratorTest()
{
	Component* cp = new ConcreteComponent;
	cp->Operation();
	std::cout << "\r\n";
	cp = new BeforeDecorator(cp);
	cp->Operation();
	std::cout << "\r\n";
	cp = new AfterDecorator(cp);
	cp->Operation();
	std::cout << "\r\n";

	return cp;
}

#endif // !__DECORATOR_H__
