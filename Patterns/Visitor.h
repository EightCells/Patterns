#pragma once
#ifndef __VISITOR_H__
#define __VISITOR_H__
#include <iostream>
#include <vector>

class Visitor;

class Element
{
public:
	virtual void Accept(Visitor*) = 0;
};

class ElementA :public Element
{
public:
	virtual void Accept(Visitor* v)override;
};

class ElementB :public Element
{
public:
	virtual void Accept(Visitor* v)override;
};

class Visitor
{
public:
	//针对每一种对象创建操作
	virtual void VisitElementA(ElementA*) = 0;
	virtual void VisitElementB(ElementB*) = 0;
};

class Visitor1 :public Visitor
{
public:
	virtual void VisitElementA(ElementA*)override;
	virtual void VisitElementB(ElementB*)override;
};

class Visitor2 :public Visitor
{
public:
	virtual void VisitElementA(ElementA*)override;
	virtual void VisitElementB(ElementB*)override;
};

//用于管理elements，通常是一个Composite
class ObjectStructure
{
public:
	void Attach(Element*);
	void Detach(Element*);
	void Accept(Visitor*);
private:
	std::vector<Element*> _elements;
};

void ElementA::Accept(Visitor* v)
{
	v->VisitElementA(this);
}

void ElementB::Accept(Visitor* v)
{
	v->VisitElementB(this);
}

void Visitor1::VisitElementA(ElementA* a)
{
	std::cout << "visitor 1 element A.\r\n";
}

void Visitor1::VisitElementB(ElementB* b)
{
	std::cout << "visitor 1 element B.\r\n";
}

void Visitor2::VisitElementA(ElementA* a)
{
	std::cout << "visitor 2 element A.\r\n";
}

void Visitor2::VisitElementB(ElementB* b)
{
	std::cout << "visitor 2 element B.\r\n";
}

void ObjectStructure::Attach(Element* e)
{
	for (auto& ele : _elements)
	{
		if (ele == e)return;
	}
	_elements.push_back(e);
}

void ObjectStructure::Detach(Element* e)
{
	for (auto ele=_elements.begin();ele!=_elements.end();++ele)
	{
		if (*ele == e)
		{
			_elements.erase(ele);
			return;
		}
	}
}

void ObjectStructure::Accept(Visitor* v)
{
	for (auto& ele : _elements)
	{
		ele->Accept(v);
	}
}

void VistorTest()
{
	ObjectStructure objs;
	ElementA* a = new ElementA;
	ElementB* b = new ElementB;

	objs.Attach(a);
	objs.Attach(b);
	objs.Attach(a); //测试重复注册

	Visitor1 v1;
	Visitor2 v2;

	objs.Accept(&v1);
	std::cout << "\r\n";
	objs.Accept(&v2);

	objs.Detach(a);
	objs.Detach(a); //测试空注销
	ElementB* b2 = b;
	objs.Detach(b2);
	objs.Detach(b); //测试空注销

	delete a;
	delete b;
	//delete b2; //no need
}

#endif // !__VISITOR_H__

