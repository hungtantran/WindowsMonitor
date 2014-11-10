#include <iostream>

#include "ThreadGuard.h"


ThreadGuard::ThreadGuard(std::thread& thread):
	m_thread(thread)
{
}


ThreadGuard::~ThreadGuard(void)
{
	if (m_thread.joinable())
	{
		m_thread.join();
	}

	std::cout << "Thread " << m_thread.get_id() << " finishes" << std::endl;
}
