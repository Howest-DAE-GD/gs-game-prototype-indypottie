#include "pch.h"
#include "Player.h"

Player::Player(Point2f location, std::string filePath, Point2f baseLocation)
	: GameActor(location, filePath)
	, m_BaseLocation(baseLocation)
	, m_MySpeed(100.f, 100.f)
	, m_Dead(false)
{
	Point2f healthBarLocation{ 5.f, 470.f };
	m_HealthBarPtr = new HealthBar(healthBarLocation, 100.f);

	Point2f hungerBarLocation{ 5.f, 440.f };
	m_HungerBarPtr = new HungerBar(hungerBarLocation, 100.f, 80.f);
}

Player::~Player()
{
	delete m_HealthBarPtr;
	delete m_HungerBarPtr;
}

void Player::Update(float elapsedSec)
{
	m_HealthBarPtr->GetCurrentHealth() <= 0 ? m_Dead = true : m_Dead = false;

	m_HungerBarPtr->Update(elapsedSec);

	UpdateMovement(elapsedSec);
}

void Player::Draw() const
{
	m_MyTexturePtr->Draw(m_MyLocation);
}

void Player::DrawHudElements() const
{
	m_HealthBarPtr->Draw();
	m_HungerBarPtr->Draw();
}

void Player::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
		// up
	case SDLK_w:
		m_PlayerMovement.up = false;
		break;

		// down
	case SDLK_s:
		m_PlayerMovement.down = false;
		break;

		// left
	case SDLK_a:
		m_PlayerMovement.left = false;
		break;

		// right
	case SDLK_d:
		m_PlayerMovement.right = false;
		break;

	default:
		break;
	}
}

void Player::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch ( e.keysym.sym )
	{
		// up
	case SDLK_w :
		m_PlayerMovement.up   = true;
		break;

		// down
	case SDLK_s:
		m_PlayerMovement.down = true;
		break;

		// left
	case SDLK_a:
		m_PlayerMovement.left = true;
		break;

		// right
	case SDLK_d:
		m_PlayerMovement.right = true;
		break;

	default:
		break;
	}
}

void Player::TakeDamage(float damagePoints)
{
	m_HealthBarPtr->DamageHealth(damagePoints);
}

void Player::RestoreHealth(float healingPoints)
{
	m_HealthBarPtr->RestoreHealth(healingPoints);
}

void Player::UpdateMovement(float elapsedSec)
{
	Vector2f movement(0.0f, 0.0f);

	if (m_PlayerMovement.up)
	{
		movement.y += 1.0f;
	}
	if (m_PlayerMovement.down)
	{
		movement.y -= 1.0f;
	}
	if (m_PlayerMovement.left)
	{
		movement.x -= 1.0f;
	}
	if (m_PlayerMovement.right)
	{
		movement.x += 1.0f;
	}

	// Normalize if moving diagonally
	if (movement.Length() > 1.0f)
	{
		movement = movement.Normalized();
	}

	m_MyLocation.x += movement.x * m_MySpeed.x * elapsedSec;
	m_MyLocation.y += movement.y * m_MySpeed.y * elapsedSec;
}
