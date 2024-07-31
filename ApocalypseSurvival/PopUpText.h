#pragma once
#include "GameActor.h"
#include "Texture.h"
#include "iostream"

class PopUpText : public GameActor
{
public:

	PopUpText(const Point2f& location, std::string textToDisplay, float windowWidth, float windowHeight);
	~PopUpText();

	void Update(float elapsedSec) override;
	void Draw() const override;

	void SetDisplay(bool display);

	void UpdateString(std::string newString);

private:

	void UpdateLocation();

	bool m_Display;
	std::string m_MyText;
	Texture*	m_TextTexturePtr;

	float m_PopupDisplayTime;
	float m_TimeElapsed;

	float m_WindowWidth;
	float m_WindowHeight;
};

