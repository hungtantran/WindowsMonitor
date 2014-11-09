#include <iostream>
#include <windows.h>
#include<winuser.h>

#include "KeyboardMonitor.h"

KeyboardEvent::KeyboardEvent(short virtualKeyCode):
	BaseEvent(),
	m_virtualKeyCode(virtualKeyCode)
{
	m_type = EVENT_KEYBOARD;
}

KeyboardMonitor::KeyboardMonitor(void)
{
}


KeyboardMonitor::~KeyboardMonitor(void)
{
}

void KeyboardMonitor::StartMonitor(void)
{
	int count = 0;

	while(1)
	{
		for (int virtualKeyCode = 0x01; virtualKeyCode <= 0xFE; ++virtualKeyCode)
		{
			short result = GetAsyncKeyState(virtualKeyCode);

			if (result & KEY_CURRENTLY_PRESSED_MASK > 0)
			{
				m_keyboardEventList.emplace_back(KeyboardEvent(virtualKeyCode));

				std::cout << m_keyboardEventList.back().toString() << std::endl;
			}
		}
	}
}
