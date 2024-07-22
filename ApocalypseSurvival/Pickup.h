#pragma once
#include "GameActor.h"
#include <random>

class Pickup : public GameActor
{
public:

	enum class PickupType
	{
		wood,
		food
	};

	Pickup(Point2f location, PickupType type); // for static spawn
	Pickup(PickupType type, float mapWidth, float mapHeight); // for random spawn

	void Update(float elapsedSec) override;
	void Draw() const override;

	PickupType GetType() const;

	Rectf GetRect() const;


private:

	Point2f GenerateRandomLocation(float mapWidth, float mapHeight) const;

	PickupType m_MyType;



};

