#include "KeyboardMonitor.h"

#include "Monitor.h"


Monitor::Monitor(void)
{
}


Monitor::~Monitor(void)
{
}

int main(int argc, const char* argv[])
{
	KeyboardMonitor keyboardMonitor;
	keyboardMonitor.StartMonitor();
}