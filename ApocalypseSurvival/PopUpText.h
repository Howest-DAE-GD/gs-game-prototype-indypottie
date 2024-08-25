#pragma once
#include "GameActor.h"
#include "Texture.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "utils.h"

class PopUpText : public GameActor
{
public:

	PopUpText(const Point2f& location, std::string textToDisplay, float windowWidth, float windowHeight);
	~PopUpText();

	void Update(float elapsedSec) override;
	void Draw() const override;

	void SetDisplay(bool display);

	void UpdateString(std::string newString); // disabled if text is wrapped
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

	void WrapText(float width, const Point2f& location); // NOTE TO SELF this will disable updateString

	void SetFontSize(int fontSize);

	void SetColor(const Color4f& textColor);

private:

	void UpdateLocation();


	bool m_Display;
	std::string m_MyText;
	std::vector<std::string> m_WrappedText;
	Texture*	m_TextTexturePtr;

	Color4f m_TextColor;

	float m_PopupDisplayTime;
	float m_TimeElapsed;

	float m_TextWidth; // used for wrap

	float m_WindowWidth;
	float m_WindowHeight;

	bool m_IsWrappedText;

	int m_FontSize;
};

