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

	// 세 번째 Thread에서 count 값이 0이되어 블락에서 깨어난다.
	// count 값을 0으로 count_down을 한 쓰레드에서 wait를 실행해도, 
	// count가 0이 되었기 때문에 계속 실행한다.
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