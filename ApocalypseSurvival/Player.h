#pragma once
#include "GameActor.h"
#include "HealthBar.h"
#include "HungerBar.h"
#include "StaminaBar.h"
#include "Vector2f.h"
#include "Pickup.h"
#include "ItemHUD.h"
#include <vector>

class Player : public GameActor
{
public:

	struct PlayerMovement
	{
		bool up			{ false };
		bool down		{ false };
		bool left		{ false };
		bool right		{ false };

		bool sprinting	{ false };
	};



	Player(Point2f location, std::string filePath, Point2f baseLocation);
	~Player();

	void Update(float elapsedSec) override;
	void Draw() const override;

	void DrawHudElements() const;

	// input
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);

	void TakeDamage(float damagePoints);
	void RestoreHealth(float healingPoints);
	void SetStopHealing(bool stopHealing);

	void PickupItem(Pickup::PickupType type);
	bool ConsumeFood();

	Rectf GetRect() const;

	int GetCurrentWood(bool erase);
	int GetCurrentFood(bool erase);

	void GiveFood(int amount);

	void SetFoodPoints(int foodPoints);

	Point2f GetCenterPoint() const;

	void SetIsDead(bool isDead);
	bool GetIsDead();

	void SetInventoryColor(const Color4f& color);

private:

	void UpdateMovement(float elapsedSec);
	void CheckHunger(float elapsedSec);

	Point2f							m_BaseLocation;

	Vector2f						m_MySpeed;

	PlayerMovement					m_PlayerMovement;

	HealthBar*						m_HealthBarPtr;
	HungerBar*						m_HungerBarPtr;
	StaminaBar*						m_StaminaBarPtr;

	ItemHUD*						m_FoodInventoryPtr;
	ItemHUD*						m_WoodInventoryPtr;

	bool							m_Dead;
	bool							m_StopHealing;
	std::vector<Pickup::PickupType> m_Inventory;
};

