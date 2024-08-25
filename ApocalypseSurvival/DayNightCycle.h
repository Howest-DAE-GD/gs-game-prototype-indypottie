#pragma once
#include "Clock.h"
#include "utils.h"


class DayNightCycle
{
public:
	DayNightCycle(Point2f clockLocation, float windowWidth, float windowHeight);
	~DayNightCycle();

	void Update(float elapsedSec);
	void Draw() const;

	// getters
	int GetCurrentDay();

	bool GetDayTime() const;

	void SetTime(int hours, int minutes, int seconds);
	void SetDay(int day);

	int GetHour();
	int GetMinutes();
	int GetSeconds();

	void SetClockColor(Color4f color);

private:

	void UpdateSkycolor();

	Clock* m_ClockPtr;
	Color4f m_SkyColor;
	Rectf m_SkyRect;
};

