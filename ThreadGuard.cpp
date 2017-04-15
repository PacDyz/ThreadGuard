// ConsoleApplication22esfse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

namespace Printer
{
	void function1(std::mutex&);
	void function2(std::mutex&);
	void function3(const int&, std::mutex&);
	void function4(std::mutex&);
};
int main()
{
	std::mutex mut;
	std::thread t1(&Printer::function1, std::ref(mut));
	std::thread t2(&Printer::function2, std::ref(mut));
	std::thread t3(&Printer::function2, std::ref(mut));
	for (int i = 0; i < 10; i++)
	{
		std::lock_guard<std::mutex> locker(mut);
		std::cout << i << std::endl;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	for (int i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(5));
		Printer::function3(i+100, mut);
	}
	std::thread t4(&Printer::function4, std::ref(mut));
	t1.join();
	t2.join();
	t3.join();
	t4.join();
    return 0;
}

void Printer::function1(std::mutex& mut)
{
	for (int i = 0; i < 500; ++i)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(2));
		std::lock_guard<std::mutex> locker(mut);
		if (i % 2)
			std::cout << "i isn't odd " << std::endl;
		else
			std::cout << "i is odd: " << i << std::endl;
	}
}
void Printer::function2(std::mutex& mut)
{
	for (int i = 0; i < 10; ++i)
	{
		std::lock_guard<std::mutex> locker(mut);
		if (i % 2)
			std::cout << "f2: i isn't odd " << std::endl;
		else
			std::cout << "f2: i is odd: " << i << std::endl;
	}
}

void Printer::function3(const int& i, std::mutex& mut)
{
	std::lock_guard<std::mutex> locker(mut);
	std::cout << "function3: " << i << std::endl;
}
void Printer::function4(std::mutex& mut)
{
	for (int i = 0; i < 10; i++)
	{
		Printer::function3(i, mut);
	}
}