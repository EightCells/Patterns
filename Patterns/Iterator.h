#pragma once
#ifndef __ITERATOR_H__
#define __ITERATOR_H__
#include <iostream>
#include <vector>

template<class Item>
class List
{
public:
	List() :_size(0) {}

	const Item& Get(long index) const
	{
		return items[index];
	}

	void Insert(const Item& item)
	{
		items.push_back(item);
		_size++;
	}

	long count() const { return _size; }

private:
	std::vector<Item> items;
	long _size;
};

template<class Item>
class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual Item CurrentItem() const = 0;

protected:
	Iterator();
};

template<typename Item>
class ListIterator :public Iterator<Item>
{
public:
	ListIterator(const List<Item>* aList);
	virtual void First() override;
	virtual void Next() override;
	virtual bool IsDone() const override;
	virtual Item CurrentItem() const override;
private:
	const List<Item>* _list;
	long _current;
};

void ITest();


#endif // !__ITERATOR_H__

