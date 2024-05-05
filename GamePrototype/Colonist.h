#pragma once
#include "utils.h"
#include "Timer.h"
#include "Colony.h"
#include <vector>
class Colony;

class Colonist
{
public:
	Colonist(const Point2f& startingLocation, Colony* colony);
	~Colonist();

	enum class ColonistTasks
	{
		WoodCutting,
		Farming,
		Guarding,
		Wandering,
		DeliveringResources
	};

	// general methods
	void Update(float elapsedSec);
	void Draw() const;

	// setters
	void SetLocation(const Point2f& newLocation);
	void SetNewTargetLocation(const Point2f& newTargetLocation);

	void SetIsWandering(bool IsWandering);

	void SetCurrentTask(const ColonistTasks& newTask);

	void AddWoodToColonistInventory(const int& amountOfWood);
	void AddFoodToColonistInventory(const int& amountOfFood);

	void SetIsDeliveringResources(bool isDeliveringResources);

	// getters
	ColonistTasks GetCurrentTask();

	bool GetIsAtTargetPoint() const;
	bool GetIsDeliveringResources() const;

	int GetWoodFromColonistInventory();
	int GetFoodFromColonistInventory();

	Point2f GetCurrentTargetPoint() const;

	// constants 

	const float		m_DRAW_COLONIST_RADIUS		{ 10.f };

	const Vector2f	m_COLONIST_SPEED			{  0.5f, 0.5f };

	const Vector2f  m_COLONIST_WANDERING_SPEED	{  0.2f, 0.2f };

private:
	// structs and enums

	struct ColonistInventory
	{
		int wood;
		int food;
	};

	// private methods
	bool PathToTargetPoint(float elapsedSec);

	void HandleCurrentTask(float elapsedSec);
	void DeliverResources();
	void PatrolGuard();


	ColonistInventory m_ColonistInventory;

	bool m_IsAtTargetPoint;
	bool m_IsWandering;
	bool m_DeliveringResources;

	Circlef m_ColonistCircle;

	Point2f m_Location;
	Point2f m_TargetLocation;
	Point2f m_MainBuildingLocation;

	ColonistTasks m_CurrentTask;
	ColonistTasks m_PreviousTask;
	Timer*		  m_ColonistTimer;
	Colony*		  m_Colony;

	float m_AccumulatedSec;

	std::vector<Point2f> m_PatrolPoints;
	int m_CurrentPatrolPointIndex;


	bool m_IsAtTaskLocation{ false };

	Color4f	m_ColonistColor;
};

