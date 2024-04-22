#pragma once
#include "utils.h"


class Colonist
{
public:
	Colonist(const Point2f& startingLocation);




	enum class ColonistTasks
	{
		WoodCutting,
		Farming,
		Guarding,
		Wandering
	};

	// general methods
	void Update(float elapsedSec);
	void Draw() const;

	// setters
	void SetLocation(const Point2f& newLocation);
	void SetNewTargetLocation(const Point2f& newTargetLocation);

	void SetCurrentTask(const ColonistTasks& newTask);

	// getters
	ColonistTasks GetCurrentTask();

	// constants 

	const float		m_DRAW_COLONIST_RADIUS_X{ 10.f };
	const float		m_DRAW_COLONIST_RADIUS_Y{ 10.f };

	const Vector2f	m_COLONIST_SPEED		{  0.5f, 0.5f };

	const Color4f	m_COLONIST_COLOR		{ 0.3f,0.5f,1.f,1.f };

private:
	// private methods
	bool PathToTargetPoint(float elapsedSec);

	Point2f m_Location;
	Point2f m_TargetLocation;

	ColonistTasks m_CurrentTask;
};

