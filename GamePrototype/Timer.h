#pragma once
#include <functional>

class Timer final
{
public:
	// constructor(s)
	Timer(std::function<void()> classFunction, float delay = 0.f, bool loop = false);
	// destructor *not virtual -> final*
	~Timer();

	// general methods
	void Update(float elapsedSec);

	// Setter / mutators
	void Start();
	void Stop();

	void SetDelay(float newDelay);
	void IsLoopTimer(bool NewBool);

	void SetNewClassFunction(std::function<void()> classFunction);

	// getters
	bool IsRunning() const;

private:
	// data members
	float	m_Delay;
	float	m_AccumulatedSeconds;

	bool	m_IsLoopTimer;
	bool	m_IsRunning;

	std::function<void()> m_ClassFunction;
};

