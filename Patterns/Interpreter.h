#pragma once
#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__
#include <unordered_map>

/* 布尔表达式解释器 */

class Context
{
public:
	bool Lookup(const char* c) const
	{
		for (auto& i : characters)
		{
			if (strcmp(i.first, c) == 0)
				return i.second;
		}
	}
	void Assign(const char* c, bool b)
	{
		characters.insert({ c, b });
	}

private:
	std::unordered_map<const char*, bool> characters;
};

class BooleanExp
{
public:
	BooleanExp() {}
	virtual ~BooleanExp() {}

	virtual bool Evaluate(Context&) = 0;
	virtual BooleanExp* Replace(const char*, BooleanExp&) = 0;
	virtual BooleanExp* Copy()const = 0;
};

class VariableExp: public BooleanExp
{
public:
	explicit VariableExp(const char* c)
	{
		name = _strdup(c);
	}

	virtual bool Evaluate(Context& ct)override
	{
		return ct.Lookup(name);
	}

	virtual BooleanExp* Replace(const char* c, BooleanExp& be)override
	{
		if (strcmp(c, name) == 0)return be.Copy();
		else return new VariableExp(name);
	}

	virtual BooleanExp* Copy()const override
	{
		return new VariableExp(name);
	}
private:
	const char* name;
};

class Constant :public BooleanExp
{
public:
	explicit Constant(bool b)
	{
		constant = b;
	}

	virtual bool Evaluate(Context& ct)override
	{
		return constant;
	}

	virtual BooleanExp* Replace(const char* c, BooleanExp& be)override
	{
		return new Constant(constant);
	}

	virtual BooleanExp* Copy()const override
	{
		return new Constant(constant);
	}
private:
	bool constant;
};

class NotExp :public BooleanExp
{
public:
	explicit NotExp(BooleanExp* v)
	{
		ve = v;
	}

	virtual bool Evaluate(Context& ct)override
	{
		return !ve->Evaluate(ct);
	}

	virtual BooleanExp* Replace(const char* c, BooleanExp& be)override
	{
		return new NotExp(
			ve->Replace(c, be)
		);
	}

	virtual BooleanExp* Copy()const override
	{
		return new NotExp(
			ve->Copy()
		);
	}

private:
	BooleanExp* ve;
};

class OrExp: public BooleanExp
{
public:
	explicit OrExp(BooleanExp* v1, BooleanExp* v2)
	{
		ve1 = v1;
		ve2 = v2;
	}

	virtual bool Evaluate(Context& ct)override
	{
		return ve1->Evaluate(ct) || ve2->Evaluate(ct);
	}

	virtual BooleanExp* Replace(const char* c, BooleanExp& be)override
	{
		return
			new OrExp(
				ve1->Replace(c, be),
				ve2->Replace(c, be)
			);
	}

	virtual BooleanExp* Copy()const override
	{
		return
			new OrExp(
				ve1->Copy(),
				ve2->Copy()
			);
	}
private:
	BooleanExp* ve1;
	BooleanExp* ve2;
};

class AndExp: public BooleanExp
{
public:
	explicit AndExp(BooleanExp* v1, BooleanExp* v2)
	{
		ve1 = v1;
		ve2 = v2;
	}

	virtual bool Evaluate(Context& ct)override
	{
		return ve1->Evaluate(ct) && ve2->Evaluate(ct);
	}

	virtual BooleanExp* Replace(const char* c, BooleanExp& be)override
	{
		return
			new AndExp(
				ve1->Replace(c, be),
				ve2->Replace(c, be)
			);
	}

	virtual BooleanExp* Copy()const override
	{
		return
			new OrExp(
				ve1->Copy(),
				ve2->Copy()
			);
	}
private:
	BooleanExp* ve1;
	BooleanExp* ve2;
};

void InterpreterTest()
{
	/* (true and x) or (y and (not x)) */
	Context ct;

	BooleanExp* x = new VariableExp("x");
	BooleanExp* y = new VariableExp("y");

	BooleanExp* expression =
		new OrExp(
			new AndExp(new Constant(true), x),
			new AndExp(y, new NotExp(x)
			)
		);

	ct.Assign("x", false);
	ct.Assign("y", true);

	cout << "Result: " << expression->Evaluate(ct) << endl;

	BooleanExp* z = new VariableExp("z");
	ct.Assign("z", false);

	BooleanExp* newexp = expression->Replace("y", *z);

	cout << "Result: " << newexp->Evaluate(ct) << endl;

	delete x;
	delete y;
	delete z;
	delete expression;
	delete newexp;
}

#endif // !__INTERPRETER_H__


