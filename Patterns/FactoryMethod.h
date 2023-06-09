#pragma once
#ifndef __FACTORY_METHOD_H__
#define __FACTORY_METHOD_H__
#include "SimpleList.h"

class Product
{
public:
	Product();
	virtual void add();
	ListNode* GetList() { return head; }
protected:
	ListNode* head;
	ListNode* tail;
	int length;
};

class ConcreteProductA :public Product
{
public:
	ConcreteProductA();
	void add();
};

class ConcreteProductB :public Product
{
public:
	ConcreteProductB();
	void add();
};

class Creator
{
public:
	virtual Product* Create();
	virtual Product* Create(int id);
};

template <class TheProduct>
class StandardCreator :public Creator
{
public:
	virtual Product* Create();
};

class ConcreteCreatorByID :public Creator
{
public:
	Product* Create(int id);
};

template <class TheProduct>
Product* StandardCreator<TheProduct>::Create()
{
	return new TheProduct;
}

#endif // !__FACTORY_METHOD_H__
