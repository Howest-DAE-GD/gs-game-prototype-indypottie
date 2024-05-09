#pragma once
#include "utils.h"
#include "Texture.h"
#include <vector>


class Map final
{

public:

	Map(float screenW, float screenH);

	~Map();

	// general methods
	void Draw() const;


	


private:
	// private methods
	void DrawTree(const Point2f& location) const;
	
	Texture* m_MainBuildingTexturePtr;
	Texture* m_FarmTexturePtr;

	float					m_ScreenWidth;
	float					m_ScreenHeight;
};

