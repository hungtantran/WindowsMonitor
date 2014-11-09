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
	keyboardMonitor.StartMonitor();
}