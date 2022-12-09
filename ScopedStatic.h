#pragma once

#include <iostream>
#include <thread>

class Singleton
{
public:
	static Singleton& getInstance()
	{
		// �ش� ������Ʈ�� getInstance�� ó�� ȣ��� ��,
		// ���� �� ���� ��������� ������ thread-safe �ϴ�.
		static Singleton sObj;
		return sObj;
	}

	// �߰����� ���� �ʿ�
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
	// Cat�� �ʱ�ȭ�� ���� �ѹ��� �Ͼ��.
	static Cat cat;
	// lazy init
	// ���μ����� ���۵� �� �ʱ�ȭ�Ǵ� ���� �ƴ϶�,
	// ���μ��� ���� �� fn�Լ��� ó�� ȣ��� �� �ʱ�ȭ�ȴ�.
}

void ScopedStaticTest()
{
	// ���α׷� ���� �� �Լ� fn�� ȣ��� �� Cat�� �ʱ�ȭ�Ǵ� ���� Ȯ���ϱ� ���� ���
	std::cout << "process starts" << std::endl;
	std::thread t1(fn);
	std::thread t2(fn);

	t1.join();
	t2.join();
}