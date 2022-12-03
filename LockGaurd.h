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
	// �ڵ������� �� �Ʒ����� ũ��Ƽ�� �������� �����Ǹ鼭,
	// �ش� �������� �����鼭 ���ؽ��� �����ȴ�.
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