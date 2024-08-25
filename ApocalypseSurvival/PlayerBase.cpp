#include "pch.h"
#include "PlayerBase.h"

PlayerBase::PlayerBase(Point2f location, std::string filePath)
	: GameActor(location, filePath)
	, m_PlayerAtBed			{ false }
	, m_PlayerAtFireplace	{ false }
	, m_PlayerAtDoor		{ false }
	, m_fireIsOn			{ true }
	, m_PlayerInBase		{ true  }
	, m_FuelLeft			{ 2     }
	, m_CurrentFuelPoints	{ 100   }
	, m_ElapsedTime			{ 0.f	}
	, m_BaseFireOnTexture{ new Texture("Base_big_FireOn.png") }
	, m_StoredFood{ 0 }
{

	Point2f fuelleftHudLocation{ 640.f, 400.f };
	m_CurrentFuelHUD = new ItemHUD{ fuelleftHudLocation,"FUEL IN BASE", m_FuelLeft };

	Point2f foodStoredLocation{ 640.f, 350.f };
	m_FoodStoredHUD = new ItemHUD{ foodStoredLocation,"FOOD STORED", m_StoredFood };

	m_MyLocation.x = (m_MyLocation.x - m_MyTexturePtr->GetWidth() / 2.f);
	m_MyLocation.y = (m_MyLocation.y - m_MyTexturePtr->GetHeight() / 2.f);

	InitializePoints();
}

PlayerBase::~PlayerBase()
{
	delete m_CurrentFuelHUD;
	delete m_BaseFireOnTexture;
	delete m_FoodStoredHUD;
}

void PlayerBase::Update(float elapsedSec)
{
	m_ElapsedTime += elapsedSec;

	if (m_ElapsedTime >= M_FUEL_DECREASE_RATE)
	{
		if (m_CurrentFuelPoints == 0)
		{
			m_CurrentFuelPoints = 0;
		}
		else
		{
			--m_CurrentFuelPoints;
		}

		m_ElapsedTime = 0.f;

		std::cout << m_CurrentFuelPoints << std::endl;
	}

	if (m_CurrentFuelPoints <= 0)
	{
		BurnFire(elapsedSec);
		std::cout << m_fireIsOn << std::endl;
	}
}

void PlayerBase::Draw() const
{
	if (m_fireIsOn)
	{
		m_BaseFireOnTexture->Draw(m_MyLocation);
	}
	else
	{
		m_MyTexturePtr->Draw(m_MyLocation);
	}
}

void PlayerBase::DrawHudElements() const
{
	if (!m_PlayerInBase) return;
	m_CurrentFuelHUD->Draw();
	m_FoodStoredHUD->Draw();
}

void PlayerBase::CheckPlayerInteraction(const Point2f& playerLocation)
{
	if (!utils::IsPointInRect(playerLocation, m_OuterRect))
	{
		m_PlayerInBase = false;
		return;
	}
	else
	{
		m_PlayerInBase = true;
	}

	m_PlayerAtBed		= false;
	m_PlayerAtDoor		= false;
	m_PlayerAtFireplace = false;

	for (const auto& interactionPoint : m_InteractionPointsUM)
	{
		if (utils::IsPointInRect(playerLocation, interactionPoint.second))
		{
			// Perform actions based on the interaction point
			if (interactionPoint.first == "bed")
			{
				// Action for bed
				m_PlayerAtBed = true;
			}
			else if (interactionPoint.first == "fireplace")
			{
				// Action for fireplace
				m_PlayerAtFireplace = true;
			}
			else if (interactionPoint.first == "door")
			{
				m_PlayerAtDoor = true;
			}
		}
	}
}

void PlayerBase::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{

	case SDLK_e:

		if (m_PlayerAtBed)
		{
			std::cout << "bed" << std::endl;
		}
		else if (m_PlayerAtDoor)
		{
			std::cout << "door" << std::endl;
		}
		else if (m_PlayerAtFireplace)
		{
			std::cout << "fireplace" << std::endl;
		}

		break;

	default:
		break;
	}
}

void PlayerBase::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{

}

void PlayerBase::DepositFuel(int amount)
{
	m_FuelLeft += amount;

	m_CurrentFuelHUD->AddItemAmount(amount);

	std::cout << m_FuelLeft << std::endl;
}

void PlayerBase::StoreFood(int amount)
{
	m_StoredFood += amount;
	m_FoodStoredHUD->AddItemAmount(amount);
	std::cout << m_StoredFood << std::endl;
}

int PlayerBase::GetCurrentStoredFood()
{
	return m_StoredFood;
}

bool PlayerBase::GetFirePlaceInteractionPoint() const
{
	return m_PlayerAtFireplace;
}

bool PlayerBase::GetDoorInteractionPoint() const
{
	return m_PlayerAtDoor;
}

bool PlayerBase::GetBedInteractionPoint() const
{
	return m_PlayerAtBed;
}

bool PlayerBase::GetIsPlayerInBase() const
{
	return m_PlayerInBase;
}

bool PlayerBase::GetIsFireOn() const
{
	return m_fireIsOn;
}

void PlayerBase::RemoveFood(int amount)
{
	if (m_StoredFood <= 0) return;

	m_StoredFood -= amount;
	m_FoodStoredHUD->RemoveItemAmount(amount);
}

void PlayerBase::RemoveWood(int amount)
{
	if (m_FuelLeft <= 0) return;

	m_FuelLeft -= amount;
	m_CurrentFuelHUD->RemoveItemAmount(amount);
}

Point2f PlayerBase::GetCenterPoint() const
{
	return Point2f{ m_MyLocation.x + (m_MyTexturePtr->GetWidth() / 2.f), m_MyLocation.y + (m_MyTexturePtr->GetHeight() / 2.f) };
}

void PlayerBase::SetInventoryColor(Color4f color)
{
	m_CurrentFuelHUD->SetTextColor(color);
	m_FoodStoredHUD->SetTextColor(color);
}

void PlayerBase::InitializePoints()
{
	m_OuterRect.bottom	= m_MyLocation.y;
	m_OuterRect.left	= m_MyLocation.x;
	m_OuterRect.width	= m_MyTexturePtr->GetWidth();
	m_OuterRect.height	= m_MyTexturePtr->GetHeight();


	const Rectf bedRect			{ m_MyLocation.x + 266.f, m_MyLocation.y + 66.f, 103.f, 23.f };

	const Rectf fireplaceRect	{ m_MyLocation.x + 160.f, m_MyLocation.y + 198.f, 81.f, 23.f };

	const Rectf doorRect		{ m_MyLocation.x + 60.f, m_MyLocation.y + 32.f, 43.f, 33.f };


	m_InteractionPointsUM.insert({ "bed", bedRect });

	m_InteractionPointsUM.insert({ "fireplace", fireplaceRect });

	m_InteractionPointsUM.insert({ "door", doorRect });
}

void PlayerBase::BurnFire(float elapsedSec)
{

	if (m_FuelLeft <= 0)
	{
		m_fireIsOn = false;
		return;
	}

	--m_FuelLeft;

	m_CurrentFuelHUD->DecreaseItem();

	m_CurrentFuelPoints = M_MAX_FUEL_POINTS;

	m_fireIsOn = true;
}
