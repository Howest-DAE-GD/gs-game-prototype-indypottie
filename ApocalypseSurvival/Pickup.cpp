#include "pch.h"
#include "Pickup.h"

Pickup::Pickup(Point2f location, PickupType type)
	: GameActor(location, type == PickupType::wood ? "Wood.png" : "Food.png")
	, m_MyType{ type }
{
	// nothing to do
}

Pickup::Pickup(PickupType type, float mapWidth, float mapHeight)
	: GameActor(GenerateRandomLocation(mapWidth, mapHeight), type == PickupType::wood ? "Wood.png" : "Food.png")
	, m_MyType{ type }

{
	// nothing to do
}

void Pickup::Update(float elapsedSec)
{
}

void Pickup::Draw() const
{
	m_MyTexturePtr->Draw(m_MyLocation);
}

Pickup::PickupType Pickup::GetType() const
{
	return m_MyType;
}

Rectf Pickup::GetRect() const
{
	Rectf pickupRect{ m_MyLocation.x, m_MyLocation.y, m_MyTexturePtr->GetWidth(), m_MyTexturePtr->GetHeight() };

	return pickupRect;
}

Point2f Pickup::GenerateRandomLocation(float mapWidth, float mapHeight) const
{
	static std::default_random_engine generator{ std::random_device{}() };

	std::uniform_real_distribution<float> distributionX(0.0f, mapWidth);
	std::uniform_real_distribution<float> distributionY(0.0f, mapHeight);

	return Point2f(distributionX(generator), distributionY(generator));
}
