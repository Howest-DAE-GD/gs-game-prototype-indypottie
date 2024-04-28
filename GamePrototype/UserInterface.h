#pragma once
#include "utils.h"
#include "Texture.h"
#include "ColonistTaskManager.h"
#include <vector>

class UserInterface final
{
public:

	// constructor(s)
	UserInterface();
	
	~UserInterface();

	// general methods
	void Draw(const int& currentWoodCutters, const int& currentFarmers, const int& currentGuards, const int& currentWanderers) const;

	// constants

	const std::string m_FONT_PATH{ "ChakraPetch-Regular.ttf" };

	const Color4f m_TEXT_COLOR{ 1.f,1.f,1.f,1.f };
	const Color4f m_UI_BOXES_COLOR{ 0.41f, 0.47f, 0.54f, 0.8f };

	const int m_TEXT_SIZE	  { 20 };


private:

	void InitializeUI();

	void DrawTaskDividerRect(const int& currentWoodCutters, const int& currentFarmers, const int& currentGuards, const int& currentWanderers) const;

	Rectf m_TaskDividerRect;

	Texture* m_WoodCuttersStringTexturePtr;
	Texture* m_FarmersStringTexturePtr;
	Texture* m_GuardsStringTexturePtr;
	Texture* m_WanderersStringTexturePtr;

	std::vector<Texture*> m_Numbers;
};

