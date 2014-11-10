#include "BaseEvent.h"


BaseEvent::BaseEvent(void):
	m_type(EVENT_NONE)
{
	::GetSystemTime(&m_systemTime);
	::GetLocalTime(&m_localTime);
}

BaseEvent::BaseEvent(const BaseEvent& other)
{
	m_type = other.m_type;
	m_systemTime = other.m_systemTime;
	m_localTime = other.m_localTime;
}

BaseEvent::~BaseEvent(void)
{
}
