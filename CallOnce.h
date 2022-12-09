#pragma once

#include <iostream>
#include <mutex>

class Cat
{
public:
	Cat()
	{
		std::cout << "init cat" << std::endl;
	}
	void speak()
	{
		std::cout << "meow" << std::endl;
	}
};

std::once_flag flag;
std::unique_ptr<Cat> cp = nullptr;

// 여러 쓰레드에서 fn 함수를 호출하더라도,
// call_once로 오직 한 번만 초기화한다.
void fn()
{
	std::call_once(flag, []() {
		cp = std::make_unique<Cat>();
		});
}

void CallOnceTest()
{
	std::thread t1(fn);
	std::thread t2(fn);
	std::thread t3(fn);
	std::thread t4(fn);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	cp->speak();
}