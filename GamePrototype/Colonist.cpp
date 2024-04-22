#include "pch.h"
#include "Colonist.h"

Colonist::Colonist(const Point2f& startingLocation) : m_Location{ startingLocation }, m_TargetLocation{ 350.f, 300.f }, m_CurrentTask { ColonistTasks::Wandering }
{
	// nothing to do 
}

void Colonist::Update(float elapsedSec)
{
	PathToTargetPoint(elapsedSec);
}

void Colonist::Draw() const
{
	utils::SetColor(m_COLONIST_COLOR);
	utils::DrawEllipse(m_Location, m_DRAW_COLONIST_RADIUS_X, m_DRAW_COLONIST_RADIUS_Y);
}

void Colonist::SetLocation(const Point2f& newLocation)
{
	m_Location = newLocation;
}

void Colonist::SetNewTargetLocation(const Point2f& newTargetLocation)
{
	m_TargetLocation = newTargetLocation;
}

void Colonist::SetCurrentTask(const ColonistTasks& newTask)
{
	m_CurrentTask = newTask;
}

Colonist::ColonistTasks Colonist::GetCurrentTask()
{
	return m_CurrentTask;
}

bool Colonist::PathToTargetPoint(float elapsedSec)
{
	if (m_Location.x != m_TargetLocation.x or m_Location.y != m_TargetLocation.y)
	{
		if (m_Location.x > m_TargetLocation.x)
		{
			m_Location.x -= m_COLONIST_SPEED.x;
		}
		else if (m_Location.x < m_TargetLocation.x)
		{
			m_Location.x += m_COLONIST_SPEED.x;
		}

		if (m_Location.y > m_TargetLocation.y)
		{
			m_Location.y -= m_COLONIST_SPEED.y;
		}
		else if (m_Location.y < m_TargetLocation.y)
		{
			m_Location.y += m_COLONIST_SPEED.y;
		}
		
		return false;
	}

	return true;
}
