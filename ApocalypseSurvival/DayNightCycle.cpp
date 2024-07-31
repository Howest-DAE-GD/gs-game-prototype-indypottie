#include "pch.h"
#include "DayNightCycle.h"

DayNightCycle::DayNightCycle(Point2f clockLocation, float windowWidth, float windowHeight)
	: m_ClockPtr{ new Clock(clockLocation, windowWidth, windowHeight) }
	, m_SkyColor{ 0.f,0.f,0.f,0.5f }
	, m_SkyRect{ 0.f,0.f, windowWidth, windowHeight }
{
	// nothing to do
}

DayNightCycle::~DayNightCycle()
{
	delete m_ClockPtr;
}

void DayNightCycle::Update(float elapsedSec)
{
	m_ClockPtr->Update(elapsedSec);
	UpdateSkycolor();
}

void DayNightCycle::Draw() const
{
	utils::SetColor(m_SkyColor);
	utils::FillRect(m_SkyRect);

	m_ClockPtr->Draw();
}

int DayNightCycle::GetCurrentDay()
{
    return m_ClockPtr->GetCurrentDay();
}

bool DayNightCycle::GetDayTime() const
{
    return m_ClockPtr->GetDayTime();
}

void DayNightCycle::UpdateSkycolor()
{
    int hour = m_ClockPtr->GetHours();
    int minute = m_ClockPtr->GetMinutes();
    int second = m_ClockPtr->GetSeconds();
    int totalMinutes = hour * 60 + minute;

    // Determine alpha based on time of day
    float alpha;

    if (totalMinutes >= 300 && totalMinutes < 420)
    {
        alpha = 0.85f - (totalMinutes - 300) / 120.0f;
    }
    // Daytime (7 AM - 5 PM)
    else if (totalMinutes >= 420 && totalMinutes < 1020)
    {
        alpha = 0.0f;
    }
    // Evening transition (5 PM - 8 PM)
    else if (totalMinutes >= 1020 && totalMinutes < 1200)
    {
        alpha = 0.85f * (totalMinutes - 1020) / 180.0f;
    }
    // Nighttime (8 PM - 5 AM)
    else
    {
        alpha = 0.85f;
    }

    // Set the sky color with the calculated alpha
    m_SkyColor = { Color4f(0.0f, 0.0f, 0.0f, alpha) };

}
