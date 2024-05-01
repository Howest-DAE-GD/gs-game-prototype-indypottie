#pragma once
#include "Colonist.h"
#include <vector>


class ColonistTaskManager
{
public:

	ColonistTaskManager(const std::vector<Colonist*>& colonistVector, float screenW, float screenH);

	// general methods
	void DivideTasks();
	void UpdateTasks(float elapsedSec);

	// getters
	int GetAmountOfWoodCutters() const;
	int GetAmountOfFarmers() const;
	int GetAmountOfGuards() const;
	int GetAmountOfWanderers() const;

	// setters
	void TryToIncreaseWoodcutters();
	void TryToIncreaseFarmers();
	void TryToIncreaseGuards();

	void TryToDecreaseWoodcutters();
	void TryToDecreaseFarmers();
	void TryToDecreaseGuards();

	int AddWoodToInventory();

private:

	struct TaskDivider
	{
		int woodCutting	{};
		int farming		{};
		int guarding	{};
		int wandering	{};
	};

	int m_AccumulatedWood;


	float m_AccumulatedSeconds;

	float m_ScreenW;
	float m_ScreenH;

	float m_RandomNewLocationX;
	float m_RandomNewLocationY;
	

	TaskDivider m_TaskDivider;

	int m_TotalAmountOfColonists;
	int m_TotalAssignedColonists;

	std::vector<Colonist*> m_ColonistVector;
};

