#pragma once

#include <iostream>
#include <barrier>
#include <Thread>
#include <vector>

// counter가 0이 되는 phase complition 때 임의의 함수 실행
// Lambda를 barrier 생성할 때 설정한다.
std::barrier barrier{ 3, []() noexcept{
	std::cout << " phase completion" << std::endl;
} };

// barrier를 적용하여 각 번호를 모두 출력하고 다음 번호가 출력되는
// 동기화된 순서를 보장한다.
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