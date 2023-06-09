#pragma once
#ifndef __SIMPLE_LIST_H__
#define __SIMPLE_LIST_H__

typedef struct ListNode
{
	const char* str;
	ListNode* next;

	ListNode(const char* s)
	{
		str = s;
		next = nullptr;
	}
}ListNode;

void DisplayList(ListNode* p);

#endif // !__SIMPLE_LIST_H__
