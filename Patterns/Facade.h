#pragma once
#ifndef __FACADE_H__
#define __FACADE_H__
#include <iostream>

class A
{
public:
	void OperationA()
	{
		std::cout << "Object A Operation.\r\n";
	}
private:
	int n;
};

class B
{
public:
	void OperationB()
	{
		std::cout << "Object B Operation.\r\n";
	}
};

class Facade
{
public:
	void UserOpreation()
	{
		A a;
		B b;
		a.OperationA();
		b.OperationB();
	}
};

//or
class Facade2
{
public:
	Facade2(A* a, B* b)
	{
		this->a = a;
		this->b = b;
	}
	~Facade2()
	{
		delete a, b;
	}
	void UserOperation()
	{
		a->OperationA();
		b->OperationB();
	}
private:
	A* a;
	B* b;
};

void FacadeTest()
{
	Facade f;
	f.UserOpreation();

	A* a = new A;
	B* b = new B;
	Facade2 f2(a, b);
	f2.UserOperation();
}

#endif // !__FACADE_H__


