#include "pch.h"
#include "HungerBar.h"

HungerBar::HungerBar(Point2f location, float maxHunger, float initialHunger)
    : GameActor(location)
    , m_MaxHunger(maxHunger) 
    , m_CurrentHunger(initialHunger)
    , m_HungerDecreaseRate(0.15f) // Example decrease rate per second
{
    // nothing to do
}


void HungerBar::Update(float elapsedSec)
{
    // Decrease hunger over time
    m_CurrentHunger -= m_HungerDecreaseRate * elapsedSec;

    if (m_CurrentHunger < 0.f)
    {
        m_CurrentHunger = 0.f;
    }
}

void HungerBar::Draw() const
{
    Rectf HungerRect{ m_MyLocation.x , m_MyLocation.y, m_CurrentHunger, m_MaxHunger / 4.f };

    utils::SetColor(Color4f(0.36f, 0.25f, 0.2f, 1.f));

    utils::FillRect(HungerRect);



    HungerRect.width = m_MaxHunger;

    utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.f));

    utils::DrawRect(HungerRect);
}

void HungerBar::Refill(float amount)
{
    m_CurrentHunger += amount;
    if (m_CurrentHunger > m_MaxHunger)
    {
        m_CurrentHunger = m_MaxHunger;
    }
}

void HungerBar::SetHungerDecreaseRate(float decreaseRate)
{
    m_HungerDecreaseRate = decreaseRate;
}

float HungerBar::GetHunger() const
{
    return m_CurrentHunger;
}
