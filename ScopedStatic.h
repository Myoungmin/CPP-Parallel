#pragma once

#include <iostream>
#include <thread>

class Singleton
{
public:
	static Singleton& getInstance()
	{
		// 해당 오브젝트는 getInstance가 처음 호출될 때,
		// 오직 한 번만 만들어지기 때문에 thread-safe 하다.
		static Singleton sObj;
		return sObj;
	}

	// 추가적인 정의 필요
	// copy constructor, assignment = delete
};

class Cat
{
public:
	Cat()
	{
		std::cout << "meow" << std::endl;
	}
};

void fn()
{
	// Cat의 초기화는 오직 한번만 일어난다.
	static Cat cat;
	// lazy init
	// 프로세스가 시작될 때 초기화되는 것이 아니라,
	// 프로세스 진행 중 fn함수가 처음 호출될 때 초기화된다.
}

void ScopedStaticTest()
{
	// 프로그램 실행 중 함수 fn이 호출될 때 Cat이 초기화되는 것을 확인하기 위한 출력
	std::cout << "process starts" << std::endl;
	std::thread t1(fn);
	std::thread t2(fn);

	t1.join();
	t2.join();
}