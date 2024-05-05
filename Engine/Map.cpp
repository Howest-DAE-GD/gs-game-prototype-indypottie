#include "Map.h"

Map::Map(float screenW, float screenH)
{
	Rectf mainBuilding{};

	mainBuilding.width  = 100.f;
	mainBuilding.height = 80.f;

	mainBuilding.left   = (screenW / 2) - mainBuilding.width / 2;
	mainBuilding.bottom = (screenH / 2) - mainBuilding.height / 2;

	m_Buildings.push_back(mainBuilding);
}

void Map::Draw() const
{
	utils::SetColor(Color4f(0.50f, 0.31f, 0.14f, 1.f));
	for (Rectf building : m_Buildings)
	{
		utils::FillRect(building);
	}


	DrawTree(Point2f(500.f, 50.f));
}

void Map::DrawTree(const Point2f& location) const
{
	for (int index{ 0 }; index < 5; ++index)
	{
		utils::SetColor(Color4f(0.42f, 0.35f, 0.30f, 1.f));
		utils::FillRect(Rectf(location.x + (index * 100), location.y, 25.f, 100.f));

		utils::SetColor(Color4f(0.23f, 0.35f, 0.25f, 1.f));
		utils::FillEllipse(Ellipsef(Point2f((location.x + (index * 100)) + (25.f / 2), location.y + 100.f), 50.f, 50.f));
	}

}
