#include <iostream>
#include <windows.h>
#include<winuser.h>

#include "KeyboardMonitor.h"


KeyboardMonitor::KeyboardMonitor(void)
{
}


KeyboardMonitor::~KeyboardMonitor(void)
{
}

void KeyboardMonitor::StartMonitor(void)
{
	while(1)
	{
		for (int i = 0x01; i <= 0xFE; ++i)
		{
			short result = GetAsyncKeyState(i);

			if (result & KEY_CURRENTLY_PRESSED_MASK > 0)
			{
				char character = MapVirtualKey(i, MAPVK_VK_TO_CHAR);
				std::cout << character << std::endl;
			}
		}
	}
}
