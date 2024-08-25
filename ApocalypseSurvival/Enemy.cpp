#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(Point2f location, std::string textureFilePath, float detectionRadius, float attackRange, Player* player, const PlayerBase* playerBase)
    : GameActor{ location,textureFilePath }
    , m_DetectionRadius(detectionRadius)
    , m_AttackRange(attackRange)
    , m_Speed(50.0f)
    , m_SprintingSpeed(170.f)
    , m_PlayerPtr(player)
    , m_PlayerBasePtr(playerBase)
    , m_IsPlayerDetected(false)
    , m_IsAttacking(false)
    , m_CenterOfEnemy(m_MyLocation.x + (m_MyTexturePtr->GetWidth() / 2.f), m_MyLocation.y + (m_MyTexturePtr->GetHeight() / 2.f))
{
    // nothing to do
}

Enemy::~Enemy()
{

}

void Enemy::Update(float elapsedSec)
{
    if (!m_IsPlayerDetected)
    {
        AvoidBase();
        Roam(elapsedSec);
        DetectPlayer();
    }
    else if (m_IsAttacking)
    {
        AvoidBase();
        AttackPlayer(elapsedSec);
        DetectPlayer();
    }
}

void Enemy::Draw() const
{
    m_MyTexturePtr->Draw(m_MyLocation);

    //utils::SetColor(Color4f(0.0f, 1.0f, 0.0f, 1.0f));
    //utils::DrawEllipse(m_CenterOfEnemy, m_DetectionRadius, m_DetectionRadius);
    //utils::DrawEllipse(m_CenterOfEnemy, m_AttackRange, m_AttackRange);
}

void Enemy::Roam(float elapsedSec)
{
    float roamTime{ 2.f };
    float waitTime{ 4.f };

    static float timeAccumulator{ 0.f };
    static bool  wait{ false };

    timeAccumulator += elapsedSec;

    if (timeAccumulator >= waitTime and !wait)
    {
        timeAccumulator = 0.0f;
        float angle = rand() % 360;
        m_Velocity.x = cosf(angle) * m_Speed;
        m_Velocity.y = sinf(angle) * m_Speed;

        wait = true;
    }
    else if (timeAccumulator >= roamTime and wait)
    {
        timeAccumulator = 0.0f;
        m_Velocity.x = 0.f;
        m_Velocity.y = 0.f;

        wait = false;
    }

    m_MyLocation.x += m_Velocity.x * elapsedSec;
    m_MyLocation.y += m_Velocity.y * elapsedSec;

    m_CenterOfEnemy.x += m_Velocity.x * elapsedSec;
    m_CenterOfEnemy.y += m_Velocity.y * elapsedSec;
}

void Enemy::DetectPlayer()
{
    float distanceToPlayer{ utils::GetDistance(m_CenterOfEnemy, m_PlayerPtr->GetCenterPoint()) };

    if (distanceToPlayer <= m_DetectionRadius)
    {
        m_IsPlayerDetected = true;
        m_IsAttacking = true;
    }
    else
    {
        m_IsPlayerDetected = false;
        m_IsAttacking = false;
    }
}

void Enemy::AttackPlayer(float elapsedSec)
{

    Vector2f direction{ m_PlayerPtr->GetCenterPoint() - m_CenterOfEnemy };
    direction = direction.Normalized();

    if (utils::GetDistance(m_CenterOfEnemy, m_PlayerPtr->GetCenterPoint()) <= m_AttackRange)
    {
        m_PlayerPtr->TakeDamage(30.f * elapsedSec);
        m_SprintingSpeed = 0.f;
    }
    else
    {
        m_SprintingSpeed = 170.f;
    }


    m_MyLocation.x += direction.x * m_SprintingSpeed * elapsedSec;
    m_MyLocation.y += direction.y * m_SprintingSpeed * elapsedSec;

    m_CenterOfEnemy.x += direction.x * m_SprintingSpeed * elapsedSec;
    m_CenterOfEnemy.y += direction.y * m_SprintingSpeed * elapsedSec;

}

void Enemy::AvoidBase()
{
    float distanceToBase{ utils::GetDistance(m_CenterOfEnemy, m_PlayerBasePtr->GetCenterPoint()) };

    if (distanceToBase <= 500.f)
    {
        Vector2f direction = m_MyLocation - m_PlayerBasePtr->GetCenterPoint();
        direction = direction.Normalized();

        m_MyLocation.x += direction.x * m_Speed * 0.5f;
        m_MyLocation.y += direction.y * m_Speed * 0.5f;

        m_CenterOfEnemy.x += direction.x * m_Speed * 0.5f;
        m_CenterOfEnemy.y += direction.y * m_Speed * 0.5f;

        m_IsAttacking = false;
        m_IsPlayerDetected = false;
    }
}
