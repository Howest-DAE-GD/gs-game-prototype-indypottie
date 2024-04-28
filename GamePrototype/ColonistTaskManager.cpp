#include "pch.h"
#include <iostream>
#include "ColonistTaskManager.h"

ColonistTaskManager::ColonistTaskManager(const std::vector<Colonist*>& colonistVector, float screenW, float screenH) : m_TotalAssignedColonists { 0 }, m_ScreenW { screenW }, m_ScreenH{ screenH }
{
	m_RandomNewLocationX = float(rand() % int(m_ScreenW));
	m_RandomNewLocationY = float(rand() % int(m_ScreenH));

	m_ColonistVector = colonistVector;

	m_TotalAmountOfColonists = m_ColonistVector.size();

	for (Colonist* colonist : m_ColonistVector)
	{
		colonist->SetCurrentTask(Colonist::ColonistTasks::Wandering);
		m_TaskDivider.wandering += 1;
	}

	DivideTasks();
}

void ColonistTaskManager::DivideTasks()
{
	std::cout << "COLONIST AMOUNT: " << m_TotalAmountOfColonists << std::endl;

	for (Colonist* colonist : m_ColonistVector)
	{
		
		switch (colonist->GetCurrentTask())
		{

		case Colonist::ColonistTasks::WoodCutting:

			colonist->SetNewTargetLocation(Point2f(500.f, 50.f));
			break;

		case Colonist::ColonistTasks::Farming:

			colonist->SetNewTargetLocation(Point2f(20.f, 270.f));
			break;

		case Colonist::ColonistTasks::Guarding:

			colonist->SetNewTargetLocation(Point2f(20.f, 270.f));
			break;

		case Colonist::ColonistTasks::Wandering:

			break;

		default:
			break;
		}
	}

	std::cout << "WOODCUTTERS: " << m_TaskDivider.woodCutting << std::endl << "FARMERS: " << m_TaskDivider.farming << std::endl << "GUARDS: " << m_TaskDivider.guarding << std::endl << "WANDERERS: " << m_TaskDivider.wandering << std::endl;
	std::cout << "COLONISTS ASSIGNED: " << m_TotalAssignedColonists << std::endl << std::endl;
}

void ColonistTaskManager::UpdateTasks()
{
	for (Colonist* colonist : m_ColonistVector)
	{

		switch (colonist->GetCurrentTask())
		{

		case Colonist::ColonistTasks::WoodCutting:

			;
			break;

		case Colonist::ColonistTasks::Farming:

			
			break;

		case Colonist::ColonistTasks::Guarding:

			
			break;

		case Colonist::ColonistTasks::Wandering:

			colonist->SetIsWandering(true);

			if (colonist->GetIsAtTargetPoint())
			{
				m_RandomNewLocationX = rand() % int(m_ScreenW);
				m_RandomNewLocationY = rand() % int(m_ScreenH);


				colonist->SetNewTargetLocation(Point2f(m_RandomNewLocationX, m_RandomNewLocationY));
			}

			break;

		default:
			break;
		}
	}
}

int ColonistTaskManager::GetAmountOfWoodCutters() const
{
	return m_TaskDivider.woodCutting;
}

int ColonistTaskManager::GetAmountOfFarmers() const
{
	return m_TaskDivider.farming;
}

int ColonistTaskManager::GetAmountOfGuards() const
{
	return m_TaskDivider.guarding;
}

int ColonistTaskManager::GetAmountOfWanderers() const
{
	return m_TaskDivider.wandering;
}

void ColonistTaskManager::TryToIncreaseWoodcutters()
{
	if (m_TaskDivider.wandering != 0)
	{
		m_ColonistVector.at(m_TotalAssignedColonists)->SetCurrentTask(Colonist::ColonistTasks::WoodCutting);
		m_ColonistVector.at(m_TotalAssignedColonists)->SetIsWandering(false);

		m_TaskDivider.woodCutting += 1;
		m_TaskDivider.wandering   -= 1;
		m_TotalAssignedColonists  += 1;
	}

	DivideTasks();
}

void ColonistTaskManager::TryToIncreaseFarmers()
{
	if (m_TaskDivider.wandering != 0)
	{
		m_ColonistVector.at(m_TotalAssignedColonists)->SetCurrentTask(Colonist::ColonistTasks::Farming);
		m_ColonistVector.at(m_TotalAssignedColonists)->SetIsWandering(false);

		m_TaskDivider.farming    += 1;
		m_TaskDivider.wandering	 -= 1;
		m_TotalAssignedColonists += 1;
	}

	DivideTasks();
}

void ColonistTaskManager::TryToIncreaseGuards()
{
	if (m_TaskDivider.wandering != 0)
	{
		m_ColonistVector.at(m_TotalAssignedColonists)->SetCurrentTask(Colonist::ColonistTasks::Guarding);
		m_ColonistVector.at(m_TotalAssignedColonists)->SetIsWandering(false);

		m_TaskDivider.guarding   += 1;
		m_TaskDivider.wandering  -= 1;
		m_TotalAssignedColonists += 1;
	}

	DivideTasks();
}

void ColonistTaskManager::TryToDecreaseWoodcutters()
{
	if (m_TaskDivider.woodCutting != 0)
	{
		for (Colonist* colonist : m_ColonistVector)
		{
			if (colonist->GetCurrentTask() == Colonist::ColonistTasks::WoodCutting)
			{
				colonist->SetCurrentTask(Colonist::ColonistTasks::Wandering);

				m_TaskDivider.woodCutting -= 1;
				m_TaskDivider.wandering	  += 1;
				m_TotalAssignedColonists  -= 1;

				DivideTasks();

				return;
			}
			
		}
	}

	return;
}

void ColonistTaskManager::TryToDecreaseFarmers()
{
	if (m_TaskDivider.farming != 0)
	{
		for (Colonist* colonist : m_ColonistVector)
		{
			if (colonist->GetCurrentTask() == Colonist::ColonistTasks::Farming)
			{
				colonist->SetCurrentTask(Colonist::ColonistTasks::Wandering);

				m_TaskDivider.farming -= 1;
				m_TaskDivider.wandering += 1;
				m_TotalAssignedColonists -= 1;

				DivideTasks();

				return;
			}

		}
	}

	return;
}

void ColonistTaskManager::TryToDecreaseGuards()
{
	if (m_TaskDivider.guarding != 0)
	{
		for (Colonist* colonist : m_ColonistVector)
		{
			if (colonist->GetCurrentTask() == Colonist::ColonistTasks::Guarding)
			{
				colonist->SetCurrentTask(Colonist::ColonistTasks::Wandering);

				m_TaskDivider.guarding -= 1;
				m_TaskDivider.wandering += 1;
				m_TotalAssignedColonists -= 1;

				DivideTasks();

				return;
			}

		}
	}

	return;
}
