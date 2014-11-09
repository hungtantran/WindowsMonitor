#pragma once

#include <string>
#include <windows.h>

enum EVENT_TYPE
{
	EVENT_NONE = 0,
	EVENT_KEYBOARD = 1
};

class BaseEvent
{
public:
	BaseEvent(void);
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

	virtual std::string toString(void) = 0;

protected:
	EVENT_TYPE m_type;

	SYSTEMTIME m_systemTime;
	SYSTEMTIME m_localTime;
};

