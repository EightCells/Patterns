#pragma once
#ifndef __STRATEGY_H__
#define __STRATEGY_H__
#include <iostream>

class CalFunc
{
public:
	virtual int Calculate(int n1, int n2) const = 0;
};

class CalculateContext
{
public:
	CalculateContext(CalFunc* cal, int n1, int n2)
		:_calfunc(cal), num1(n1), num2(n2) {}
	~CalculateContext()
	{
		delete _calfunc;
	}
	void set_cal(CalFunc* cal)
	{
		if (cal != _calfunc)
		{
			CalFunc* old = _calfunc;
			_calfunc = cal;
			delete old;
		}
	}
	void Display()
	{
		std::cout << "The result is: " << _calfunc->Calculate(num1, num2) << ".\r\n";
	}
private:
	CalFunc* _calfunc;
	int num1;
	int num2;
};

template<class ACalFunc>
class ModelContext
{
public:
	ModelContext(ACalFunc& cal, int n1, int n2)
		:_calfunc(cal), num1(n1), num2(n2) {}
	void Display()
	{
		std::cout << "The result is: " << _calfunc.Calculate(num1, num2) << ".\r\n";
	}
private:
	ACalFunc _calfunc;
	int num1;
	int num2;
};

class AddFunc :public CalFunc
{
public:
	virtual int Calculate(int n1, int n2) const override
	{
		return n1 + n2;
	}
};

class MinusFunc :public CalFunc
{
public:
	virtual int Calculate(int n1, int n2) const override
	{
		return n1 - n2;
	}
};

class MultiFunc :public CalFunc
{
public:
	virtual int Calculate(int n1, int n2) const override
	{
		return n1 * n2;
	}
};

class DevideFunc :public CalFunc
{
public:
	virtual int Calculate(int n1, int n2) const override
	{
		if (n2 == 0)
		{
			std::cout << "Can't devide zero, change the devide number to 1...";
			return n1;
		}
		return n1 / n2;
	}
};

class PowerFunc :public CalFunc
{
public:
	virtual int Calculate(int n1, int n2) const override
	{
		if (n2 == 0)return 1;
		int res = n1;
		while (--n2)
		{
			res *= n1;
		}
		return res;
	}
};


void StrategyTest()
{
	CalculateContext context1(new PowerFunc, 2, 0);
	context1.Display();

	context1.set_cal(new DevideFunc);
	context1.Display();

	PowerFunc pf;
	ModelContext<PowerFunc> context2(pf, 10, 5);
	context2.Display();
}

#endif // !__STRATEGY_H__
