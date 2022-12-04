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

// scoped_lock을 사용하면 우리가 scoped_lock에 넘겨주는 mutex의 순서와 상관없이 
// 알아서 내부적으로 정한 mutex Lock 순서로 해당 mutex를 획득하려고 시도한다.
void ScopedLockTest()
{
	std::thread t1(ab);
	std::thread t2(ba);
	t1.join();
	t2.join();

	std::cout << "bye" << std::endl;
}