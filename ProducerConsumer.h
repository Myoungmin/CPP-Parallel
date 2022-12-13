#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class StrStack
{
public:
	// Producer
	void addStr(std::string s)
	{
		// vector를 lock_guard로 보호한다.
		{
			std::lock_guard<std::mutex> lck(m_Mtx);
			m_vecStrs.emplace_back(std::move(s));
		}
		// lock이 풀린 뒤 condition_variable를 통해 시그널을 보낸다.
		m_Cv.notify_one();
	}

	// Consumer
	std::string getStr()
	{
		// Consumer에서 vector에 접근하기 전에 unique_lock을 걸어주고
		std::unique_lock<std::mutex> lck(m_Mtx);
		// 해당 vector가 비어있다면 wait상태로 대기한다.
		while (m_vecStrs.empty())
		{
			m_Cv.wait(lck);
		}

		// vector안에 데이터가 있거나, wait 상태에서 깨어나면 데어터를 가져온다.
		std::string s = std::move(m_vecStrs.back());
		m_vecStrs.pop_back();

		// 데이터를 가져오면 mutex를 unlock 한다.
		// 어차피 unique_lock이라 해당함수를 종료하면 자동으로 unlock되지만,
		// 코드를 읽는 사람을 위해 명시적으로 해주는 것이 좋다.
		lck.unlock();

		return s;
	}

private:
	std::vector<std::string> m_vecStrs;
	std::mutex m_Mtx;
	std::condition_variable m_Cv;
};

void ProducerConsumerTest()
{
	StrStack strStack;

	std::thread t1([&]() {
		strStack.addStr("Job1");
		});

	std::thread t2([&]() {
		strStack.addStr("Job2");
		});

	std::thread t3([&]() {
		strStack.addStr("Job3");
		});

	std::thread t4([&]() {
		std::cout << strStack.getStr() << std::endl;
		});

	std::thread t5([&]() {
		std::cout << strStack.getStr() << std::endl;
		});

	std::thread t6([&]() {
		std::cout << strStack.getStr() << std::endl;
		});

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
}