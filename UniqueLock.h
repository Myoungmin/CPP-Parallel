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

	// Mutex�� �����ϴ� unique_lock�� �ٸ� �Լ��� ������ ��ȯ�Ѵ�.
	
	// unique_lock�� ���� move�� �����ϱ� ������
	// std::move�� R-Value�� �����ؼ� Argument�� �Ѱܾ��Ѵ�.
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