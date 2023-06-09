#include "SimpleList.h"
#include <iostream>

void DisplayList(ListNode* p)
{
	while (p->next != NULL)
	{
		std::cout << p->str << " -> ";
		p = p->next;
	}
	std::cout << p->str << std::endl;
}