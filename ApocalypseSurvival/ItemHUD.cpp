#include "pch.h"
#include "ItemHUD.h"

ItemHUD::ItemHUD(Point2f location, std::string itemName, int initialAmount)
	: GameActor(location)
	, m_ItemName{ itemName }
	, m_CurrentItems{ initialAmount }
	, m_ItemHudTexturePtr{ nullptr }
{
	UpdateTextureString();
}

ItemHUD::~ItemHUD()
{
	delete m_ItemHudTexturePtr;
}

void ItemHUD::Update(float elapsedSec)
{
}

void ItemHUD::Draw() const
{
	m_ItemHudTexturePtr->Draw(m_MyLocation);
}

void ItemHUD::IncreaseItem()
{
	m_CurrentItems += 1;

	UpdateTextureString();
}

void ItemHUD::DecreaseItem()
{
	if (m_CurrentItems == 0) return;

	m_CurrentItems -= 1;

	UpdateTextureString();
}

void ItemHUD::AddItemAmount(int amount)
{
	m_CurrentItems += amount;

	UpdateTextureString();
}

void ItemHUD::RemoveItemAmount(int amount)
{
	if (m_CurrentItems == 0) return;
	
	m_CurrentItems -= amount;

	UpdateTextureString();
}

void ItemHUD::UpdateTextureString()
{
	std::string textureString { m_ItemName + ": " + std::to_string(m_CurrentItems) };

	if (m_ItemHudTexturePtr != nullptr)
	{
		delete m_ItemHudTexturePtr;
	}
	
	m_ItemHudTexturePtr = new Texture{ textureString,"Poxast-R9Jjl.ttf",15 ,Color4f(0.f,0.f,0.f,1.f) };
}
