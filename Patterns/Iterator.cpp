#include "Iterator.h"

template<class Item>
Iterator<Item>::Iterator() {}

template<class Item>
ListIterator<Item>::ListIterator(const List<Item>* aList)
	:_list(aList), _current(0) {}

template<class Item>
void ListIterator<Item>::First()
{
	_current = 0;
}

template<class Item>
void ListIterator<Item>::Next()
{
	++_current;
}

template<class Item>
bool ListIterator<Item>::IsDone() const
{
	if (_current >= _list->count())return true;
	return false;
}


template<class Item>
Item ListIterator<Item>::CurrentItem() const
{
	if (IsDone()) return _list->Get(_list->count() - 1);
	return _list->Get(_current);
}

void ITest()
{
	List<int> l;
	l.Insert(1);
	l.Insert(1);
	l.Insert(4);
	l.Insert(5);
	l.Insert(1);
	l.Insert(4);

	const List<int>* li = &l;

	ListIterator<int> i(li);
	for (i.First(); !i.IsDone(); i.Next())
	{
		std::cout << i.CurrentItem();
	}
}
