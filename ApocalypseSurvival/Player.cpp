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
	m_HungerBarPtr = new HungerBar(hungerBarLocation, 100.f, 90.f);

	Point2f staminaBarLocation{ 5.f, 30.f };
	m_StaminaBarPtr = new StaminaBar(staminaBarLocation, 100.f);

	Point2f foodHudLocation{ 5.f, 400.f };
	m_FoodInventoryPtr = new ItemHUD{ foodHudLocation,"FOOD",0 };

	Point2f woodHudLocation{ 5.f, 380.f };
	m_WoodInventoryPtr = new ItemHUD{ woodHudLocation,"WOOD",0 };
}

Player::~Player()
{
	delete m_HealthBarPtr;
	delete m_HungerBarPtr;
	delete m_StaminaBarPtr;
	delete m_FoodInventoryPtr;
	delete m_WoodInventoryPtr;
}

void Player::Update(float elapsedSec)
{
	m_HealthBarPtr->GetCurrentHealth() <= 0 ? m_Dead = true : m_Dead = false;

	m_HungerBarPtr->Update(elapsedSec);

	UpdateMovement(elapsedSec);

	CheckHunger(elapsedSec);

	if (!m_PlayerMovement.sprinting)
	{
		m_StaminaBarPtr->Increase(0.1f);
	}
}

void Player::Draw() const
{
	m_MyTexturePtr->Draw(m_MyLocation);
}

void Player::DrawHudElements() const
{
	m_HealthBarPtr->Draw();
	m_HungerBarPtr->Draw();
	m_StaminaBarPtr->Draw();
	m_FoodInventoryPtr->Draw();
	m_WoodInventoryPtr->Draw();
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

		// sprint
	case SDLK_LSHIFT:
		m_PlayerMovement.sprinting = false;
		m_HungerBarPtr->SetHungerDecreaseRate(0.25f);
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

		// sprint
	case SDLK_LSHIFT:
		m_PlayerMovement.sprinting = true;
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

void Player::SetStopHealing(bool stopHealing)
{
	m_StopHealing = stopHealing;
}

void Player::PickupItem(Pickup::PickupType type)
{
	m_Inventory.push_back(type);

	if (type == Pickup::PickupType::food)
	{
		m_FoodInventoryPtr->IncreaseItem();
	}
	else if (type == Pickup::PickupType::wood)
	{
		m_WoodInventoryPtr->IncreaseItem();
	}
}

bool Player::ConsumeFood()
{
	auto it = std::find(m_Inventory.begin(), m_Inventory.end(), Pickup::PickupType::food);
	if (it != m_Inventory.end())
	{
		m_Inventory.erase(it);
		return true;
	}
	return false;
}

Rectf Player::GetRect() const
{
	Rectf playerRect{ m_MyLocation.x, m_MyLocation.y, m_MyTexturePtr->GetWidth(), m_MyTexturePtr->GetHeight() };

	return playerRect;
}

int Player::GetCurrentWood(bool erase)
{
	int woodCount = 0;

	for (const auto& item : m_Inventory)
	{
		if (item == Pickup::PickupType::wood)
		{
			++woodCount;
			
		}
	}

	if (erase)
	{
		m_Inventory.erase(
			std::remove(m_Inventory.begin(), m_Inventory.end(), Pickup::PickupType::wood),
			m_Inventory.end()
		);

		m_WoodInventoryPtr->RemoveItemAmount(woodCount);
	}

	return woodCount;
}

int Player::GetCurrentFood(bool erase)
{
	int foodCount = 0;

	for (const auto& item : m_Inventory)
	{
		if (item == Pickup::PickupType::food)
		{
			++foodCount;

		}
	}

	if (erase)
	{
		m_Inventory.erase(
			std::remove(m_Inventory.begin(), m_Inventory.end(), Pickup::PickupType::food),
			m_Inventory.end()
		);

		m_FoodInventoryPtr->RemoveItemAmount(foodCount);
	}

	return foodCount;
}

void Player::GiveFood(int amount)
{
	for (int iterator{ 0 }; iterator < amount; ++iterator)
	{
		m_Inventory.push_back(Pickup::PickupType::food);
		m_FoodInventoryPtr->IncreaseItem();
	}
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

	if (!m_PlayerMovement.sprinting and m_StaminaBarPtr->GetCurrentStamina() > 0.f)
	{
		m_MyLocation.x += movement.x * m_MySpeed.x * elapsedSec;
		m_MyLocation.y += movement.y * m_MySpeed.y * elapsedSec;
	}
	else
	{
		m_MyLocation.x += movement.x * (m_MySpeed.x * 2.f) * elapsedSec;
		m_MyLocation.y += movement.y * (m_MySpeed.y * 2.f) * elapsedSec;

		m_StaminaBarPtr->Decrease(0.1f);

		m_HungerBarPtr->SetHungerDecreaseRate(0.5f);

		if (m_StaminaBarPtr->GetCurrentStamina() <= 0)
		{
			m_PlayerMovement.sprinting = false;
		}
	}

}

void Player::CheckHunger(float elapsedSec)
{
	if (m_HungerBarPtr->GetHunger() <= 95.f)
	{
		if (ConsumeFood())
		{
			m_HungerBarPtr->Refill(5.f);
			m_FoodInventoryPtr->DecreaseItem();
		}
	}

	if (m_HungerBarPtr->GetHunger() <= 0.f)
	{
		TakeDamage(0.005f);
	}

	if (m_HungerBarPtr->GetHunger() >= 80.f and !m_StopHealing)
	{
		RestoreHealth(0.05);
	}
}
