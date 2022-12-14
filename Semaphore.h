#pragma once

#include <iostream>
#include <thread>
#include <semaphore>

std::counting_semaphore<2> sp1(2);

void fn()
{
	sp1.acquire();
	std::cout << "semaphore region" << std::endl;
	
	// 아래를 주석하여 마지막 쓰레드는 wait하고 멈춰있는 것을 확인할 수 있다.
	//sp.release();
}

// 세마포어를 리소스 제한을 위해 사용하는 실습
void SemaphoreTest1()
{
	std::thread t1(fn);
	std::thread t2(fn);
	std::thread t3(fn);

	t1.join();
	t2.join();
	t3.join();
}


std::counting_semaphore<10> sp2(0);

void WaitFn()
{
	std::cout << "waiting" << std::endl;
	sp2.acquire();
	std::cout << "rerun" << std::endl;
}

void SignalFn()
{
	std::cout << "signal" << std::endl;
	sp2.release();
}

// 세마포어를 시그널 보내는 용도로 사용하는 실습
void SemaphoreTest2()
{
	std::thread waitT(WaitFn);
	std::thread signalT(SignalFn);

	waitT.join();
	signalT.join();
}