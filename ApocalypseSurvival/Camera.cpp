#include "pch.h"
#include "Camera.h"
#include <iostream>

Camera::Camera(float screenWidth, float screenHeight) 
	: m_ScreenWidth { screenWidth }
	, m_ScreenHeight{ screenHeight }
{
}

void Camera::Aim(float levelWidth, float levelHeight, const Point2f& trackPoint) const
{
	Point2f cameraPos{ -(trackPoint.x - m_ScreenWidth / 2.f), -(trackPoint.y - m_ScreenHeight / 2.f) };

	if (cameraPos.x - m_ScreenWidth <= -levelWidth)
	{
		cameraPos.x = -(levelWidth - m_ScreenWidth);
	}
	else
	if (cameraPos.x >= .0f)
	{
		cameraPos.x = .0f;
	}
	if (cameraPos.y - m_ScreenHeight <= -levelHeight)
	{
		cameraPos.y = -(levelHeight - m_ScreenHeight);
	}
	else
	if (cameraPos.y >= .0f)
	{
		cameraPos.y = .0f;
	}

	glPushMatrix();
	glTranslatef(cameraPos.x, cameraPos.y, .0f);
}

void Camera::Reset() const
{
	glPopMatrix();
}
