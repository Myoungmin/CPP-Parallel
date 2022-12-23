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
	// 비동기적으로 실행된 future의 결과값이 준비가 되지 않았다면,
	// 메인 쓰레드는 fut.get()에서 wait 상태가 되었다가, 
	// 값이 준비되면 num으로 대입되고 메인쓰레드가 계속 진행되게 된다.
	const int num = fut.get();

	std::cout << "return num : " << num << std::endl;
}