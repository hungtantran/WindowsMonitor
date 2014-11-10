#pragma once

#include <thread>

class ThreadGuard
{
public:
	ThreadGuard(std::thread& thread);
	~ThreadGuard(void);

private:
	std::thread& m_thread;
};

