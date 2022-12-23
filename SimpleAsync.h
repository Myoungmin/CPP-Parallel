#pragma once

#include <future>
#include <iostream>

int fn()
{
	std::cout << "async fn" << std::endl;
	return 123;
}

void SimpleAsyncTest()
{
	std::future<int> fut = std::async(std::launch::async, fn);
	// �񵿱������� ����� future�� ������� �غ� ���� �ʾҴٸ�,
	// ���� ������� fut.get()���� wait ���°� �Ǿ��ٰ�, 
	// ���� �غ�Ǹ� num���� ���Եǰ� ���ξ����尡 ��� ����ǰ� �ȴ�.
	const int num = fut.get();

	std::cout << "return num : " << num << std::endl;
}