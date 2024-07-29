#pragma once
#include "GameActor.h"
#include "Texture.h"


class ItemHUD : public GameActor
{
public:

	 ItemHUD(Point2f location, std::string itemName, int initialAmount);
	~ItemHUD();

	void Update(float elapsedSec) override;
	void Draw() const override;

	void IncreaseItem();
	void DecreaseItem();

	void AddItemAmount(int amount);
	void RemoveItemAmount(int amount);

private:

	void UpdateTextureString();

	Texture*	m_ItemHudTexturePtr;

	std::string m_ItemName;

	int			m_CurrentItems;
	
};

