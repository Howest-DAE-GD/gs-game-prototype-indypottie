#include "pch.h"
#include "HealthBar.h"

HealthBar::HealthBar(Point2f location, float maxHealth)
	: GameActor(location)
	, m_MaxHealth		{ maxHealth }
	, m_CurrentHealth	{ maxHealth }
	, m_Width			{ maxHealth }
	, m_Height			{ maxHealth / 4.f }
{
	// nothing to do
}

void HealthBar::Update(float elapsedSec)
{

}

void HealthBar::Draw() const
{
	Rectf healthRect{ m_MyLocation.x , m_MyLocation.y, m_Width, m_Height };

	utils::SetColor(Color4f(0.55f, 0.0f, 0.0f, 1.f));

	utils::FillRect(healthRect);



	healthRect.width = m_MaxHealth;

	utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.f));

	utils::DrawRect(healthRect);
}

void HealthBar::DamageHealth(float damagePoints)
{
	m_CurrentHealth <= 0.f ? m_CurrentHealth = 0.f : m_CurrentHealth -= damagePoints;

	m_Width = m_CurrentHealth;

	std::cout << m_CurrentHealth << std::endl;
}

void HealthBar::RestoreHealth(float HealingPoints)
{
	m_CurrentHealth >= m_MaxHealth ? m_CurrentHealth = m_MaxHealth : m_CurrentHealth += HealingPoints;

	m_Width = m_CurrentHealth;
}

float HealthBar::GetCurrentHealth()
{
	return m_CurrentHealth;
}
