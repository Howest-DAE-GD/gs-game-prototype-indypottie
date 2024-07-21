#pragma once
#include "GameActor.h"
#include <iostream>
#include <iomanip>
#include <sstream>

class Clock : public GameActor
{
public:
    Clock(Point2f location, float windowWidth, float windowHeight);
    ~Clock();

    void Update(float elapsedSec) override;
    void Draw() const override;

    // Getters for time
    //int GetHours()   const;
    //int GetMinutes() const;
    //int GetSeconds() const;

private:

    void UpdateTimeString();

    float   m_TimeElapsed; // Total elapsed time in seconds
    int     m_Hours;
    int     m_Minutes;
    int     m_Seconds;

    const float m_SecsPerInGameHour{ (8 * 60.0f) / 24.0f };

    std::string m_TimeString;

    float m_WindowWidth;
    float m_WindowHeight;

    Texture* m_ClockTexturePtr;
};