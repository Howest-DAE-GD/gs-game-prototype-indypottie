#pragma once
#include "utils.h"
#include "Colonist.h"
#include "ColonistTaskManager.h"
#include "UserInterface.h"
#include "Map.h"
#include <iostream>
#include <vector>

class Colonist;
class ColonistTaskManager;
class UserInterface;
class Map;

class Colony
{
public:

	Colony(const int& amountOfColonists, float screenW, float screenH);

	~Colony();


	// general methods
	void Draw() const;
	void Update(float elapsedSec);
	
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);

	//setters
	void AddResourcesToColonyInventory(const int& wood, const int& food);

	//getters




	



private:
	// private methods
	void InitializeColony();
	void ShowControlsInConsole() const;

	// private structs 
	struct Inventory
	{
		int wood;
		int food;
	};


	// data members
	float					m_ScreenWidth;
	float					m_ScreenHeight;

	int						m_AmountOfColonists;
	
	Inventory				m_ColonyInventory;

	Map*					m_MapPtr;

	std::vector<Colonist*>	m_ColonistVectorPtr;

	ColonistTaskManager*	m_ColonistTaskManagerPtr;

	UserInterface*			m_GameUIPtr;

};

