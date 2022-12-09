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

// ���� �����忡�� fn �Լ��� ȣ���ϴ���,
// call_once�� ���� �� ���� �ʱ�ȭ�Ѵ�.
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