#pragma once
#ifndef __PROTOTYPE_H__
#define __PROTOTYPE_H__
#include "SimpleList.h"
#include <iostream>
#include <unordered_map>

class Prototype
{
public:
	virtual Prototype* Clone() = 0;
	virtual void Print() = 0;
	void change(int n)
	{
		test = n;
		std::cout << "change test number success.\r\n";
	}
protected:
	int test;
};

class PrototypeClassA :public Prototype
{
public:
	PrototypeClassA(int n) :num(n) { test = 0; }
	PrototypeClassA(const PrototypeClassA&);
	Prototype* Clone();
	void Print();
private:
	int num;
};

class PrototypeClassB :public Prototype
{
public:
	PrototypeClassB(std::string s) :str(s) { test = 1; }
	PrototypeClassB(const PrototypeClassB&);
	Prototype* Clone();
	void Print();
private:
	std::string str;
};

class PrototypeFactory
{
public:
	PrototypeFactory()
	{
		factory["A"] = new PrototypeClassA(10086);
		factory["B"] = new PrototypeClassB("Prototype Class B");
	}
	Prototype* GetPrototype(std::string)const;
	void AddPrototype(std::string, Prototype*);

	Prototype* GetOrigin(std::string s)const
	{
		return factory.at(s);
	}
private:
	std::unordered_map<std::string, Prototype*> factory;
};

#endif // !__PROTOTYPE_H__

/*PrototypeFactory factory;

Prototype* pa_copy = factory.GetPrototype("A");
Prototype* pb_copy = factory.GetPrototype("B");

cout << "pa_copy_1: ";
pa_copy->Print();
cout << "pb_copy_1: ";
pb_copy->Print();
cout << endl;

Prototype* pa2_copy = factory.GetPrototype("A");
cout << "pa_copy_1: ";
pa_copy->change(1234);
cout << "pa_copy_2: ";
pa2_copy->change(114514);
cout << endl;

cout << "pa_copy_1: ";
pa_copy->Print();
cout << "pa_copy_2: ";
pa2_copy->Print();
cout << "Original pa: ";
factory.GetOrigin("A")->Print();*/
