#include "FactoryMethod.h"

Product::Product()
{
	head = new ListNode("Default Product head");
	tail = head;
	length = 0;
}

void Product::add()
{
	ListNode* p = new ListNode("Add Default Node");
	tail->next = p;
	tail = p;
	length++;
}

ConcreteProductA::ConcreteProductA()
{
	Product::Product();
	head->str = "Product A head";
}

void ConcreteProductA::add()
{
	Product::add();
	tail->str = "Add Node A";
}

ConcreteProductB::ConcreteProductB()
{
	Product::Product();
	head->str = "Product B head";
}

void ConcreteProductB::add()
{
	Product::add();
	tail->str = "Add Node B";
}

Product* Creator::Create()
{
	return new Product;
}

Product* Creator::Create(int id)
{
	/* 基础的根据参数返回，只有当子类中
	遇到未定义的id才会到此函数继续执行 */
	switch (id)
	{
	case 3:
		return new ConcreteProductA;
		break;
	case 4:
		return new ConcreteProductB;
		break;
	default:
		return Create();
		break;
	}
}

Product* ConcreteCreatorByID::Create(int id)
{
	switch (id)
	{
	case 1:
		return new ConcreteProductA;
		break;
	case 2:
		return new ConcreteProductB;
		break;
	default:
		//id为1、2之外时，会调用父类的Create(id)，因此3/4和1/2的效果应该是一样的
		//由此可知，可以把部分创建延迟到父类去完成
		return Creator::Create(id);
		break;
	}
}

/*//1. 通过模板类实现具体创建者，获取对应的产品
Creator* creator = new StandardCreator<ConcreteProductA>;
Product* product = creator->Create();
product->add();
ListNode* res = product->GetList();
DisplayList(res);

cout << endl;

//2. 在创建者中的工厂方法中引入参数，从而一个建造者可以控制多个产品的建造
creator = new ConcreteCreatorByID;
product = creator->Create(2); //id为1、2之外时，会调用父类的Create(id)，因此3/4和1/2的效果应该是一样的
product->add();
res = product->GetList();
DisplayList(res);

cout << endl;*/
