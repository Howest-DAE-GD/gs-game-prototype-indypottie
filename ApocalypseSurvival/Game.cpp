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
	m_MapPtr = new Map{ Point2f(0.f,0.f),"Map_tiled.png",2000.f,2000.f };

	m_PlayerPtr = new Player{ m_MapPtr->GetCenterPoint(),"Player.png",Point2f{100.f,100.f} };
	m_CameraPtr = new Camera{ GetViewPort().width, GetViewPort().height };

	m_ClockPtr = new Clock(Point2f(GetViewPort().width, GetViewPort().height), GetViewPort().width, GetViewPort().height);

	SpawnPickups();
}

void Game::Cleanup( )
{
	delete m_CameraPtr;
	delete m_PlayerPtr;
	delete m_MapPtr;
	delete m_ClockPtr;

	for (auto pickup : m_PickupsPtrArr)
	{
		delete pickup;
	}
	m_PickupsPtrArr.clear();
}

void Game::Update( float elapsedSec )
{
	m_ClockPtr->Update(elapsedSec);

	m_PlayerPtr->Update(elapsedSec);

	HandlePickups();

	if (!m_MapPtr->IsWithinBounds(m_PlayerPtr->GetLocation()))
	{
		m_PlayerPtr->SetLocation(m_MapPtr->GetCenterPoint());
	}

	//m_PlayerPtr->SetCanMove(m_MapPtr->IsWithinBounds(m_PlayerPtr->GetLocation()));

	//std::cout << m_PlayerPtr->GetLocation().x << " , " << m_PlayerPtr->GetLocation().y << std::endl;

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


	m_PlayerPtr->Draw();

	m_CameraPtr->Reset();

	m_PlayerPtr->DrawHudElements();

	m_ClockPtr->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_PlayerPtr->ProcessKeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_PlayerPtr->ProcessKeyUpEvent(e);

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	m_PlayerPtr->TakeDamage(5.f);

	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::SpawnPickups()
{
	const int numPickups{ 50 };

	for (int index{ 0 }; index < numPickups; ++index)
	{
		Pickup::PickupType type = (index % 2 == 0) ? Pickup::PickupType::wood : Pickup::PickupType::food;
		m_PickupsPtrArr.push_back(new Pickup(type, m_MapPtr->GetWidth(), m_MapPtr->GetHeight()));
	}
}

void Game::HandlePickups()
{
	for (auto it = m_PickupsPtrArr.begin(); it != m_PickupsPtrArr.end(); )
	{
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