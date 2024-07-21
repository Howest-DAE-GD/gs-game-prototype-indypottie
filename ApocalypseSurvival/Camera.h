#pragma once

class Camera final
{
public:
	explicit Camera(float screenWidth, float screenHeight);

	void Aim(float levelWidth, float levelHeight, const Point2f& trackPoint) const;
	void Reset() const;

private:
	float m_ScreenWidth;
	float m_ScreenHeight;
};

