#pragma once
#include "GameActor.h"
#include "utils.h"

class Map : public GameActor
{
public:

	Map(Point2f location, std::string filePath, float width, float height);


	void Update(float elapsedSec) override;
	void Draw() const override;

	float GetWidth()  const;
	float GetHeight() const;

	Point2f GetCenterPoint() const;

	bool IsWithinBounds(Point2f point) const;

private:
	float	m_Width;
	float	m_Height;

	Point2f m_CenterPoint;
};

