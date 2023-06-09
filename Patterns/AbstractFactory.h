#pragma once
#ifndef __ABSTRACT_FACTORY_H__
#define __ABSTRACT_FACTORY_H__
#include "SimpleList.h"

class AbstractProduct
{
public:
	virtual void test() {}
};

class AbstractProductA :public AbstractProduct
{
public:
	AbstractProductA()
	{
		headA = new ListNode("Product A head");
		tailA = headA;
	}
	void addA(const char* s)
	{
		ListNode* p = new ListNode(s);
		tailA->next = p;
		tailA = p;
	}
	ListNode* GetList()
	{
		return headA;
	}
protected:
	ListNode* headA;
	ListNode* tailA;
	virtual void InitA() {};
};

class ProductA1 :public AbstractProductA
{
public:
	void InitA()
	{
		headA->str = "Product A1 head";
	}
};

class ProductA2 :public AbstractProductA
{
public:
	void InitA()
	{
		headA->str = "Product A2 head";
	}
};

class AbstractProductB :public AbstractProduct
{
public:
	AbstractProductB()
	{
		headB = new ListNode("Product B head");
		tailB = headB;
	}
	void addB(const char* s)
	{
		ListNode* p = new ListNode(s);
		tailB->next = p;
		tailB = p;
	}
	ListNode* GetList()
	{
		return headB;
	}
protected:
	ListNode* headB;
	ListNode* tailB;
	virtual void InitB() {};
};

class ProductB1 :public AbstractProductB
{
public:
	void InitB()
	{
		headB->str = "Product B1 head";
	}
};

class ProductB2 :public AbstractProductB
{
public:
	void InitB()
	{
		headB->str = "Product B2 head";
	}
};

enum PRODUCT_TYPE
{
	A1,
	A2,
	B1,
	B2
};

class Factory
{
public:
	AbstractProduct* CreateProduct(PRODUCT_TYPE PT)
	{
		switch (PT)
		{
		case A1:
		{
			ProductA1 p;
			p.InitA();
			product = &p;
			return product;
			break;
		}
		case A2:
		{
			ProductA2 p;
			p.InitA();
			product = &p;
			return product;
			break;
		}
		case B1:
		{
			ProductB1 p;
			p.InitB();
			product = &p;
			return product;
			break;
		}
		case B2:
		{
			ProductB2 p;
			p.InitB();
			product = &p;
			return product;
			break;
		}
		default:
			return product;
			break;
		}
	}
private:
	AbstractProduct* product;
};

class AbstractFactory
{
public:
	virtual void CreateProductA() {}
	virtual void CreateProductB() {}
	AbstractProductA& GetProdctA()
	{
		return productA;
	}
	AbstractProductB& GetProdctB()
	{
		return productB;
	}
protected:
	AbstractProductA productA;
	AbstractProductB productB;
};

class ConcreteFactory1 :public AbstractFactory
{
public:
	void CreateProductA()
	{
		ProductA1 product;
		product.InitA();
		productA = product;
	}
	void CreateProductB()
	{
		ProductB1 product;
		product.InitB();
		productB = product;
	}
};

class ConcreteFactory2 :public AbstractFactory
{
public:
	void CreateProductA()
	{
		ProductA2 product;
		product.InitA();
		productA = product;
	}
	void CreateProductB()
	{
		ProductB2 product;
		product.InitB();
		productB = product;
	}
};

#endif // !__ABSTRACT_FACTORY_H__
