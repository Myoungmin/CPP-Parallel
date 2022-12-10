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
	

	//// �غ� �ȵǾ� ���� ��츸 wait�� �ǰ�, 
	//// �ƴ� ��� �ٷ� �Ʒ� �������� �� �� �ְ��Ͽ�
	//// Lost Wakeup�� �����Ѵ�.
	
	//while (!readyFlag)
	//{
	//	cv.wait(lck);
	//}

	// while���� ���� ���� ���
	// condition_variable�� wait Lock�� 2��° argument�� ���� �Լ��� �Ѱ��ָ� �ȴ�.
	cv.wait(lck, [] {return readyFlag; });


	// unlock�� �����൵ ���������, �� Ÿ��Ʈ�ϰ� ��������� �� �� �ְԵȴ�. 
	lck.unlock();

	// �Ʒ� ������ unique_lock�� ��ȣ�Ǵ� critical section�� �ȴ�.
	std::cout << "re run" << std::endl;
}

void SignalFn()
{
	std::cout << "signal" << std::endl;
	// ��ȣ�ϴ� ���� �����ϱ� ���� �������� �����Ѵ�.
	{
		// ���ؽ��� ���� ��ȣ�Ѵ�.
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