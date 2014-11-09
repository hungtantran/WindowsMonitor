#include "BaseEvent.h"


BaseEvent::BaseEvent(void):
	m_type(EVENT_NONE)
{
	::GetSystemTime(&m_systemTime);
	::GetLocalTime(&m_localTime);
}


BaseEvent::~BaseEvent(void)
{
}
