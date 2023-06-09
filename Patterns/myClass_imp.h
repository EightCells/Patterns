#pragma once
#include "myClass.h"

myClass::myClass()
{
	data = 114514;
}

void myClass::setData(int d)
{
	data = d;
}

int myClass::getData()
{
	return data;
}