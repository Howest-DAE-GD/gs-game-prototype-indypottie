#include "pch.h"
#include "Game.h"
#include "Colonist.h"
#include <iostream>

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
	ShowControlsInConsole();

	for (int index{ 0 }; index < 9; ++index)
	{
		m_ColonistVector.push_back(new Colonist(Point2f(float(index + 10), float(index + 10))));
	}
	
	m_ColonistTaskManager = new ColonistTaskManager(m_ColonistVector,GetViewPort().width,GetViewPort().height);

	m_GameUI = new UserInterface();
}

void Game::Cleanup( )
{
	delete m_GameUI;

	delete m_ColonistTaskManager;

	for (Colonist* colonist : m_ColonistVector)
	{
		delete colonist;
	}
}

void Game::Update( float elapsedSec )
{
	for (Colonist* colonist : m_ColonistVector)
	{
		colonist->Update(elapsedSec);
	}

	m_ColonistTaskManager->UpdateTasks();
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground();
	

	for (Colonist* colonist : m_ColonistVector)
	{
		colonist->Draw();
	}

	m_GameUI->Draw(m_ColonistTaskManager->GetAmountOfWoodCutters(), m_ColonistTaskManager->GetAmountOfFarmers(), m_ColonistTaskManager->GetAmountOfGuards(), m_ColonistTaskManager->GetAmountOfWanderers());
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_w:
		m_ColonistTaskManager->TryToIncreaseWoodcutters();
		break;

	case SDLK_f:
		m_ColonistTaskManager->TryToIncreaseFarmers();
		break;

	case SDLK_g:
		m_ColonistTaskManager->TryToIncreaseGuards();
		break;


	case SDLK_s:
		m_ColonistTaskManager->TryToDecreaseWoodcutters();
		break;

	case SDLK_r:
		m_ColonistTaskManager->TryToDecreaseFarmers();
		break;

	case SDLK_t:
		m_ColonistTaskManager->TryToDecreaseGuards();
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	
	glClearColor(0.32f, 0.48f, 0.28f, 1.f);
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::ShowControlsInConsole() const
{
	std::cout << "--- CONTROLS ---" << std::endl << "INCREASE/DECREASE WOODCUTTERS: W / S" << std::endl << "INCREASE/DECREASE FARMERS: F / R" << std::endl << "INCREASE/DECREASE GUARDS: G / T" << std::endl << "-------------" << std::endl << std::endl;
}
