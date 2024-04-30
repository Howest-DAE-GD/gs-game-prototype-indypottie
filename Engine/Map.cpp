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
	for (Rectf building : m_Buildings)
	{
		utils::FillRect(building);
	}
}
