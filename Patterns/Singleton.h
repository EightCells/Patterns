#pragma once
#ifndef __SINGLETON_H__
#define __SINGLETON_H__
#include <iostream>
#include <mutex>

/* 1. 饿汉式 */
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
//程序开始就被创建，因此线程安全
Singleton1* Singleton1::instance = new Singleton1;

/* 2. 局部静态变量（非标准的懒汉式，但它是线程安全的） */
class Singleton2
{
public:
	//只有当第一次调用Instance时才被创建
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

/* 3. 双重判定加锁（加强式懒汉式，但是线程安全） */
class Singleton3
{
public:
	static Singleton3* Instance()
	{
		//第一重判定是避免每次都要加锁
		if (instance == nullptr)
		{
			/* 使用lock_guard变量，它的析构函数会自动解锁，
			 * 因此在函数调用结束，mutex_会自动解锁，这样
			 * 可以省去手动调用unlock函数。
			 */
			std::lock_guard<std::mutex> lock/* = std::lock_guard<std::mutex>*/(mutex_);
			//第二重判定才是有效的线程安全的判定
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
