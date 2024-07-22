#include "pch.h"
#include "StaminaBar.h"

StaminaBar::StaminaBar(Point2f location, float maxStamina)
	: GameActor(location)
	, m_MaxStamina		{ maxStamina }
	, m_CurrentStamina	{ maxStamina }
{
	// nothing to do
}

void StaminaBar::Draw() const
{

	Rectf staminaRect{ m_MyLocation.x , m_MyLocation.y, m_CurrentStamina, m_MaxStamina / 4.f };

	utils::SetColor(Color4f(0.f, 1.f, 1.f, 1.f));

	utils::FillRect(staminaRect);



	staminaRect.width = m_MaxStamina;

	utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.f));

	utils::DrawRect(staminaRect);

}

void StaminaBar::Update(float elapsedSec)
{
}

void StaminaBar::Increase(float amount)
{
	m_CurrentStamina += amount;
	if (m_CurrentStamina > m_MaxStamina)
	{
		m_CurrentStamina = m_MaxStamina;
	}
}

void StaminaBar::Decrease(float amount)
{
	m_CurrentStamina -= amount;
	if (m_CurrentStamina < 0.0f)
	{
		m_CurrentStamina = 0.0f;
	}
}

float StaminaBar::GetCurrentStamina() const
{
	return m_CurrentStamina;
}
