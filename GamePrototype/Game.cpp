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
	m_ColonyPtr = new Colony(9, GetViewPort().width, GetViewPort().height);
}

void Game::Cleanup( )
{
	delete m_ColonyPtr;
}

void Game::Update( float elapsedSec )
{
	m_ColonyPtr->Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground();

	m_ColonyPtr->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_ColonyPtr->ProcessKeyUpEvent(e);
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{

}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ClearBackground( ) const
{
	glClearColor(0.32f, 0.48f, 0.28f, 1.f);
	glClear( GL_COLOR_BUFFER_BIT );
}