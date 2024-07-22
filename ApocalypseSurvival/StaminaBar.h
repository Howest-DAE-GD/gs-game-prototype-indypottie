#pragma once
#include "GameActor.h"
#include "utils.h"


class StaminaBar : public GameActor
{
public:

	StaminaBar(Point2f location, float maxStamina);

	void Draw() const override;
	void Update(float elapsedSec) override;

	void Increase(float amount);
	void Decrease(float amount);

	float GetCurrentStamina() const;

private:

	float m_MaxStamina;
	float m_CurrentStamina;

};

