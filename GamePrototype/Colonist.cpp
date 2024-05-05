#include "pch.h"
#include "Colonist.h"
#include <iostream>

Colonist::Colonist(const Point2f& startingLocation, Colony* colony) : m_Location{ startingLocation }, m_Colony{ colony }, m_CurrentTask{ ColonistTasks::Wandering }, m_PreviousTask{ ColonistTasks::Wandering }, m_IsAtTargetPoint { false }, m_IsWandering{ true }, m_TargetLocation(startingLocation), m_ColonistInventory{ 0 , 0 }, m_DeliveringResources{ false }, m_CurrentPatrolPointIndex{0}, m_ColonistColor{ 0.95f, 0.76f, 0.49f,1.f }
{
	m_MainBuildingLocation = startingLocation;

	m_ColonistCircle.center  = m_Location;
	m_ColonistCircle.radius = m_DRAW_COLONIST_RADIUS;

	m_ColonistTimer = new Timer(std::bind(&Colonist::DeliverResources, this), 5.f, false);

	m_PatrolPoints.push_back(Point2f(startingLocation.x - 70.f, startingLocation.y + 60.f));
	m_PatrolPoints.push_back(Point2f(startingLocation.x - 70.f, startingLocation.y - 60.f));
	m_PatrolPoints.push_back(Point2f(startingLocation.x + 70.f, startingLocation.y - 60.f));
	m_PatrolPoints.push_back(Point2f(startingLocation.x + 70.f, startingLocation.y + 60.f));
}

Colonist::~Colonist()
{
	delete m_ColonistTimer;
}

void Colonist::Update(float elapsedSec)
{
	m_ColonistTimer->Update(elapsedSec);

	m_IsAtTargetPoint = PathToTargetPoint(elapsedSec);

	m_ColonistCircle.center = m_Location;

	HandleCurrentTask(elapsedSec);
}

void Colonist::Draw() const
{
	utils::SetColor(m_ColonistColor);
	utils::FillEllipse(m_ColonistCircle.center, m_ColonistCircle.radius, m_ColonistCircle.radius);
}

void Colonist::SetLocation(const Point2f& newLocation)
{
	m_Location = newLocation;
}

void Colonist::SetNewTargetLocation(const Point2f& newTargetLocation)
{
	m_TargetLocation = newTargetLocation;
	m_IsAtTargetPoint = false;
}

void Colonist::SetIsWandering(bool IsWandering)
{
	m_IsWandering = IsWandering;
}

void Colonist::SetCurrentTask(const ColonistTasks& newTask)
{
	m_CurrentTask = newTask;
}

void Colonist::AddWoodToColonistInventory(const int& amountOfWood)
{
	m_ColonistInventory.wood += amountOfWood;
}

void Colonist::AddFoodToColonistInventory(const int& amountOfFood)
{
	m_ColonistInventory.food += amountOfFood;
}

void Colonist::SetIsDeliveringResources(bool isDeliveringResources)
{
	m_DeliveringResources = isDeliveringResources;
}


Colonist::ColonistTasks Colonist::GetCurrentTask()
{
	return m_CurrentTask;
}

bool Colonist::GetIsAtTargetPoint() const
{
	return m_IsAtTargetPoint;
}

bool Colonist::GetIsDeliveringResources() const
{
	return m_DeliveringResources;
}

int Colonist::GetWoodFromColonistInventory()
{
	return m_ColonistInventory.wood;
}

int Colonist::GetFoodFromColonistInventory()
{
	return m_ColonistInventory.food;
}

Point2f Colonist::GetCurrentTargetPoint() const
{
	return m_TargetLocation;
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

void Colonist::HandleCurrentTask(float elapsedSec)
{
	m_AccumulatedSec += elapsedSec;

	switch (m_CurrentTask)
	{
	case Colonist::ColonistTasks::WoodCutting:
		m_ColonistColor = Color4f(0.74f, 0.28f, 0.29f, 1.f);

		if (!m_IsAtTaskLocation)
		{
			if (GetCurrentTargetPoint() != Point2f(500.f, 50.f))
			{
				SetNewTargetLocation(Point2f(500.f, 50.f));
			}
		}

		if (GetIsAtTargetPoint())
		{
			if (!m_ColonistTimer->IsRunning())
			{
				m_IsAtTaskLocation = true;
				m_ColonistTimer->Start();
				m_ColonistInventory.wood += 1;
				m_PreviousTask = ColonistTasks::WoodCutting;
			}
		}
		
		break;

	case Colonist::ColonistTasks::Farming:
		m_ColonistColor = Color4f(0.96f, 0.64f, 0.35f, 1.f);

		if (!m_IsAtTaskLocation)
		{
			if (GetCurrentTargetPoint() != Point2f(20.f, 270.f))
			{
				SetNewTargetLocation(Point2f(20.f, 270.f));
			}
		}

		if (GetIsAtTargetPoint())
		{
			if (!m_ColonistTimer->IsRunning())
			{
				m_IsAtTaskLocation = true;
				m_ColonistTimer->Start();
				m_ColonistInventory.food += 1;
				m_PreviousTask = ColonistTasks::Farming;
			}
		}

		break;

	case Colonist::ColonistTasks::Guarding:
		m_ColonistColor = Color4f(0.12f, 0.14f, 0.13f, 1.f);

		m_ColonistTimer->SetNewClassFunction(std::bind(&Colonist::PatrolGuard, this));
		m_ColonistTimer->SetDelay(1.f);

		if (!m_IsAtTaskLocation)
		{
			if (GetCurrentTargetPoint() != m_PatrolPoints.at(m_CurrentPatrolPointIndex))
			{
				SetNewTargetLocation(m_PatrolPoints.at(m_CurrentPatrolPointIndex));
			}
		}

		if (GetIsAtTargetPoint())
		{
			if (!m_ColonistTimer->IsRunning())
			{
				m_IsAtTaskLocation = true;
				m_ColonistTimer->Start();
				m_PreviousTask = ColonistTasks::Guarding;
			}
		}

		break;

	case Colonist::ColonistTasks::Wandering:
		m_ColonistColor = Color4f(0.95f, 0.76f, 0.49f, 1.f);
		break;

	case Colonist::ColonistTasks::DeliveringResources:
		if (GetCurrentTargetPoint() != m_MainBuildingLocation)
		{
			SetNewTargetLocation(m_MainBuildingLocation);
		}

		if (GetIsAtTargetPoint())
		{
			m_Colony->AddResourcesToColonyInventory(m_ColonistInventory.wood, m_ColonistInventory.food);
			m_ColonistInventory.wood = 0;
			m_ColonistInventory.food = 0;
			m_IsAtTaskLocation = false;
			SetCurrentTask(m_PreviousTask);
		}
		break;

	default:
		break;
	}
}

void Colonist::DeliverResources()
{
	SetCurrentTask(ColonistTasks::DeliveringResources);
}

void Colonist::PatrolGuard()
{
	if (m_CurrentPatrolPointIndex != 3)
	{
		m_CurrentPatrolPointIndex += 1;
	}
	else
	{
		m_CurrentPatrolPointIndex = 0;
	}

	m_IsAtTaskLocation = false;

}
