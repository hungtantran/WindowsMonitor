#include <windows.h>
#include <psapi.h>
#include <iostream>

#include "ProcessMonitor.h"

ProcessEvent::ProcessEvent(const DWORD& processId, std::string& processName):
	m_processId(processId),
	m_processName(processName)
{
	m_type = EVENT_PROCESS;
	::GetLocalTime(&m_startTime);
}

ProcessEvent::ProcessEvent(const ProcessEvent& other)
{
	BaseEvent::BaseEvent(other);
	m_processId = other.m_processId;
	m_processName = other.m_processName;
	m_startTime = other.m_startTime;
	m_endTime = other.m_endTime;
}

ProcessEvent::~ProcessEvent()
{
}

ProcessMonitor::ProcessMonitor(void):
	Monitor(),
	m_processIdMap(),
	m_processEventList(),
	m_finishedProcessEventList()
{
}

ProcessMonitor::ProcessMonitor(const std::string logFilePath):
	Monitor(logFilePath),
	m_processIdMap(),
	m_processEventList(),
	m_finishedProcessEventList()
{
}

ProcessMonitor::~ProcessMonitor(void)
{
	Monitor::~Monitor();
}

#pragma region Monitor overrides
void ProcessMonitor::operator()()
{
	int count = 0;
	DWORD processIds[256];
	DWORD pBytesReturned;
	DWORD processIdsSize = sizeof(processIds);

	while(true)
	{
		if (!EnumProcesses(processIds, processIdsSize, &pBytesReturned))
		{
			continue;
		}

		DWORD numProcesses = pBytesReturned / sizeof(DWORD);
		
		// Find processes that have already finsihed
		auto iter = m_processEventList.begin();
		while (iter != m_processEventList.end())
		{
			std::shared_ptr<ProcessEvent> processEvent = *iter;

			bool foundProcess = false;
			for (DWORD i = 0; i < numProcesses; ++i)
			{
				if (processIds[i] == processEvent->getProcessId())
				{
					foundProcess = true;
					break;
				}
			}

			if (!foundProcess)
			{
				std::cout << "Finished PID: " << processEvent->getProcessId() << " : " << processEvent->getProcesdName() << std::endl;

				// Remove finished process
				processEvent->endProcess();
				m_processIdMap.erase(m_processIdMap.find(processEvent->getProcessId()));
				m_finishedProcessEventList.emplace_back(processEvent);
				iter = m_processEventList.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		// Find new process and add to list and map
		for (DWORD i = 0; i < numProcesses; ++i)
		{
			if (m_processIdMap.find(processIds[i]) == m_processIdMap.end())
			{
				std::cout << "Add new PID: " << processIds[i] << std::endl;
				AddNewProcess(processIds[i]);
			}
		}
	}
}
#pragma endregion

void ProcessMonitor::AddNewProcess(DWORD processId)
{
    HANDLE process = OpenProcess(
		PROCESS_ALL_ACCESS,
		FALSE,
		processId);

	std::string processName = "<unknown>";

	if (process != nullptr)
    {
        HMODULE moduleHandles[256];
        DWORD numBytesReturned;

        if (EnumProcessModules(
			process,
			moduleHandles,
			sizeof(moduleHandles),
			&numBytesReturned))
        {
			DWORD numModules = numBytesReturned / sizeof(HMODULE);
			std::cout << "Found " << numModules << " modules" << std::endl;

			/*for (DWORD i = 0; i < numModules; ++i)
			{
				TCHAR processName[MAX_PATH] = TEXT("<unknown>");

				GetModuleBaseName(
					process,
					moduleHandles[i],
					processName,
					sizeof(processName)/sizeof(TCHAR));

				// Print the process name and identifier.
				std::cout << "ProcessName: " << processName << " (PID: "  << processId << ")" << std::endl;
			}*/

			TCHAR processNameChar[MAX_PATH] = TEXT("<unknown>");

			GetModuleBaseName(
				process,
				moduleHandles[0],
				processNameChar,
				sizeof(processNameChar)/sizeof(TCHAR));

			// Print the process name and identifier.
			std::cout << "ProcessName: " << processNameChar << " (PID: "  << processId << ")" << std::endl;
			
			processName = std::string(processNameChar);
        }
    }
	else
	{
		std::cout << "Unexpected can't find PID " << processId << std::endl;
	}

	ProcessEvent* event = new ProcessEvent(processId, processName);
	
	std::shared_ptr<ProcessEvent> eventPtr;
	eventPtr.reset(event);

	m_processIdMap.emplace(processId, eventPtr);
	m_processEventList.emplace_back(eventPtr);

    CloseHandle(process);
}
