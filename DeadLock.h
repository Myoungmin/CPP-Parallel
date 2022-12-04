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

// ���ΰ� ������ Lock�� UnLock�� �Ǳ� ������ ��ٸ��� �ȴ�.
// �̸� �ذ��� �� �ִ� ����� ���ؽ��� ������ ������ �������� �ɾ��ִ� ���̴�.
void DeadLockTest()
{
	std::thread t1(ab);
	std::thread t2(ba);
	t1.join();
	t2.join();

	std::cout << "bye" << std::endl;
}