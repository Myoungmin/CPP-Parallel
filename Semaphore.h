#pragma once

#include <iostream>
#include <thread>
#include <semaphore>

std::counting_semaphore<2> sp1(2);

void fn()
{
	sp1.acquire();
	std::cout << "semaphore region" << std::endl;
	
	// �Ʒ��� �ּ��Ͽ� ������ ������� wait�ϰ� �����ִ� ���� Ȯ���� �� �ִ�.
	//sp.release();
}

// ������� ���ҽ� ������ ���� ����ϴ� �ǽ�
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

// ������� �ñ׳� ������ �뵵�� ����ϴ� �ǽ�
void SemaphoreTest2()
{
	std::thread waitT(WaitFn);
	std::thread signalT(SignalFn);

	waitT.join();
	signalT.join();
}