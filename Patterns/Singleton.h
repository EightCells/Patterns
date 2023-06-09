#pragma once
#ifndef __SINGLETON_H__
#define __SINGLETON_H__
#include <iostream>
#include <mutex>

/* 1. ����ʽ */
class Singleton1 {
public:
	static Singleton1* Instance()
	{
		return instance;
	}
private:
	static Singleton1* instance;
	Singleton1() {}
	Singleton1(const Singleton1&) = delete;
	Singleton1& operator=(Singleton1&) = delete;
};
//����ʼ�ͱ�����������̰߳�ȫ
Singleton1* Singleton1::instance = new Singleton1;

/* 2. �ֲ���̬�������Ǳ�׼������ʽ���������̰߳�ȫ�ģ� */
class Singleton2
{
public:
	//ֻ�е���һ�ε���Instanceʱ�ű�����
	static Singleton2* Instance()
	{
		static Singleton2* instance;
		return instance;
	}
private:
	Singleton2() {}
	Singleton2(const Singleton2&) = delete;
	Singleton2& operator=(Singleton2&) = delete;
};

/* 3. ˫���ж���������ǿʽ����ʽ�������̰߳�ȫ�� */
class Singleton3
{
public:
	static Singleton3* Instance()
	{
		//��һ���ж��Ǳ���ÿ�ζ�Ҫ����
		if (instance == nullptr)
		{
			/* ʹ��lock_guard���������������������Զ�������
			 * ����ں������ý�����mutex_���Զ�����������
			 * ����ʡȥ�ֶ�����unlock������
			 */
			std::lock_guard<std::mutex> lock/* = std::lock_guard<std::mutex>*/(mutex_);
			//�ڶ����ж�������Ч���̰߳�ȫ���ж�
			if (instance == nullptr)
			{
				instance = new Singleton3;
			}
		}
	}
private:
	static Singleton3* instance;
	static std::mutex mutex_;
	Singleton3() {}
	Singleton3(const Singleton3&) = delete;
	Singleton3& operator=(Singleton3&) = delete;
};
Singleton3* Singleton3::instance = nullptr;


#endif // !__SINGLETON_H__
