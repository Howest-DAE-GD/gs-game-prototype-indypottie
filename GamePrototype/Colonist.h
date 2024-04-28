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

	void SetIsWandering(bool IsWandering);

	void SetCurrentTask(const ColonistTasks& newTask);

	// getters
	ColonistTasks GetCurrentTask();

	bool GetIsAtTargetPoint() const;

	// constants 

	const float		m_DRAW_COLONIST_RADIUS		{ 10.f };

	const Vector2f	m_COLONIST_SPEED			{  0.5f, 0.5f };

	const Vector2f  m_COLONIST_WANDERING_SPEED	{  0.2f, 0.2f };

	const Color4f	m_COLONIST_COLOR			{ 0.3f,0.5f,1.f,1.f };

private:
	// private methods
	bool PathToTargetPoint(float elapsedSec);

	bool m_IsAtTargetPoint;
	bool m_IsWandering;

	Circlef m_ColonistCircle;

	Point2f m_Location;
	Point2f m_TargetLocation;

	ColonistTasks m_CurrentTask;
};

