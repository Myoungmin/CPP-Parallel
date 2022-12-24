#pragma once

#include <future>
#include <iostream>

void FuturePromiseTest()
{
	std::promise<int> prms;
	std::future<int> fut = prms.get_future();

	prms.set_value(123);

	const int num = fut.get();

	std::cout << "num : " << num << std::endl;
}