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

private:

	void UpdateSkycolor();

	Clock* m_ClockPtr;
	Color4f m_SkyColor;
	Rectf m_SkyRect;
};

