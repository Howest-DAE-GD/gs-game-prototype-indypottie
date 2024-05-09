#include "Map.h"

Map::Map(float screenW, float screenH) : m_ScreenWidth{ screenW }, m_ScreenHeight{ screenH }
{
	m_MainBuildingTexturePtr = new Texture("MainBuilding.png");
	m_FarmTexturePtr		 = new Texture("Farm.png");
}

Map::~Map()
{
	delete m_FarmTexturePtr;
	delete m_MainBuildingTexturePtr;
}

void Map::Draw() const
{
	m_MainBuildingTexturePtr->Draw(Point2f(m_ScreenWidth / 2 - (m_MainBuildingTexturePtr->GetWidth() / 2), m_ScreenHeight / 2 - (m_MainBuildingTexturePtr->GetHeight() / 2)));
	
	m_FarmTexturePtr->Draw(Point2f(20.f, 270.f));

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
