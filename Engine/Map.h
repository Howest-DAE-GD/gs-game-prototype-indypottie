#pragma once
#include "utils.h"
#include <vector>


class Map final
{

public:

	Map(float screenW, float screenH);

	// general methods
	void Draw() const;


	

	
	


private:
	// private methods
	void DrawTree(const Point2f& location) const;

	std::vector<Rectf> m_Buildings;
};

