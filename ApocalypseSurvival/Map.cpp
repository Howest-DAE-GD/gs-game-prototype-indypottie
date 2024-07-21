#include "pch.h"
#include "Map.h"

Map::Map(Point2f location, std::string filePath, float width, float height)
	: GameActor(location, filePath)
	, m_Width		{ width  }
	, m_Height		{ height }
	, m_CenterPoint	{ m_Width / 2.f, m_Height / 2.f }
{
	// nothing to do
}

void Map::Update(float elapsedSec)
{
	
}

void Map::Draw() const
{
	m_MyTexturePtr->Draw(m_MyLocation);
}

float Map::GetWidth() const
{
	return m_Width;
}

float Map::GetHeight() const
{
	return m_Height;
}

Point2f Map::GetCenterPoint() const
{
	return m_CenterPoint;
}

bool Map::IsWithinBounds(Point2f point) const
{
	Rectf mapRect{ m_MyLocation.x, m_MyLocation.y, m_Width, m_Height };

	return (utils::IsPointInRect(point, mapRect));
}
