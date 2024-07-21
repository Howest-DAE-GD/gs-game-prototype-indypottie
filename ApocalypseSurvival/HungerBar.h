#pragma once
#include "GameActor.h"
#include "utils.h"
#include <iostream>

class HungerBar : public GameActor
{
public:

    HungerBar(Point2f location, float maxHunger, float initialHunger);

    void Update(float elapsedSec) override;
    void Draw() const override;

    void Refill(float amount);
    void SetHungerDecreaseRate(float decreaseRate);

    float GetHunger() const;


private:

    float m_MaxHunger;
    float m_CurrentHunger;
    float m_HungerDecreaseRate;

};

