#pragma once
#ifndef __CHAIN_OF_RESPONSIBILITY__
#define __CHAIN_OF_RESPONSIBILITY__

#include<iostream>

class Handler
{
public:
	Handler(Handler* h = nullptr) :_handler(h), flag(-1) {}
	virtual ~Handler() { delete _handler; }
	virtual void HandleRequest(int f)
	{
		std::cout << "default Handle Request.\r\n";
	}
	int GetFlag() { return flag; }
protected:
	Handler* _handler;
	int flag;
};

class ConcreteHandler1 :public Handler
{
public:
	ConcreteHandler1(Handler* h = nullptr, int f = 0) :Handler(h) { flag = f; }
	virtual void HandleRequest(int f) override
	{
		if (f >= 0 && f < 5)
		{
			std::cout << "Concrete Handler 1 Request.\r\n";
		}
		else
		{
			std::cout << "Concrete Handler 1 can NOT handle this flag = " << f << ".\r\n";
			_handler->HandleRequest(f);
		}
	}
};

class ConcreteHandler2 :public Handler
{
public:
	ConcreteHandler2(Handler* h = nullptr, int f = 0) :Handler(h) { flag = f; }
	virtual void HandleRequest(int f) override
	{
		if (f >= 5 && f < 10)
		{
			std::cout << "Concrete Handler 2 Request.\r\n";
		}
		else
		{
			std::cout << "Concrete Handler 2 can NOT handle this flag = " << f << ".\r\n";
			_handler->HandleRequest(f);
		}
	}
};

void ChainTest()
{
	Handler* h = new Handler();
	Handler* h1 = new ConcreteHandler1(h, 6);  //6 > 5，转到 h 执行
	Handler* h2 = new ConcreteHandler2(h1, 13); //13 > 10，转到 h1 执行，而 h1 也不执行这种情况，最终转给 h

	h->HandleRequest(h->GetFlag());
	h1->HandleRequest(h1->GetFlag());
	h2->HandleRequest(h2->GetFlag());
}

#endif // !__CHAIN_OF_RESPONSIBILITY__

