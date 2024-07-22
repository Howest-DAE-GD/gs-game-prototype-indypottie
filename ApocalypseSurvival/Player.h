#pragma once
#include "GameActor.h"
#include "HealthBar.h"
#include "HungerBar.h"
#include "StaminaBar.h"
#include "Vector2f.h"
#include "Pickup.h"
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

	void PickupItem(Pickup::PickupType type);
	bool ConsumeFood();

	Rectf GetRect() const;

private:

	void UpdateMovement(float elapsedSec);
	void CheckHunger(float elapsedSec);

	Point2f							m_BaseLocation;

	Vector2f						m_MySpeed;

	PlayerMovement					m_PlayerMovement;

	HealthBar*						m_HealthBarPtr;
	HungerBar*						m_HungerBarPtr;
	StaminaBar*						m_StaminaBarPtr;

	bool							m_Dead;

	std::vector<Pickup::PickupType> m_Inventory;
};

