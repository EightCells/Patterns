#pragma once
#ifndef __COMPOSITE_H__
#define __COMPOSITE_H__

#include <vector>

class Componet;
class Leaf;
class Composite;

class Component
{
public:
	virtual void Operation() = 0;
	/*virtual void Add(Component*);
	virtual void Remove(Component*);
	virtual Component* GetChild(int);*/
	virtual Composite* GetComposite();
};

class Leaf :public Component
{
public:
	virtual void Operation() override;
};

class Composite :public Component
{
public:
	virtual void Operation() override;
	void Add(Component*);
	void Remove(Component*);
	Component* GetChild(int);
	virtual Composite* GetComposite() override;
private:
	std::vector<Component*> children;
};

void CompositeTest();

#endif // !__COMPOSITE_H__
