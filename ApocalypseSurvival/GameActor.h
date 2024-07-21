#pragma once
#include "Texture.h"

class GameActor
{
public:

	         GameActor(Point2f location, std::string filePath);
			 GameActor(Point2f location);
	virtual ~GameActor();

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;

	Point2f GetLocation() const;
	void    SetLocation(Point2f location);

protected:

	Point2f  m_MyLocation;
	
	Texture* m_MyTexturePtr;
};