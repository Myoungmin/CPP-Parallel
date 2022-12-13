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
		// vector�� lock_guard�� ��ȣ�Ѵ�.
		{
			std::lock_guard<std::mutex> lck(m_Mtx);
			m_vecStrs.emplace_back(std::move(s));
		}
		// lock�� Ǯ�� �� condition_variable�� ���� �ñ׳��� ������.
		m_Cv.notify_one();
	}

	// Consumer
	std::string getStr()
	{
		// Consumer���� vector�� �����ϱ� ���� unique_lock�� �ɾ��ְ�
		std::unique_lock<std::mutex> lck(m_Mtx);
		// �ش� vector�� ����ִٸ� wait���·� ����Ѵ�.
		while (m_vecStrs.empty())
		{
			m_Cv.wait(lck);
		}

		// vector�ȿ� �����Ͱ� �ְų�, wait ���¿��� ����� �����͸� �����´�.
		std::string s = std::move(m_vecStrs.back());
		m_vecStrs.pop_back();

		// �����͸� �������� mutex�� unlock �Ѵ�.
		// ������ unique_lock�̶� �ش��Լ��� �����ϸ� �ڵ����� unlock������,
		// �ڵ带 �д� ����� ���� ��������� ���ִ� ���� ����.
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