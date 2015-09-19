#ifndef _TIMER_H_
#define _TIMER_H_

#include "glew\glew.h"
#include "GLFW\glfw3.h"

class Timer {
public:
	Timer() { m_lastTime = GetMS(); }
	~Timer() {}

	double GetMS();
	double GetTimedMS();

protected:
	double m_lastTime;
};

#endif