#include "pch.h"
#include "Clock.h"

Clock::Clock(Point2f location, float windowWidth, float windowHeight)
	: GameActor(location)
    , m_TimeElapsed(0.0f)
    , m_Hours(0)
    , m_Minutes(0)
    , m_Seconds(0)
    , m_WindowWidth(windowWidth)
    , m_WindowHeight(windowHeight)
{
    m_TimeString = (std::to_string(m_Hours) + " : " + std::to_string(m_Minutes) + " : " + std::to_string(m_Seconds));
    m_ClockTexturePtr = new Texture{ m_TimeString,"Poxast-R9Jjl.ttf",25 ,Color4f(0.f,0.f,0.f,1.f) };
}

Clock::~Clock()
{
    delete m_ClockTexturePtr;
}

void Clock::Update(float elapsedSec)
{
    m_TimeElapsed += elapsedSec;

    // Calculate in-game time
    float inGameSeconds = m_TimeElapsed * m_SecsPerInGameHour; // Convert real seconds to in-game seconds

    m_Hours   = static_cast<int>(inGameSeconds / 3600) % 24;
    m_Minutes = static_cast<int>(inGameSeconds / 60) % 60;
    m_Seconds = static_cast<int>(inGameSeconds) % 60;

    UpdateTimeString();
}

void Clock::Draw() const
{
    m_ClockTexturePtr->Draw(m_MyLocation);
}

void Clock::UpdateTimeString()
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << m_Hours << ":"
        << std::setw(2) << std::setfill('0') << m_Minutes << ":"
        << std::setw(2) << std::setfill('0') << m_Seconds;

    m_TimeString = oss.str();

    delete m_ClockTexturePtr;

    m_ClockTexturePtr = new Texture{ m_TimeString,"Poxast-R9Jjl.ttf",25 ,Color4f(0.f,0.f,0.f,1.f) };

    m_MyLocation.x = (m_WindowWidth - 180.f);
    m_MyLocation.y = (m_WindowHeight - m_ClockTexturePtr->GetHeight());
}
