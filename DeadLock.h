#pragma once

#include <iostream>
#include <mutex>

std::mutex mtxA;
std::mutex mtxB;

void ab()
{
	const std::lock_guard<std::mutex> lckA(mtxA);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	const std::lock_guard<std::mutex> lckB(mtxB);
}

void ba()
{
	const std::lock_guard<std::mutex> lckB(mtxB);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	const std::lock_guard<std::mutex> lckA(mtxA);
}

// 서로가 서로의 Lock이 UnLock이 되길 영원히 기다리게 된다.
// 이를 해결할 수 있는 방법은 뮤텍스를 언제나 ‘같은 순서’로 걸어주는 것이다.
void DeadLockTest()
{
	std::thread t1(ab);
	std::thread t2(ba);
	t1.join();
	t2.join();

	std::cout << "bye" << std::endl;
}