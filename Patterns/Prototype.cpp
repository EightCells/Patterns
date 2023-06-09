#include "Prototype.h"

PrototypeClassA::PrototypeClassA(const PrototypeClassA& pa)
{
	this->num = pa.num;
	this->test = pa.test;
}

Prototype* PrototypeClassA::Clone()
{
	return new PrototypeClassA(*this);
}

void PrototypeClassA::Print()
{
	std::cout << "PrototypeClassA -> num: " << this->num << ", test num: " << this->test << std::endl;
}

PrototypeClassB::PrototypeClassB(const PrototypeClassB& pb)
{
	this->str = pb.str;
	this->test = pb.test;
}

Prototype* PrototypeClassB::Clone()
{
	return new PrototypeClassB(*this);
}

void PrototypeClassB::Print()
{
	std::cout << "PrototypeClassB -> str: " << this->str << ", test num: " << this->test << std::endl;
}

Prototype* PrototypeFactory::GetPrototype(std::string s)const
{
	return this->factory.at(s)->Clone();
}

void PrototypeFactory::AddPrototype(std::string s, Prototype* p)
{
	this->factory[s] = p;
}