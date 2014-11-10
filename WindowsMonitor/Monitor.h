#pragma once

class Monitor
{
public:
	Monitor(void);
	Monitor(std::string m_logFilePath);
	~Monitor(void);

	virtual void operator()() = 0;

protected:
	bool m_writeToLog;
	std::string m_logFilePath;
};

