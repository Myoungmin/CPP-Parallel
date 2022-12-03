#pragma once

#include <iostream>
#include <mutex>

struct MutexInt
{
	std::mutex mtx;
	int num = 0;
};

std::unique_lock<std::mutex> unlockTest(std::unique_lock<std::mutex> lck)
{
	if (true)
	{
		lck.unlock();
	}
	return lck;
}

void plus1(MutexInt& mutexInt)
{
	std::unique_lock<std::mutex> lock(mutexInt.mtx);
	mutexInt.num++;

	// Mutex를 관리하는 unique_lock을 다른 함수로 보내고 반환한다.
	
	// unique_lock은 오직 move만 가능하기 때문에
	// std::move로 R-Value로 변경해서 Argument로 넘겨야한다.
	lock = unlockTest(std::move(lock));
}

void UniqueLockTest()
{
	MutexInt mutexInt;
	std::thread t1(plus1, std::ref(mutexInt));
	std::thread t2(plus1, std::ref(mutexInt));

	t1.join();
	t2.join();

	std::cout << "num: " << mutexInt.num << std::endl;
}