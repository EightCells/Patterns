#pragma once
#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <iostream>
#include <queue>
#include <stack>

class Reciever
{
public:
	explicit Reciever(int c) :_count(c) {}
	void add_c(int a) { _count += a; }
	void minus_c(int a) { _count -= a; }
	void print_c() { std::cout << "The Count is " << _count << ".\r\n"; }
	void action() 
	{ 
		++_count;
		print_c();
	}
private:
	int _count;
};

class Command
{
public:
	explicit Command(bool b = false) :_can_undo(b) {}
	virtual ~Command() {}
	virtual void execute() = 0;
	virtual void undo() {};
	bool can_undo() { return _can_undo; }
private:
	bool _can_undo;
};

//Add 5 Command.
class ConcreteCommand :public Command
{
public:
	ConcreteCommand(Reciever* r) :Command(true), _reciever(r) {}
	virtual void execute() override
	{
		_reciever->add_c(5);
		_reciever->print_c();
	}
	void undo()
	{
		_reciever->minus_c(5);
		_reciever->print_c();
	}
private:
	Reciever* _reciever;
};

//对于不带参数的excute，且不需要撤销操作，可使用函数指针加模板类
template<class T>
class SimpleCommand :public Command
{
public:
	typedef void(T::* Action)();
	SimpleCommand(T* r, Action a) :_reciever(r), _action(a) {}
	virtual void execute()
	{
		(_reciever->*_action)();
	}
private:
	T* _reciever;
	Action _action;
};

class Invoker
{
public:
	~Invoker()
	{
		while (!_cmds.empty())
		{
			_cmds.pop();
		}
		while (!_can_undo_cmds.empty())
		{
			_can_undo_cmds.pop();
		}
		while (!_cant_undo_cmds.empty())
		{
			_cant_undo_cmds.pop();
		}
		while (!_redo_cmds.empty())
		{
			_redo_cmds.pop();
		}
	}
	void ExecuteACommand()
	{
		if (_cmds.empty()) return;
		Command* cmd = _cmds.front();
		cmd->execute();
		if (cmd->can_undo())
			_can_undo_cmds.push(cmd);
		else _cant_undo_cmds.push(cmd);
		_cmds.pop();
	}
	void ExecuteAllCommands()
	{
		while (!_cmds.empty())
		{
			ExecuteACommand();
		}
	}
	void AddACommand(Command* cmd)
	{
		if (cmd != nullptr)
			_cmds.push(cmd);
	}
	void UndoACommand()
	{
		if (!_can_undo_cmds.empty())
		{
			Command* cmd = _can_undo_cmds.top();
			_can_undo_cmds.pop();
			cmd->undo();
			_redo_cmds.push(cmd);
		}
	}
	void RedoACommand()
	{
		if (!_redo_cmds.empty())
		{
			Command* cmd = nullptr;
			cmd = _redo_cmds.top();
			cmd->execute();
			_can_undo_cmds.push(cmd);//redo的命令必定可以撤销
			_redo_cmds.pop();
		}
	}
private:
	std::queue<Command*> _cmds;
	std::stack<Command*> _can_undo_cmds;
	std::stack<Command*> _cant_undo_cmds;//有可能_cmds中有重复的，所以暂时不能delete
	std::stack<Command*> _redo_cmds;
};

void CommandTest()
{
	Reciever* recieve = new Reciever(0);
	Command* cmd1 = new ConcreteCommand(recieve);
	Command* cmd2 = new SimpleCommand<Reciever>(recieve, &Reciever::action);

	Invoker* invoker = new Invoker;

	for (int i = 0; i < 2; i++)
	{
		invoker->AddACommand(cmd1);
		invoker->AddACommand(cmd2);
	}

	invoker->ExecuteAllCommands();

	invoker->UndoACommand();

	invoker->RedoACommand();

	delete invoker;
	delete cmd1;
	delete cmd2;
	delete recieve;
}

#endif // !__COMMAND_H__


