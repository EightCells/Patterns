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
	/* �����ĸ��ݲ������أ�ֻ�е�������
	����δ�����id�Żᵽ�˺�������ִ�� */
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
		//idΪ1��2֮��ʱ������ø����Create(id)�����3/4��1/2��Ч��Ӧ����һ����
		//�ɴ˿�֪�����԰Ѳ��ִ����ӳٵ�����ȥ���
		return Creator::Create(id);
		break;
	}
}

/*//1. ͨ��ģ����ʵ�־��崴���ߣ���ȡ��Ӧ�Ĳ�Ʒ
Creator* creator = new StandardCreator<ConcreteProductA>;
Product* product = creator->Create();
product->add();
ListNode* res = product->GetList();
DisplayList(res);

cout << endl;

//2. �ڴ������еĹ�������������������Ӷ�һ�������߿��Կ��ƶ����Ʒ�Ľ���
creator = new ConcreteCreatorByID;
product = creator->Create(2); //idΪ1��2֮��ʱ������ø����Create(id)�����3/4��1/2��Ч��Ӧ����һ����
product->add();
res = product->GetList();
DisplayList(res);

cout << endl;*/
