#pragma once

#include <list>
#include <memory>
#include <sstream>
#include <unordered_map>

#include "BaseEvent.h"
#include "Monitor.h"

class ProcessEvent : public BaseEvent
{
public:
	ProcessEvent(const DWORD& processId, std::string& processName);
	ProcessEvent(const ProcessEvent& other);
	~ProcessEvent();

	const SYSTEMTIME& getStartTime(void) const
	{
		return m_startTime;
	}

	const SYSTEMTIME& getEndTime(void) const
	{
		return m_endTime;
	}

	const DWORD& getProcessId(void) const
	{
		return m_processId;
	}

	const std::string& getProcesdName(void) const
	{
		return m_processName;
	}

	void endProcess(void)
	{
		::GetLocalTime(&m_endTime);
	}

#pragma region BaseEvent pverrides
public:
	virtual std::string toString(void)
	{
		std::ostringstream stream;
		stream << "[LocalTime: " << m_localTime.wYear << "/" << m_localTime.wMonth << "/" << m_localTime.wDay << " ";
		stream << m_localTime.wHour << ":" << m_localTime.wMinute << ":" << m_localTime.wSecond << ":" << m_localTime.wMilliseconds << "] ";
		stream << "[Process Event] ";
		stream << "Start time: "  << m_startTime.wHour << ":" << m_startTime.wMinute << ":" << m_startTime.wSecond << ":" << m_startTime.wMilliseconds << ", ";
		stream << "End time: "  << m_endTime.wHour << ":" << m_endTime.wMinute << ":" << m_endTime.wSecond << ":" << m_endTime.wMilliseconds << ", ";
		stream << "ProcessId: " << m_processId << ", ";
		stream << "ProcessName: " << m_processName;

		return stream.str();
	}
#pragma endregion

private:
	DWORD m_processId;
	std::string m_processName;

	SYSTEMTIME m_startTime;
	SYSTEMTIME m_endTime;
};

class ProcessMonitor : public Monitor
{
public:
	ProcessMonitor(void);
	ProcessMonitor(const std::string logFilePath);
	~ProcessMonitor(void);

#pragma region Monitor overrides
public:
	virtual void operator()();
#pragma endregion

private:
	void AddNewProcess(DWORD processId);

private:
	std::unordered_map<DWORD, std::shared_ptr<ProcessEvent>> m_processIdMap;
	std::list<std::shared_ptr<ProcessEvent>> m_processEventList;
	std::list<std::shared_ptr<ProcessEvent>> m_finishedProcessEventList;
};

