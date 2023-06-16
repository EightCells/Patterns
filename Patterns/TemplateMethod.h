#pragma once
#ifndef __TEMPLATE_METHOD_H__
#define __TEMPLATE_METHOD_H__
#include <iostream>

class Method
{
public:
	void oper()
	{
		first_oper();
		second_oper();
		third_oper();
	}
protected:
	virtual void first_oper()
	{
		std::cout << "abstract method default first oper.\r\n";
	}
	virtual void second_oper() = 0;
	virtual void third_oper() = 0;
};

class ConcreteMethod1 :public Method
{
protected:
	virtual void first_oper() override
	{
		std::cout << "concrete method 1 first oper.\r\n";
	}
	virtual void second_oper() override
	{
		std::cout << "concrete method 1 second oper.\r\n";
	}
	virtual void third_oper() override
	{
		std::cout << "concrete method 1 third oper.\r\n";
	}
};

class ConcreteMethod2 :public Method
{
protected:
	/*virtual void first_oper() override
	{
		Method::first_oper();
	}*/
	virtual void second_oper() override
	{
		std::cout << "concrete method 2 second oper.\r\n";
	}
	virtual void third_oper() override
	{
		std::cout << "concrete method 2 third oper.\r\n";
	}
};

void TemplateMethodTest()
{
	Method* method = new ConcreteMethod1;
	method->oper();
	delete method;
	method = new ConcreteMethod2;
	method->oper();
	delete method;
}

#endif // !__TEMPLATEMETHOD_H__
