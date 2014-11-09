#pragma once

#include <iomanip>
#include <list>
#include <sstream>

#include "BaseEvent.h"

#define KEY_CURRENTLY_PRESSED_MASK (1 << 15)
#define KEY_PRESSED_SINCE_LAST_CALL 1

class KeyboardEvent : public BaseEvent
{
public:
	explicit KeyboardEvent(short virtualKeyCode);
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

#pragma region BaseEvent pverrides
public:
	virtual std::string toString(void)
	{
		std::ostringstream stream;
		stream << "[LocalTime: " << m_localTime.wYear << "/" << m_localTime.wMonth << "/" << m_localTime.wDay << "]";
		stream << "[SystemTime: " << m_systemTime.wYear << "/" << m_systemTime.wMonth << "/" << m_systemTime.wDay << "]";
		stream << "[Keyboard Event] "<< " KeyCode: 0x" << std::hex << m_virtualKeyCode << " ";
		stream << "Character: " << getCharacter();

		return stream.str();
	}
#pragma endregion

private:
	short m_virtualKeyCode;
};

class KeyboardMonitor
{
public:
	KeyboardMonitor(void);
	~KeyboardMonitor(void);

	void StartMonitor();

private:
	std::list<KeyboardEvent> m_keyboardEventList;
};

