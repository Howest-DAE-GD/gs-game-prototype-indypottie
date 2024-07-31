#pragma once
#include "BaseGame.h"

#include <iostream>

#include "Camera.h"
#include "GameActor.h"
#include "Player.h"
#include "Map.h"
#include "DayNightCycle.h"
#include "Pickup.h"
#include "PlayerBase.h"
#include "utils.h"
#include "PopUpText.h"

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	Player* m_PlayerPtr;

	Camera* m_CameraPtr;

	Map*	m_MapPtr;

	DayNightCycle* m_DayNightCyclePtr;

	PlayerBase* m_PlayerBasePtr;

	std::vector<Pickup*> m_PickupsPtrArr;

	PopUpText* m_CurrentDayPopUp;

	void SpawnPickups();
	void HandlePickups();

	void DropOffWood();
	void StoreFood();

	void GivePlayerFood();

	void HandleNightTime();
};