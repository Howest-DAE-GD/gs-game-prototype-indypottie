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
	void StoreFood(int amount);

	int GetCurrentStoredFood();

	bool GetFirePlaceInteractionPoint() const;
	bool GetDoorInteractionPoint() const;
	bool GetBedInteractionPoint() const;

	bool GetIsPlayerInBase() const;
	bool GetIsFireOn() const;

	void RemoveFood(int amount);
	void RemoveWood(int amount);

	Point2f GetCenterPoint() const;

	void SetInventoryColor(Color4f color);

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

	int m_StoredFood;

	float m_ElapsedTime;

	const float M_FUEL_DECREASE_RATE{ 0.125f };
	const int M_MAX_FUEL_POINTS{ 100 };

	ItemHUD*	m_CurrentFuelHUD;
	ItemHUD*	m_FoodStoredHUD;

	Texture*	m_BaseFireOnTexture;
};

