#include <iostream>
#include <memory>
#include <thread>

#include "KeyboardMonitor.h"

#include "Monitor.h"

#define DEFAULT_LOG_PATH "C:\\Skydrive\\Dropbox\\Dropbox\\WindowsMonitor\\keyboard"

Monitor::Monitor(void)
{
}

Monitor::~Monitor(void)
{
}

int main(int argc, const char* argv[])
{
	KeyboardMonitor keyboardMonitor(DEFAULT_LOG_PATH);
	
	std::thread keyboardMonitorThread(keyboardMonitor);

	std::cout << "Start Monitoring" << std::endl;
	keyboardMonitorThread.join();
	std::cout << "End Monitoring" << std::endl;
}