#pragma once

#include <iostream>
#include <shared_mutex>

struct MutexInt
{
	std::shared_mutex mtx;
	int num = 0;
};


void SetNum(MutexInt& mi, int num)
{
	// 쓰기 동작이기 때문에 Exclusive Lock을 걸어준다.

	/*mi.mtx.lock();
	mi.num = num;
	mi.mtx.unlock();*/

	// RAII 적용
	std::lock_guard<std::shared_mutex> lck(mi.mtx);
	mi.num = num;
}

void PrintNum(MutexInt& mi)
{
	// 읽기 동작이기 때문에 Shared Lock을 걸어준다.

	/*mi.mtx.lock_shared();
	std::cout << "num: " << mi.num << std::endl;
	mi.mtx.unlock_shared();*/

	// RAII 적용
	std::shared_lock<std::shared_mutex> lck(mi.mtx);
	std::cout << "num: " << mi.num << std::endl;
}


void SharedMutexTest()
{
	MutexInt mi;

	std::thread t0(PrintNum, std::ref(mi));
	std::thread t1(SetNum, std::ref(mi), 100);
	std::thread t2(PrintNum, std::ref(mi));
	std::thread t3(PrintNum, std::ref(mi));

	t0.join();
	t1.join();
	t2.join();
	t3.join();

	std::cout << "final num : " << mi.num << std::endl;
}