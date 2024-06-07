#include "pch.h"
#include "Colony.h"

Colony::Colony(const int& amountOfColonists, float screenW, float screenH) : m_ScreenWidth { screenW }, m_ScreenHeight { screenH }, m_AmountOfColonists { amountOfColonists }, m_ColonyInventory { 0 , 0 }
{
	InitializeColony();
}

Colony::~Colony()
{
	delete m_MapPtr;
	delete m_GameUIPtr;
	delete m_ColonistTaskManagerPtr;

	for (Colonist* colonist : m_ColonistVectorPtr)
	{
		delete colonist;
	}
}

void Colony::Draw() const
{
	for (Colonist* colonist : m_ColonistVectorPtr)
	{
		colonist->Draw();
	}

	m_MapPtr->Draw();

	m_GameUIPtr->Draw(m_ColonistTaskManagerPtr->GetAmountOfWoodCutters(), m_ColonistTaskManagerPtr->GetAmountOfFarmers(), m_ColonistTaskManagerPtr->GetAmountOfGuards(), m_ColonistTaskManagerPtr->GetAmountOfWanderers());
}

void Colony::Update(float elapsedSec)
{
	for (Colonist* colonist : m_ColonistVectorPtr)
	{
		colonist->Update(elapsedSec);
	}

	m_ColonistTaskManagerPtr->UpdateTasks(elapsedSec);

	m_ColonyInventory.wood += m_ColonistTaskManagerPtr->AddWoodToInventory();
}

void Colony::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_w:
		m_ColonistTaskManagerPtr->TryToIncreaseWoodcutters();
		break;

	case SDLK_f:
		m_ColonistTaskManagerPtr->TryToIncreaseFarmers();
		break;

	case SDLK_g:
		m_ColonistTaskManagerPtr->TryToIncreaseGuards();
		break;


	case SDLK_s:
		m_ColonistTaskManagerPtr->TryToDecreaseWoodcutters();
		break;

	case SDLK_r:
		m_ColonistTaskManagerPtr->TryToDecreaseFarmers();
		break;

	case SDLK_t:
		m_ColonistTaskManagerPtr->TryToDecreaseGuards();
		break;
	}
}

void Colony::AddResourcesToColonyInventory(const int& wood, const int& food)
{
	m_ColonyInventory.wood += wood;
	m_ColonyInventory.food += food;

	std::cout << "Current Wood: " << m_ColonyInventory.wood << std::endl << "Current Food: " << m_ColonyInventory.food << std::endl;
}

void Colony::InitializeColony()
{
	ShowControlsInConsole();

	for (int index{ 0 }; index < m_AmountOfColonists; ++index)
	{
		m_ColonistVectorPtr.push_back(new Colonist(Point2f(m_ScreenWidth / 2, m_ScreenHeight / 2), this,false));
	}

	m_ColonistTaskManagerPtr = new ColonistTaskManager(m_ColonistVectorPtr, m_ScreenWidth, m_ScreenHeight);

	m_GameUIPtr = new UserInterface();

	m_MapPtr = new Map(m_ScreenWidth, m_ScreenHeight);

}

void Colony::ShowControlsInConsole() const
{
	std::cout << "--- CONTROLS ---" << std::endl << "INCREASE/DECREASE WOODCUTTERS: W / S" << std::endl << "INCREASE/DECREASE FARMERS: F / R" << std::endl << "INCREASE/DECREASE GUARDS: G / T" << std::endl << "-------------" << std::endl << std::endl;
}
