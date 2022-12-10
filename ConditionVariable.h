#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>

bool readyFlag = false;
std::mutex mtx;
std::condition_variable cv;

void WaitFn()
{
	std::cout << "wait" << std::endl;
	std::unique_lock<std::mutex> lck(mtx);
	

	//// 준비가 안되어 있을 경우만 wait가 되고, 
	//// 아닐 경우 바로 아래 지역으로 갈 수 있게하여
	//// Lost Wakeup을 방지한다.
	
	//while (!readyFlag)
	//{
	//	cv.wait(lck);
	//}

	// while문이 보기 싫을 경우
	// condition_variable의 wait Lock과 2번째 argument로 람다 함수를 넘겨주면 된다.
	cv.wait(lck, [] {return readyFlag; });


	// unlock은 안해줘도 상관없지만, 더 타이트하고 명시적으로 할 수 있게된다. 
	lck.unlock();

	// 아래 지역은 unique_lock로 보호되는 critical section이 된다.
	std::cout << "re run" << std::endl;
}

void SignalFn()
{
	std::cout << "signal" << std::endl;
	// 보호하는 곳을 한정하기 위해 스코프를 제한한다.
	{
		// 뮤텍스를 통해 보호한다.
		std::lock_guard<std::mutex> lck(mtx);
		readyFlag = true;
	}
	cv.notify_one();
}

void ConditionVariableTest()
{
	std::thread waitT(WaitFn);
	std::thread signalT(SignalFn);

	waitT.join();
	signalT.join();
}