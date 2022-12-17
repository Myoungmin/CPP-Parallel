#pragma once

#include <chrono>
#include <iostream>
#include <latch>
#include <Thread>
#include <vector>

std::latch latch{ 3 };

void fn()
{
	std::cout << "decrease counter" << std::endl;
	latch.count_down();
	std::cout << "wait" << std::endl;
	latch.wait();
	std::cout << "rerun" << std::endl;
}

void LatchTest()
{
	std::vector<std::thread> threads;

	// �� ��° Thread���� count ���� 0�̵Ǿ� ������� �����.
	// count ���� 0���� count_down�� �� �����忡�� wait�� �����ص�, 
	// count�� 0�� �Ǿ��� ������ ��� �����Ѵ�.
	for (int i = 0; i < 3; i++)
	{
		using namespace std::literals;
		std::this_thread::sleep_for(500ms);
		threads.emplace_back(std::thread(fn));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
}