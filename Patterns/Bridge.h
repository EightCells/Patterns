#pragma once
#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include <iostream>

class Implementor
{
public:
	virtual void OperationImp() = 0;
};

class ConcreteImplementorA :public Implementor
{
public:
	void OperationImp()
	{
		std::cout << "Concrete Implementor A.\r\n";
	}
};

class ConcreteImplementorB :public Implementor
{
public:
	void OperationImp()
	{
		std::cout << "Concrete Implementor B.\r\n";
	}
};

//组合方式，imp对象在抽象类里
class Abstraction1
{
public:
	Abstraction1(Implementor* imp_) :imp(imp_) {}
	virtual void Operation() = 0;
protected:
	Implementor* imp;
};

class RefinedAbstraction1 :public Abstraction1
{
public:
	RefinedAbstraction1(Implementor* imp_) :Abstraction1(imp_) {}
	void Operation()
	{
		imp->OperationImp();
	}
};

//继承方式，imp对象在子类里
class Abstraction2
{
public:
	virtual void Operation() = 0;
};

class RefinedAbstraction2 :public Abstraction2
{
public:
	RefinedAbstraction2(Implementor* imp_) :imp(imp_) {}
	void Operation()
	{
		imp->OperationImp();
	}
private:
	Implementor* imp;
};

void BridgeTest()
{
	Implementor* imp_ = new ConcreteImplementorA();

	Abstraction1* a1 = new RefinedAbstraction1(imp_);
	a1->Operation();

	imp_ = new ConcreteImplementorB();
	Abstraction2* a2 = new RefinedAbstraction2(imp_);
	a2->Operation();
}

#endif // !__BRIDGE_H__
