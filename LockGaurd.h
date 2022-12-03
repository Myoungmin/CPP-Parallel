#pragma once

#include <iostream>
#include <mutex>

struct MutexInt
{
	std::mutex mtx;
	int num = 0;
};


void plus1(MutexInt& mutexInt)
{
	// 자동적으로 그 아래쪽이 크리티컬 섹션으로 지정되면서,
	// 해당 스코프가 끝나면서 뮤텍스가 해제된다.
	std::lock_guard<std::mutex> lock(mutexInt.mtx);
	mutexInt.num++;
}

void LockGaurdTest()
{
	MutexInt mutexInt;
	std::thread t1(plus1, std::ref(mutexInt));
	std::thread t2(plus1, std::ref(mutexInt));

	t1.join();
	t2.join();

	std::cout << "num: " << mutexInt.num << std::endl;
}