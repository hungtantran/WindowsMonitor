#include <iostream>
#include <memory>
#include <thread>

#include "KeyboardMonitor.h"
#include "ProcessMonitor.h"
#include "ThreadGuard.h"

#include "Monitor.h"

#define DEFAULT_KEYBOARD_LOG_PATH "C:\\Skydrive\\Dropbox\\Dropbox\\WindowsMonitor\\keyboard"
#define DEFAULT_PROCESS_LOG_PATH "C:\\Skydrive\\Dropbox\\Dropbox\\WindowsMonitor\\process"

Monitor::Monitor(void):
	m_writeToLog(false),
	m_logFilePath()
{
}

Monitor::Monitor(std::string logFilePath):
	m_writeToLog(true),
	m_logFilePath(logFilePath)
{
}

Monitor::~Monitor(void)
{
}

int main(int argc, const char* argv[])
{
	// Keyboard monitoring thread
	KeyboardMonitor keyboardMonitor(DEFAULT_KEYBOARD_LOG_PATH);
	
	std::thread keyboardMonitorThread(keyboardMonitor);
	ThreadGuard keyboardMonitorThreadGuard(keyboardMonitorThread);

	// Process monitoring thread
	ProcessMonitor processMonitor(DEFAULT_PROCESS_LOG_PATH);
	
	std::thread processMonitorThread(processMonitor);
	ThreadGuard processMonitorThreadGuard(processMonitorThread);
}