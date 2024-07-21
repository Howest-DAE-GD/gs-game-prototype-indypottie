#pragma once
#include "GameActor.h"
#include "HealthBar.h"
#include "HungerBar.h"
#include "Vector2f.h"

class Player : public GameActor
{
public:

	struct PlayerMovement
	{
		bool up   { false };
		bool down { false };
		bool left { false };
		bool right{ false };
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

private:

	void UpdateMovement(float elapsedSec);

	Point2f        m_BaseLocation;

	Vector2f       m_MySpeed;

	PlayerMovement m_PlayerMovement;

	HealthBar*	   m_HealthBarPtr;
	HungerBar*	   m_HungerBarPtr;

	bool		   m_Dead;
};

