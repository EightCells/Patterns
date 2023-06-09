#pragma once
#ifndef __BUILDER_H__
#define __BUILDER_H__
#include "SimpleList.h"

class Product
{
public:
	Product()
	{
		head = new ListNode("head");
		tail = head;
	}
	void add(const char* s)
	{
		ListNode* p = new ListNode(s);
		tail->next = p;
		tail = p;
	}
	ListNode* GetList()
	{
		return head;
	}
private:
	ListNode* head;
	ListNode* tail;
};

class Builder
{
public:
	virtual void BuildPartA() {};
	virtual void BuildPartB() {};
	Product& GetResult()
	//�˴��践���������ͣ�����product�е�tailָ�벻���
	{
		return product;
	}
private:
	Product product;
};

class ConcreteBuilder1 : public Builder
{
public:
	void BuildPartA()
	{
		GetResult().add("Concrete Part A 1");
	}
	void BuildPartB()
	{
		GetResult().add("Concrete Part B 1");
	}
};

class ConcreteBuilder2 : public Builder
{
public:
	void BuildPartA()
	{
		GetResult().add("Concrete Part A 2");
	}
	void BuildPartB()
	{
		GetResult().add("Concrete Part B 2");
	}
};

class Director
{
public:
	void Construct(Builder& builder)
	//�˴��������ô��ݣ�����ʹ�õ��ǻ����BuildPartA��BuildPartB���൱��ɶ��û����
	{
		builder.BuildPartA();
		builder.BuildPartB();
	}
};

#endif // !__BUILDER_H__
