#pragma once
#include "GameActor.h"
#include "utils.h"
#include "ItemHUD.h"
#include <unordered_map>
#include <iostream>


class PlayerBase : public GameActor
{
public:

	PlayerBase(Point2f location, std::string filePath);
	~PlayerBase();


	void Update(float elapsedSec) override;
	void Draw() const override;
	void DrawHudElements() const;

	void CheckPlayerInteraction(const Point2f& playerLocation);

	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);

	void DepositFuel(int amount);

	bool GetFirePlaceInteractionPoint() const;

private:

	void InitializePoints();
	void BurnFire(float elapsedSec);

	std::unordered_map<std::string, Rectf> m_InteractionPointsUM;

	Rectf m_OuterRect;

	bool m_PlayerAtBed;
	bool m_PlayerAtFireplace;
	bool m_PlayerAtDoor;

	bool m_PlayerInBase;

	bool m_fireIsOn;

	int m_FuelLeft;
	int m_CurrentFuelPoints;

	float m_ElapsedTime;

	const float M_FUEL_DECREASE_RATE{ 2.5f };
	const int M_MAX_FUEL_POINTS{ 100 };

	ItemHUD*	m_CurrentFuelHUD;
};

