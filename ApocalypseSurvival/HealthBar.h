#pragma once
#include "GameActor.h"
#include <iostream>
#include "utils.h"


class HealthBar : public GameActor
{
public:

	HealthBar(Point2f location, float maxHealth);

	void Update(float elapsedSec) override;
	void Draw() const override;

	void DamageHealth(float damagePoints);
	void RestoreHealth(float HealingPoints);

	float GetCurrentHealth();

private:

	float m_MaxHealth;
	float m_CurrentHealth;
	float m_Width;
	float m_Height;
};

