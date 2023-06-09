#pragma once
#ifndef __FLYWEIGHT_H__
#define __FLYWEIGHT_H__

#include <iostream>
#include <unordered_map>

class Flyweight
{
public:
	Flyweight(const int i) :in_state(i) {}
	virtual void Operation(const int ex_state) const = 0;
protected:
	int in_state;
};

class ConcreteFlyweight :public Flyweight
{
public:
	ConcreteFlyweight(const int i) :Flyweight(i) {}
	virtual void Operation(const int ex_state) const override
	{
		std::cout << "This Concrete Flyweight's in_state is " << in_state << ", ex_state is " << ex_state << ".\r\n";
	}
};

class UnsharedConcreteFlyweight :public Flyweight
{
public:
	UnsharedConcreteFlyweight(const int i) :Flyweight(i) {}
	virtual void Operation(const int ex_state) const override
	{
		std::cout << "This Unshared Concrete Flyweight's in_state is " << in_state << ", ex_state is " << ex_state << ".\r\n";
	}
};

class FlyweightFactory
{
public:
	~FlyweightFactory()
	{
		for (auto it = flyweights.begin(); it != flyweights.end(); ++it)
			delete it->second;
		flyweights.clear();
	}
	Flyweight* GetFlyweight(const int in_state_cmp)
	{
		/*std::unordered_map<int, Flyweight*>::iterator*/
		auto res = flyweights.find(in_state_cmp);
		if (res == flyweights.end())
		{
			std::cout << "new a Flyweight success.\r\n";
			Flyweight* f = new ConcreteFlyweight(in_state_cmp);
			flyweights.emplace(in_state_cmp, f);
			return f;
		}
		std::cout << "find the Flyweight success.\r\n";
		return res->second;
	}
private:
	std::unordered_map<int, Flyweight*> flyweights;
};

void FlyweightTest()
{
	FlyweightFactory* fac = new FlyweightFactory;

	//map此时为空，会新建一个对象
	Flyweight* r = fac->GetFlyweight(1);
	r->Operation(100);

	//map已经有了key值为1的对象，直接返回该对象
	r = fac->GetFlyweight(1);
	r->Operation(200);
	
	//不需要再delete r，因为FlyweightFactory的析构会释放内存。
	delete fac;
}

#endif // !__FLYWEIGHT_H__




