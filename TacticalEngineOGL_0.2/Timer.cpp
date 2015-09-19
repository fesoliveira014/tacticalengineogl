#include "Timer.h"

double Timer::GetMS() {
	return 1.0f * glfwGetTime();
}

double Timer::GetTimedMS() {
	double currentTime = GetMS();
	double deltaTime = currentTime - m_lastTime;

	m_lastTime = currentTime;

	return deltaTime;
}