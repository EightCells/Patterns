#include "Composite.h"
#include <iostream>

/*void Component::Add(Component* comp_)
{
	throw std::runtime_error("Not Composite Node! Can't Add!");
}

void Component::Remove(Component* comp_)
{
	throw std::runtime_error("Not Composite Node! Can't Remove!");
}

Component* Component::GetChild(int n)
{
	throw std::runtime_error("Not Composite Node! Can't Get Child!");
}*/

Composite* Component::GetComposite()
{
	return nullptr;
}

void Leaf::Operation()
{
	std::cout << "This is a Leaf Node.\r\n";
}

void Composite::Add(Component* comp_)
{
	if (comp_ != nullptr)
		children.push_back(comp_);
}

void Composite::Remove(Component* comp_)
{
	if (comp_ != nullptr)
		// std::remove查找comp_将它（们）逻辑删除（移到末尾，注意不会改变size），
		// 它返回最后一个元素下一个位置的迭代器。
		// 因此还要调用erase把那些匹配的都删除（会改变size）。
		children.erase(std::remove(children.begin(), children.end(), comp_), children.end());
}

Component* Composite::GetChild(int n)
{
	if (n >= 0 && n < children.size())
		return children[n];
	return nullptr;
}

void Composite::Operation()
{
	std::cout << "\r\nThis is a Composite Node.\r\n";
	for (Component* c : children) {
		c->Operation();
	}
}

Composite* Composite::GetComposite()
{
	return this;
}

void CompositeTest()
{
	/*
				h
			 ________
			 |		|
			l1		c1
					_________
					|		|
					l2		l3
	*/
	Component* h = new Composite;
	Component* c1 = new	Composite;
	Component* l1 = new Leaf;
	Component* l2 = new Leaf;
	Component* l3 = new Leaf;
	
	Composite* p;

	//Add、Remove、GetChild前需要判断是否为组合节点
	if (p = h->GetComposite())
	{
		p->Add(l1);
		p->Add(c1);
	}
	if (p = c1->GetComposite())
	{
		c1->GetComposite()->Add(l2);
		c1->GetComposite()->Add(l3);
	}

	h->Operation(); //层次遍历

	if (p = l1->GetComposite())
	{
		//判断失败不会执行
		p->GetChild(0);
	}

	//l1->Add(l2);//throw异常
}
