#include "pch.h"
#include "Timer.h"

Timer::Timer(std::function<void()> classFunction, float delay, bool loop) : m_Delay{ delay }, m_IsLoopTimer{ loop }, m_ClassFunction{ classFunction }, m_AccumulatedSeconds{ 0.f }, m_IsRunning{ false }
{
	// nothing to do 
}

Timer::~Timer()
{

}

void Timer::Update(float elapsedSec)
{
	// check if timer is running
	if (!m_IsRunning) return;

	m_AccumulatedSeconds += elapsedSec;

	if (m_AccumulatedSeconds >= m_Delay)
	{
		if (m_IsLoopTimer)
		{
			m_AccumulatedSeconds -= m_Delay;
			m_ClassFunction();
			return;
		}
		else
		{
			m_ClassFunction();
			Stop();
			return;
		}
	}
}

void Timer::Start()
{
	m_IsRunning = true;
}

void Timer::Stop()
{
	m_IsRunning = false;
	m_AccumulatedSeconds = 0.f;
}

void Timer::SetDelay(float newDelay)
{
	m_Delay = newDelay;
}

void Timer::IsLoopTimer(bool NewBool)
{
	m_IsLoopTimer = NewBool;
}

void Timer::SetNewClassFunction(std::function<void()> classFunction)
{
	m_ClassFunction = classFunction;
}

bool Timer::IsRunning() const
{
	return m_IsRunning;
}