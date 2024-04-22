#pragma once
#include "Colonist.h"
#include <vector>


class ColonistTaskManager
{
public:

	ColonistTaskManager(const std::vector<Colonist*>& colonistVector);

	// general methods
	void DivideTasks();
	
	// getters

	// setters
	void TryToIncreaseWoodcutters();
	void TryToIncreaseFarmers();
	void TryToIncreaseGuards();

	/*void SetTasks(const int& woodCutters, const int& farmers, const int& guards, const int& wanderers);*/

private:
	void SetWoodCutters(const int& newAmountOfWoodCutters);
	void SetFarmers(const int& newAmountOfFarmers);
	void SetGuards(const int& newAmountOfGuards);

	struct TaskDivider
	{
		int woodCutting	{};
		int farming		{};
		int guarding	{};
		int wandering	{};
	};

	

	TaskDivider m_TaskDivider;

	int m_TotalAmountOfColonists;
	int m_TotalAssignedColonists;

	std::vector<Colonist*> m_ColonistVector;
};

