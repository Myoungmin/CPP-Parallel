#pragma once

#include <iostream>
#include <mutex>

std::mutex mtxA;
std::mutex mtxB;

void ab()
{
	const std::scoped_lock lck(mtxA, mtxB);
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void ba()
{
	const std::scoped_lock lck(mtxB, mtxA);
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

// scoped_lock�� ����ϸ� �츮�� scoped_lock�� �Ѱ��ִ� mutex�� ������ ������� 
// �˾Ƽ� ���������� ���� mutex Lock ������ �ش� mutex�� ȹ���Ϸ��� �õ��Ѵ�.
void ScopedLockTest()
{
	std::thread t1(ab);
	std::thread t2(ba);
	t1.join();
	t2.join();

	std::cout << "bye" << std::endl;
}