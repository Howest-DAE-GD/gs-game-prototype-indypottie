#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_Paused = true;
	m_PlayerWon = false;

	m_HandledDayTime = false;
	m_HandledNightTime = false;
	m_HandledEvening = false;

	m_IntroPopup = new PopUpText{ Point2f(100.f,100.f), "Welcome to Apocalypse Survival !^ Survive for 7 days by collecting food and wood, while avoiding enemies. Manage your resources wisely and ensure you are back in your base by 20:00. Click to start the game. For an overview of the controls, press 'i'.",GetViewPort().width , GetViewPort().height };
	m_IntroPopup->SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
	m_IntroPopup->WrapText(600.f, Point2f(100.f, 100.f));
	m_IntroPopup->SetDisplay(true);

	m_ControlsPopup = new PopUpText{ Point2f(100.f,100.f),
	"Press i again to go back or click to start the game^ WASD -> move around.^ LSHIFT -> sprint.^ E -> interact/drop off.^ F -> get food from door.",
	GetViewPort().width, GetViewPort().height
	};
	m_ControlsPopup->SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
	m_ControlsPopup->WrapText(400.f, Point2f(100.f, 100.f));
	m_DisplayControls = false;
	m_ControlsPopup->SetDisplay(true);

	m_PlayerDeadPopup = new PopUpText(Point2f(100.f, 100.f), "YOU DIED, CLICK TO RESTART", GetViewPort().width, GetViewPort().height);
	m_PlayerDeadPopup->SetDisplay(true);
	m_PlayerDeadPopup->SetColor(Color4f(1.f, 1.f, 1.f, 1.f));

	m_PlayerWonPopup = new PopUpText(Point2f(100.f, 100.f), "YOU WON, CLICK TO PLAY AGAIN", GetViewPort().width, GetViewPort().height);
	m_PlayerWonPopup->SetDisplay(true);
	m_PlayerWonPopup->SetColor(Color4f(1.f, 1.f, 1.f, 1.f));

	m_MapPtr = new Map{ Point2f(0.f,0.f),"map.png",4000.f,4000.f };

	m_PlayerPtr = new Player{ m_MapPtr->GetCenterPoint(),"Player.png",Point2f{100.f,100.f} };

	m_CameraPtr = new Camera{ GetViewPort().width, GetViewPort().height };

	m_DayNightCyclePtr = new DayNightCycle(Point2f(GetViewPort().width, GetViewPort().height), GetViewPort().width, GetViewPort().height);

	m_PlayerBasePtr = new PlayerBase(m_MapPtr->GetCenterPoint(), "Base_big.png");

	SpawnEnemies();

	SpawnPickups();

	m_CurrentDayPopUp = new PopUpText{ Point2f(GetViewPort().width / 2.f, GetViewPort().height / 2.f), "DAY: 1" ,GetViewPort().width , GetViewPort().height };
	m_CurrentDayPopUp->SetDisplay(true);


	//debug
	m_DayNightCyclePtr->SetDay(1);
	std::string currentDayString{ "Day: " + std::to_string(m_DayNightCyclePtr->GetCurrentDay()) };
	m_CurrentDayPopUp->UpdateString(currentDayString);

	m_DayNightCyclePtr->SetTime(7, 0 , 0);
}

void Game::Cleanup( )
{
	delete m_CameraPtr;
	delete m_PlayerPtr;
	delete m_MapPtr;
	delete m_DayNightCyclePtr;

	for (auto pickup : m_PickupsPtrArr)
	{
		delete pickup;
	}
	m_PickupsPtrArr.clear();

	delete m_PlayerBasePtr;
	delete m_CurrentDayPopUp;
	
	for (auto enemy : m_EnemiesPtrArr)
	{
		delete enemy;
	}
	m_EnemiesPtrArr.clear();

	for (auto enemy : m_SmallEnemiesPtrArr)
	{
		delete enemy;
	}
	m_SmallEnemiesPtrArr.clear();

	for (auto enemy : m_SmallNightEnemiesPtrArr)
	{
		delete enemy;
	}
	m_SmallNightEnemiesPtrArr.clear();

	delete m_IntroPopup;
	delete m_ControlsPopup;

	delete m_PlayerDeadPopup;
	delete m_PlayerWonPopup;
}

void Game::Update( float elapsedSec )
{
	if (m_PlayerPtr->GetIsDead()) return;
	if (m_PlayerWon) return;

	if (m_Paused) return;
	m_CurrentDayPopUp->Update(elapsedSec);


	int previousDay = m_DayNightCyclePtr->GetCurrentDay();

	m_DayNightCyclePtr->Update(elapsedSec);

	if (m_DayNightCyclePtr->GetCurrentDay() > previousDay)
	{
		std::string currentDayString { "Day: " + std::to_string(m_DayNightCyclePtr->GetCurrentDay()) };
		m_CurrentDayPopUp->UpdateString(currentDayString);
		m_CurrentDayPopUp->SetDisplay(true);

		SpawnPickups();
	}


	m_PlayerPtr->Update(elapsedSec);

	for (auto& enemy : m_EnemiesPtrArr)
	{
		enemy->Update(elapsedSec);
	}

	for (auto& enemy : m_SmallEnemiesPtrArr)
	{
		enemy->Update(elapsedSec);
	}

	if (!m_DayNightCyclePtr->GetDayTime())
	{
		for (auto& enemy : m_SmallNightEnemiesPtrArr)
		{
			enemy->Update(elapsedSec);
		}
	}

	HandlePickups();

	if (!m_MapPtr->IsWithinBounds(m_PlayerPtr->GetLocation()))
	{
		m_PlayerPtr->SetLocation(m_MapPtr->GetCenterPoint());
	}


	m_PlayerBasePtr->CheckPlayerInteraction(m_PlayerPtr->GetLocation());

	m_PlayerBasePtr->Update(elapsedSec);

	if(!m_DayNightCyclePtr->GetDayTime())
	{
		HandleNightTime();
	}

	if (m_DayNightCyclePtr->GetDayTime() or (m_PlayerBasePtr->GetIsPlayerInBase() and m_PlayerBasePtr->GetIsFireOn()))
	{
		m_PlayerPtr->SetStopHealing(false);
	}

	if (m_DayNightCyclePtr->GetDayTime())
	{
		HandleDayTime();
	}

	if (m_DayNightCyclePtr->GetHour() == 19 and m_DayNightCyclePtr->GetHour() < 20)
	{
		HandleEvening();
	}

	if (m_DayNightCyclePtr->GetCurrentDay() == 8)
	{
		m_PlayerWon = true;
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	m_CameraPtr->Aim(m_MapPtr->GetWidth(), m_MapPtr->GetHeight(), m_PlayerPtr->GetLocation());

	m_MapPtr->Draw();

	for (const auto pickup : m_PickupsPtrArr)
	{
		pickup->Draw();
	}

	m_PlayerBasePtr->Draw();

	m_PlayerPtr->Draw();

	for (const auto& enemy : m_EnemiesPtrArr)
	{
		enemy->Draw();
	}

	for (const auto& enemy : m_SmallEnemiesPtrArr)
	{
		enemy->Draw();
	}

	if (!m_DayNightCyclePtr->GetDayTime())
	{
		for (auto& enemy : m_SmallNightEnemiesPtrArr)
		{
			enemy->Draw();
		}
	}

	m_CameraPtr->Reset();

	// hud elements

	m_DayNightCyclePtr->Draw();

	m_PlayerPtr->DrawHudElements();
	m_PlayerBasePtr->DrawHudElements();



	m_CurrentDayPopUp->Draw();

	if (m_Paused and !m_DisplayControls)
	{
		utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
		utils::FillRect(0.f, 0.f, GetViewPort().width, GetViewPort().height);
		m_IntroPopup->Draw();
	}

	if (m_Paused and m_DisplayControls)
	{
		utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
		utils::FillRect(0.f, 0.f, GetViewPort().width, GetViewPort().height);
		m_ControlsPopup->Draw();
	}

	if (m_PlayerPtr->GetIsDead())
	{
		utils::SetColor(Color4f(0.f, 0.f, 0.f, 0.8f));
		utils::FillRect(0.f, 0.f, GetViewPort().width, GetViewPort().height);
		m_PlayerDeadPopup->Draw();
	}

	if (m_PlayerWon)
	{
		utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
		utils::FillRect(0.f, 0.f, GetViewPort().width, GetViewPort().height);
		m_PlayerWonPopup->Draw();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_PlayerPtr->ProcessKeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_PlayerPtr->ProcessKeyUpEvent(e);
	m_PlayerBasePtr->ProcessKeyUpEvent(e);

	switch (e.keysym.sym)
	{
	case SDLK_e:

		if (m_PlayerBasePtr->GetFirePlaceInteractionPoint())
		{
			DropOffWood();
		}

		if (m_PlayerBasePtr->GetDoorInteractionPoint())
		{
			StoreFood();
		}

		if (m_PlayerBasePtr->GetBedInteractionPoint())
		{
			Sleep();
		}

		break;

	case SDLK_f:

		if (m_PlayerBasePtr->GetDoorInteractionPoint())
		{
			GivePlayerFood();
		}

		break;

	case SDLK_i:
		if (!m_Paused) break;

		m_DisplayControls = !m_DisplayControls;
		break;

	default:
		break;
	}

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	if (m_Paused)
	{
		m_IntroPopup->ProcessMouseUpEvent(e);
		m_Paused = false;
		m_DisplayControls = false;
	}

	if (m_PlayerPtr->GetIsDead())
	{
		Restart();
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::SpawnPickups()
{
	const int numPickups{ 150 };

	for (int index{ 0 }; index < numPickups; ++index)
	{
		Pickup::PickupType type = (index % 2 == 0) ? Pickup::PickupType::wood : Pickup::PickupType::food;
		m_PickupsPtrArr.push_back(new Pickup(type, m_MapPtr->GetWidth(), m_MapPtr->GetHeight()));
	}
}

void Game::SpawnEnemies()
{
	//m_EnemyPtr = new Enemy{ m_MapPtr->GetCenterPoint(),"Enemy.png",200.f,40.f,m_PlayerPtr,m_PlayerBasePtr };

	for (int i = 0; i < 5; ++i)
	{
		Point2f enemyLocation{ float(rand() % int(m_MapPtr->GetWidth())), float(rand() % int(m_MapPtr->GetHeight())) };

		m_EnemiesPtrArr.push_back(new Enemy(enemyLocation, "Enemy.png", 200.0f, 40.0f, m_PlayerPtr, m_PlayerBasePtr));
	}

	for (int i = 0; i < 10; ++i)
	{
		Point2f enemyLocation{ float(rand() % int(m_MapPtr->GetWidth())), float(rand() % int(m_MapPtr->GetHeight())) };

		m_SmallEnemiesPtrArr.push_back(new Enemy(enemyLocation, "Enemy_Small.png", 100.0f, 15.0f, m_PlayerPtr, m_PlayerBasePtr));
	}

	for (int i = 0; i < 100; ++i)
	{
		Point2f enemyLocation{ float(rand() % int(m_MapPtr->GetWidth())), float(rand() % int(m_MapPtr->GetHeight())) };

		m_SmallNightEnemiesPtrArr.push_back(new Enemy(enemyLocation, "Enemy_Small.png", 100.0f, 15.0f, m_PlayerPtr, m_PlayerBasePtr));
	}
}

void Game::HandlePickups()
{
	for (auto it = m_PickupsPtrArr.begin(); it != m_PickupsPtrArr.end(); )
	{
		if ((m_PlayerPtr->GetCurrentFood(false) == 10) and ((*it)->GetType() == Pickup::PickupType::food))
		{
			++it;
			continue;
		}

		if ((m_PlayerPtr->GetCurrentWood(false) == 10) and ((*it)->GetType() == Pickup::PickupType::wood))
		{
			++it;
			continue;
		}

		if (utils::IsOverlapping(m_PlayerPtr->GetRect(), (*it)->GetRect()))
		{
			m_PlayerPtr->PickupItem((*it)->GetType());
			delete* it;
			it = m_PickupsPtrArr.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Game::DropOffWood()
{
	m_PlayerBasePtr->DepositFuel(m_PlayerPtr->GetCurrentWood(true));
}

void Game::StoreFood()
{
	m_PlayerBasePtr->StoreFood(m_PlayerPtr->GetCurrentFood(true));
}

void Game::GivePlayerFood()
{
	// Get current food amounts
	int currentPlayerFood = m_PlayerPtr->GetCurrentFood(false);
	int currentStoredFood = m_PlayerBasePtr->GetCurrentStoredFood();

	// Calculate how much food the player can take
	int maxPlayerCapacity = 10 - currentPlayerFood;
	int foodToGive = std::min(currentStoredFood, maxPlayerCapacity);

	// Give food to player and remove from storage
	m_PlayerPtr->GiveFood(foodToGive);
	m_PlayerBasePtr->RemoveFood(foodToGive);
}

void Game::HandleNightTime()
{
	m_PlayerPtr->TakeDamage(0.015f);
	m_PlayerPtr->SetStopHealing(true);

	if (m_HandledNightTime) return;

	m_PlayerPtr->SetInventoryColor(Color4f(1.f, 1.f, 1.f, 1.f));
	m_DayNightCyclePtr->SetClockColor(Color4f(1.f, 1.f, 1.f, 1.f));
	m_PlayerBasePtr->SetInventoryColor(Color4f(1.f, 1.f, 1.f, 1.f));
	m_HandledNightTime = true;
	m_HandledDayTime = false;
	m_HandledEvening = false;
}

void Game::HandleDayTime()
{
	if (m_HandledDayTime) return;

	m_PlayerPtr->SetInventoryColor(Color4f(0.f, 0.f, 0.f, 1.f));
	m_DayNightCyclePtr->SetClockColor(Color4f(0.f, 0.f, 0.f, 1.f));
	m_PlayerBasePtr->SetInventoryColor(Color4f(0.f, 0.f, 0.f, 1.f));
	m_HandledDayTime = true;
	m_HandledNightTime = false;
	m_HandledEvening = false;
}

void Game::HandleEvening()
{
	if (m_HandledEvening) return;

	m_PlayerPtr->SetInventoryColor(Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_DayNightCyclePtr->SetClockColor(Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_PlayerBasePtr->SetInventoryColor(Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_HandledEvening = true;
}

void Game::Sleep()
{
	if (m_DayNightCyclePtr->GetDayTime()) return;

	m_PlayerPtr->SetFoodPoints(10);
	m_PlayerBasePtr->RemoveWood(12);
	m_DayNightCyclePtr->SetTime(6, 59, 59);
}

void Game::Restart()
{
	Cleanup();
	Initialize();
}
