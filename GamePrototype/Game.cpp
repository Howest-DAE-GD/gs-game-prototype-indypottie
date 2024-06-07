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

	//m_TestZombie1 = new Colonist(Point2f(500.f,300.f), m_ColonyPtr, true);
	//m_TestZombie2 = new Colonist(Point2f(300.f, 500.f), m_ColonyPtr, true);
	//m_TestZombie3 = new Colonist(Point2f(800.f, 900.f), m_ColonyPtr, true);
}

void Game::Cleanup()
{
	delete m_ColonyPtr;

	//delete m_TestZombie1;
	//delete m_TestZombie2;
	//delete m_TestZombie3;
}

void Game::Update( float elapsedSec )
{
	m_ColonyPtr->Update(elapsedSec);

	//m_TestZombie1->Update(elapsedSec);
	//m_TestZombie2->Update(elapsedSec);
	//m_TestZombie3->Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground();

	m_ColonyPtr->Draw();

	//m_TestZombie1->Draw();
	//m_TestZombie2->Draw();
	//m_TestZombie3->Draw();
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