#pragma once
#ifndef __STATE_H__
#define __STATE_H__

#include <iostream>
/*
 * ״̬����Ĵ��������ٿ��ܻ����һ���Ŀ�����
 * �ر�����״̬ת���ǳ�Ƶ��������¡��������
 * ��һ���ؼ��������أ����Կ���ʹ�ö���ػ��
 * �󻺴�ȼ���������״̬�����Լ��ٶ���Ĵ�
 * �������ٿ�����������ģʽ��һ�����׵ķ�ʽ��
 */

class State;
class Context;

class State
{
public:
	virtual void handle(Context*) = 0;
protected:
	void change_state(Context* ct, State* st);
};

class Context
{
public:
	Context(State* st) :_state(st) {}
	~Context()
	{
		delete _state;
	}
	void Request()
	{
		_state->handle(this);
	}
private:
	friend class State;
	void change_state(State* st)
	{
		State* _state_copy = _state;
		_state = st;
		delete _state_copy;
	}

	State* _state;
};

class State1 :public State
{
public:
	State1() = default;
	~State1() = default;
	virtual void handle(Context* ct)override;
};

class State2 :public State
{
public:
	//static State2* Instance();
	State2() = default;

	virtual void handle(Context* ct)override;

private:
	//State2() = default;

	static State2* _state2;
};

//State2* State2::_state2 = nullptr;

void StateTest()
{
	State* st = new State1;
	Context* ct = new Context(st);

	ct->Request();
	ct->Request();
	ct->Request();

	delete ct;
}

void State::change_state(Context* ct, State* st)
{
	ct->change_state(st);
}

/*State2* State2::Instance()
{
	if (_state2 == nullptr)
	{
		_state2 = new State2;
	}
	return _state2;
}*/

void State2::handle(Context* ct)
{
	std::cout << "Handle: State 2 change to State 1.\r\n";
	change_state(ct, new State1);
}

void State1::handle(Context* ct)
{
	std::cout << "Handle: State 1 change to State 2.\r\n";
	change_state(ct, new State2/*::Instance()*/);
}

#endif // !__STATE_H__

