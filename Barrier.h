#pragma once

#include <iostream>
#include <barrier>
#include <Thread>
#include <vector>

// counter�� 0�� �Ǵ� phase complition �� ������ �Լ� ����
// Lambda�� barrier ������ �� �����Ѵ�.
std::barrier barrier{ 3, []() noexcept{
	std::cout << " phase completion" << std::endl;
} };

// barrier�� �����Ͽ� �� ��ȣ�� ��� ����ϰ� ���� ��ȣ�� ��µǴ�
// ����ȭ�� ������ �����Ѵ�.
void fn()
{
	std::cout << "1" << std::flush;
	barrier.arrive_and_wait();
	std::cout << "2" << std::flush;
	barrier.arrive_and_wait();
	std::cout << "3" << std::flush;
}

void BarrierTest()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 3; i++)
	{
		threads.emplace_back(std::thread(fn));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	std::cout << std::endl;
}