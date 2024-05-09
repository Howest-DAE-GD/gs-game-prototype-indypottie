#include "pch.h"
#include "UserInterface.h"
#include <string>

UserInterface::UserInterface()
{
	InitializeUI();
}

UserInterface::~UserInterface()
{
	delete m_WoodCuttersStringTexturePtr;
	delete m_FarmersStringTexturePtr;
	delete m_GuardsStringTexturePtr;
	delete m_WanderersStringTexturePtr;

	for (Texture* number : m_Numbers)
	{
		delete number;
	}
}

void UserInterface::Draw(const int& currentWoodCutters, const int& currentFarmers, const int& currentGuards, const int& currentWanderers) const
{
	DrawTaskDividerRect(currentWoodCutters, currentFarmers, currentGuards, currentWanderers);

}

void UserInterface::InitializeUI()
{
	for (int index{ 0 }; index < 10; ++index)
	{
		m_Numbers.push_back(new Texture(std::to_string(index),m_FONT_PATH,m_TEXT_SIZE,m_TEXT_COLOR));
	}

	m_WoodCuttersStringTexturePtr	 = new Texture("Woodcutters: ", m_FONT_PATH, m_TEXT_SIZE, m_TEXT_COLOR);
	m_FarmersStringTexturePtr		 = new Texture("Farmers: "    , m_FONT_PATH, m_TEXT_SIZE, m_TEXT_COLOR);
	m_GuardsStringTexturePtr		 = new Texture("Guards: "     , m_FONT_PATH, m_TEXT_SIZE, m_TEXT_COLOR);
	m_WanderersStringTexturePtr		 = new Texture("Wanderers: "  , m_FONT_PATH, m_TEXT_SIZE, m_TEXT_COLOR);

	m_TaskDividerRect.bottom = 0.f;
	m_TaskDividerRect.left	 = 0.f;

	m_TaskDividerRect.width	 = 300.f;
	m_TaskDividerRect.height = 150.f;
	

	
}

void UserInterface::DrawTaskDividerRect(const int& currentWoodCutters, const int& currentFarmers, const int& currentGuards, const int& currentWanderers) const
{
	utils::SetColor(m_UI_BOXES_COLOR);

	utils::FillRect(m_TaskDividerRect);

	m_WoodCuttersStringTexturePtr->Draw(Point2f(10.f, 110.f));
	m_FarmersStringTexturePtr->Draw(Point2f(10.f, 80.f));
	m_GuardsStringTexturePtr->Draw(Point2f(10.f, 50.f));
	m_WanderersStringTexturePtr->Draw(Point2f(10.f, 20.f));

	if (currentWoodCutters < 10)
	{
		m_Numbers.at(currentWoodCutters)->Draw(Point2f(m_WoodCuttersStringTexturePtr->GetWidth() + 10.f, 110.f));
	}

	if (currentFarmers < 10)
	{
		m_Numbers.at(currentFarmers)->Draw(Point2f(m_FarmersStringTexturePtr->GetWidth() + 10.f, 80.f));
	}

	if (currentGuards < 10)
	{
		m_Numbers.at(currentGuards)->Draw(Point2f(m_GuardsStringTexturePtr->GetWidth() + 10.f, 50.f));
	}

	if (currentWanderers < 10)
	{
		m_Numbers.at(currentWanderers)->Draw(Point2f(m_WanderersStringTexturePtr->GetWidth() + 10.f, 20.f));
	}
}
