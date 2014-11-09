#pragma once

#define KEY_CURRENTLY_PRESSED_MASK (1 << 15)
#define KEY_PRESSED_SINCE_LAST_CALL 1

class KeyboardMonitor
{
public:
	KeyboardMonitor(void);
	~KeyboardMonitor(void);

	void StartMonitor();
};

