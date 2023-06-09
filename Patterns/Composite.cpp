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
		// std::remove����comp_�������ǣ��߼�ɾ�����Ƶ�ĩβ��ע�ⲻ��ı�size����
		// ���������һ��Ԫ����һ��λ�õĵ�������
		// ��˻�Ҫ����erase����Щƥ��Ķ�ɾ������ı�size����
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

	//Add��Remove��GetChildǰ��Ҫ�ж��Ƿ�Ϊ��Ͻڵ�
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

	h->Operation(); //��α���

	if (p = l1->GetComposite())
	{
		//�ж�ʧ�ܲ���ִ��
		p->GetChild(0);
	}

	//l1->Add(l2);//throw�쳣
}
