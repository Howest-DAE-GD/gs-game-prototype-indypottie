#include "pch.h"
#include "GameActor.h"

GameActor::GameActor(Point2f location, std::string filePath)
	: m_MyLocation	(location)
	, m_MyTexturePtr(new Texture{ filePath })

{
	// nothing to do
}

GameActor::GameActor(Point2f location)
	: m_MyLocation	{ location }
	, m_MyTexturePtr{ nullptr }
{
}

GameActor::~GameActor()
{
	if (m_MyTexturePtr != nullptr)
	{
		delete m_MyTexturePtr;
	}
}

Point2f GameActor::GetLocation() const
{
	return m_MyLocation;
}

void GameActor::SetLocation(Point2f location)
{
	m_MyLocation = location;
}
