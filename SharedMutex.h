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
	// ���� �����̱� ������ Exclusive Lock�� �ɾ��ش�.
	
	mi.mtx.lock();
	mi.num = num;
	mi.mtx.unlock();
}

void PrintNum(MutexInt& mi)
{
	// �б� �����̱� ������ Shared Lock�� �ɾ��ش�.
	
	mi.mtx.lock_shared();
	std::cout << "num: " << mi.num << std::endl;
	mi.mtx.unlock_shared();
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