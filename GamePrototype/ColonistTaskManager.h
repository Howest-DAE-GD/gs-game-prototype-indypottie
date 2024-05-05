#pragma once
#include "Colonist.h"
#include "utils.h"
#include <vector>

class Colonist;

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

	int AddWoodToInventory();

	// setters
	void TryToIncreaseWoodcutters();
	void TryToIncreaseFarmers();
	void TryToIncreaseGuards();

	void TryToDecreaseWoodcutters();
	void TryToDecreaseFarmers();
	void TryToDecreaseGuards();

	// constants



private:

	struct TaskDivider
	{
		int woodCutting			{};
		int farming				{};
		int guarding			{};
		int wandering			{};
		int deliveringResources	{};
	};

	int m_AccumulatedWood;
	int m_WoodToDeliver;


	float m_AccumulatedSeconds;

	float m_ScreenW;
	float m_ScreenH;

	float m_RandomNewLocationX;
	float m_RandomNewLocationY;
	

	TaskDivider m_TaskDivider;

	int m_TotalAmountOfColonists;
	int m_TotalAssignedColonists;

	std::vector<Colonist*> m_ColonistVector;

	Point2f m_MainBuildingLocation;
};

