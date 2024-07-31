#include "pch.h"
#include "Clock.h"

Clock::Clock(Point2f location, float windowWidth, float windowHeight)
    : GameActor(location)
    , m_Hours(7)
    , m_Minutes(0)
    , m_Seconds(0)
    , m_WindowWidth(windowWidth)
    , m_WindowHeight(windowHeight)
    , m_SecsPerInGameHour(12.5f) //12.5f
    , m_CurrentDay(1)
    , m_DayTime(true)
{
    m_TimeString = (std::to_string(m_Hours) + " : " + std::to_string(m_Minutes) + " : " + std::to_string(m_Seconds));
    m_ClockTexturePtr = new Texture{ m_TimeString, "Poxast-R9Jjl.ttf", 25, Color4f(0.f, 0.f, 0.f, 1.f) };

    SetTime(7, 0, 0);
}

Clock::~Clock()
{
    delete m_ClockTexturePtr;
}

void Clock::Update(float elapsedSec)
{

    int previousHours = m_Hours;
    int previousMinutes = m_Minutes;
    int previousSeconds = m_Seconds;


    // Increment the in-game time
    float inGameSeconds = elapsedSec * (3600.0f / m_SecsPerInGameHour);

    int totalSeconds = static_cast<int>(m_Hours * 3600 + m_Minutes * 60 + m_Seconds + inGameSeconds);

    m_Hours = (totalSeconds / 3600) % 24;
    m_Minutes = (totalSeconds / 60) % 60;
    m_Seconds = totalSeconds % 60;

    if (previousHours == 6 && m_Hours == 7)
    {
        m_CurrentDay++;
        std::cout << "Day " << m_CurrentDay << std::endl;
        m_DayTime = true;

        std::cout << "day time" << std::endl;
    }

    if (previousHours == 19 and m_Hours == 20)
    {
        m_DayTime = false;
        std::cout << "night time" << std::endl;
    }

    UpdateTimeString();
}

void Clock::Draw() const
{
    m_ClockTexturePtr->Draw(m_MyLocation);
}

int Clock::GetHours() const
{
    return m_Hours;
}

int Clock::GetMinutes() const
{
    return m_Minutes;
}

int Clock::GetSeconds() const
{
    return m_Seconds;
}

int Clock::GetCurrentDay() const
{
    return m_CurrentDay;
}

bool Clock::GetDayTime() const
{
    return m_DayTime;
}

void Clock::UpdateTimeString()
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << m_Hours << ":"
        << std::setw(2) << std::setfill('0') << m_Minutes << ":"
        << std::setw(2) << std::setfill('0') << m_Seconds;

    m_TimeString = oss.str();

    delete m_ClockTexturePtr;
    m_ClockTexturePtr = new Texture{ m_TimeString, "Poxast-R9Jjl.ttf", 25, Color4f(0.f, 0.f, 0.f, 1.f) };

    m_MyLocation.x = (m_WindowWidth - 180.f);
    m_MyLocation.y = (m_WindowHeight - m_ClockTexturePtr->GetHeight());
}

void Clock::SetTime(int hours, int minutes, int seconds)
{
    m_Hours = hours % 24;
    m_Minutes = minutes % 60;
    m_Seconds = seconds % 60;
    UpdateTimeString();
}

void Clock::AddTime(int hours, int minutes, int seconds)
{
    int totalSeconds = static_cast<int>(m_Hours * 3600 + m_Minutes * 60 + m_Seconds + hours * 3600 + minutes * 60 + seconds);

    m_Hours = (totalSeconds / 3600) % 24;
    m_Minutes = (totalSeconds / 60) % 60;
    m_Seconds = totalSeconds % 60;

    UpdateTimeString();
}
