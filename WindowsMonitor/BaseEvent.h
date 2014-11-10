#pragma once

#include <string>
#include <sstream>
#include <windows.h>

enum EVENT_TYPE
{
	EVENT_NONE = 0,
	EVENT_KEYBOARD = 1,
	EVENT_PROCESS = 2
};

class BaseEvent
{
public:
	BaseEvent(void);
	BaseEvent(const BaseEvent& other);
	~BaseEvent(void);

	EVENT_TYPE getEventType(void)
	{
		return m_type;
	}

	const SYSTEMTIME& getSystemTime(void)
	{
		return m_systemTime;
	}

	const SYSTEMTIME& getLocalTime(void)
	{
		return m_localTime;
	}

	virtual std::string toString(void)
	{
		std::ostringstream stream;
		stream << "[LocalTime: " << m_localTime.wYear << "/" << m_localTime.wMonth << "/" << m_localTime.wDay << " ";
		stream << m_localTime.wHour << ":" << m_localTime.wMinute << ":" << m_localTime.wSecond << ":" << m_localTime.wMilliseconds << "] ";

		return stream.str();
	}

protected:
	EVENT_TYPE m_type;

	SYSTEMTIME m_systemTime;
	SYSTEMTIME m_localTime;
};

