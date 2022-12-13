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
		m_vecStrs.emplace_back(std::move(s));
	}

	// Consumer
	std::string getStr()
	{
		std::string s = std::move(m_vecStrs.back());
		m_vecStrs.pop_back();
		return s;
	}

private:
	std::vector<std::string> m_vecStrs;
};

void ProducerConsumerTest()
{
	StrStack strStack;
	strStack.addStr("Job1");
	std::cout << strStack.getStr() << std::endl;
}