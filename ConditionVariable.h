#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;

void WaitFn()
{
	std::cout << "wait" << std::endl;
	std::unique_lock<std::mutex> lck(mtx);
	cv.wait(lck);
	std::cout << "re run" << std::endl;
}

void SignalFn()
{
	std::cout << "signal" << std::endl;
	cv.notify_one();
}

void ConditionVariableTest()
{
	std::thread waitT(WaitFn);
	std::thread signalT(SignalFn);

	waitT.join();
	signalT.join();
}