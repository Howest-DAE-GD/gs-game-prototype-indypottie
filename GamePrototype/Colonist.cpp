#include "pch.h"
#include "Colonist.h"

Colonist::Colonist(const Point2f& startingLocation) : m_Location{ startingLocation }, m_CurrentTask{ ColonistTasks::Wandering }, m_IsAtTargetPoint{ false }, m_IsWandering{ true }, m_TargetLocation(startingLocation)
{
	m_ColonistCircle.center  = m_Location;
	m_ColonistCircle.radius = m_DRAW_COLONIST_RADIUS;
}

void Colonist::Update(float elapsedSec)
{
	m_IsAtTargetPoint = PathToTargetPoint(elapsedSec);

	m_ColonistCircle.center = m_Location;
}

void Colonist::Draw() const
{
	utils::SetColor(m_COLONIST_COLOR);
	utils::FillEllipse(m_ColonistCircle.center, m_ColonistCircle.radius, m_ColonistCircle.radius);
}

void Colonist::SetLocation(const Point2f& newLocation)
{
	m_Location = newLocation;
}

void Colonist::SetNewTargetLocation(const Point2f& newTargetLocation)
{
	m_TargetLocation = newTargetLocation;
}

void Colonist::SetIsWandering(bool IsWandering)
{
	m_IsWandering = IsWandering;
}

void Colonist::SetCurrentTask(const ColonistTasks& newTask)
{
	m_CurrentTask = newTask;
}

Colonist::ColonistTasks Colonist::GetCurrentTask()
{
	return m_CurrentTask;
}

bool Colonist::GetIsAtTargetPoint() const
{
	return m_IsAtTargetPoint;
}

bool Colonist::PathToTargetPoint(float elapsedSec)
{
	if (!m_IsWandering)
	{
		if (!utils::IsPointInCircle(m_TargetLocation, m_ColonistCircle))
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
	else
	{
		if (!utils::IsPointInCircle(m_TargetLocation, m_ColonistCircle))
		{
			if (m_Location.x > m_TargetLocation.x)
			{
				m_Location.x -= m_COLONIST_WANDERING_SPEED.x;
			}
			else if (m_Location.x < m_TargetLocation.x)
			{
				m_Location.x += m_COLONIST_WANDERING_SPEED.x;
			}

			if (m_Location.y > m_TargetLocation.y)
			{
				m_Location.y -= m_COLONIST_WANDERING_SPEED.y;
			}
			else if (m_Location.y < m_TargetLocation.y)
			{
				m_Location.y += m_COLONIST_WANDERING_SPEED.y;
			}

			return false;
		}

		return true;
	}
}
