#pragma once
#include "Vector2f.h"
#include "utils.h"
#include "GameActor.h"
#include "Player.h"
#include "PlayerBase.h"

class Enemy : public GameActor
{
public:

	Enemy(Point2f location, std::string textureFilePath, float detectionRadius, float attackRange, Player* player, const PlayerBase* playerBase);
	~Enemy();

	void Update(float elapsedSec) override;
	void Draw() const override;


private:

	void Roam(float elapsedSec);
	void DetectPlayer();
	void AttackPlayer(float elapsedSec);
	void AvoidBase();


	float				m_DetectionRadius;
	float				m_AttackRange;
	float				m_Speed;
	float				m_SprintingSpeed;

	Vector2f			m_Velocity;

	Player*				m_PlayerPtr;
	const PlayerBase*	m_PlayerBasePtr;

	bool				m_IsPlayerDetected;
	bool				m_IsAttacking;

	Point2f				m_CenterOfEnemy;

};

