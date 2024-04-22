#include "pch.h"
#include <iostream>
#include "ColonistTaskManager.h"

ColonistTaskManager::ColonistTaskManager(const std::vector<Colonist*>& colonistVector) : m_TotalAssignedColonists { 0 }
{
	m_ColonistVector = colonistVector;

	m_TotalAmountOfColonists = m_ColonistVector.size();
	DivideTasks();
}

void ColonistTaskManager::DivideTasks()
{
	std::cout << "COLONIST AMOUNT: " << m_TotalAmountOfColonists << std::endl;

	//for (int index{ 0 }; index < m_ColonistVector.size(); ++index)
	//{
	//	if (index < m_TaskDivider.woodCutting)
	//	{
	//		m_ColonistVector.at(index)->SetNewTargetLocation(Point2f(500.f, 50.f));

	//		std::cout << "WOODCUTTER MOVING" << std::endl;
	//	}

	//	if (index < m_TaskDivider.farming)
	//	{
	//		m_ColonistVector.at(index)->SetNewTargetLocation(Point2f(20.f, 270.f));

	//		std::cout << "FARMER MOVING" << std::endl;
	//	}

	//	if (index < m_TaskDivider.guarding)
	//	{
	//		m_ColonistVector.at(index)->SetNewTargetLocation(Point2f(230.f, 490.f));

	//		std::cout << "GUARD MOVING" << std::endl;
	//	}
	//	
	//}

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

		default:
			break;
		}
	}

	std::cout << "WOODCUTTERS: " << m_TaskDivider.woodCutting << std::endl << "FARMERS: " << m_TaskDivider.farming << std::endl << "GUARDS: " << m_TaskDivider.guarding << std::endl << "WANDERERS: " << m_TaskDivider.wandering << std::endl;
	std::cout << "COLONISTS ASSIGNED: " << m_TotalAssignedColonists + 1 << std::endl << std::endl;
}

void ColonistTaskManager::TryToIncreaseWoodcutters()
{
	if (m_TotalAmountOfColonists - m_TotalAssignedColonists != 0)
	{
		m_TaskDivider.woodCutting += 1;
		m_TotalAssignedColonists  += 1;

		m_ColonistVector.at(m_TotalAssignedColonists)->SetCurrentTask(Colonist::ColonistTasks::WoodCutting);
	}

	DivideTasks();
}

void ColonistTaskManager::TryToIncreaseFarmers()
{
	if (m_TotalAmountOfColonists - m_TotalAssignedColonists != 0)
	{
		m_TaskDivider.farming += 1;
		m_TotalAssignedColonists += 1;

		m_ColonistVector.at(m_TotalAssignedColonists)->SetCurrentTask(Colonist::ColonistTasks::Farming);
	}

	DivideTasks();
}

void ColonistTaskManager::TryToIncreaseGuards()
{
	if (m_TotalAmountOfColonists - m_TotalAssignedColonists != 0)
	{
		m_TaskDivider.guarding += 1;
		m_TotalAssignedColonists += 1;
	}

	DivideTasks();
}

void ColonistTaskManager::SetWoodCutters(const int& newAmountOfWoodCutters)
{
	m_TaskDivider.woodCutting = newAmountOfWoodCutters;
}

void ColonistTaskManager::SetFarmers(const int& newAmountOfFarmers)
{
	m_TaskDivider.farming = newAmountOfFarmers;
}

void ColonistTaskManager::SetGuards(const int& newAmountOfGuards)
{
	m_TaskDivider.guarding = newAmountOfGuards;
}
