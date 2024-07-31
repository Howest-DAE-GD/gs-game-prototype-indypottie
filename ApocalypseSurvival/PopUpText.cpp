#include "pch.h"
#include "PopUpText.h"

PopUpText::PopUpText(const Point2f& location, std::string textToDisplay, float windowWidth, float windowHeight)
	: GameActor{ location }
	, m_MyText{ textToDisplay }
	, m_Display{ false }
	, m_TimeElapsed{ 0.f }
	, m_PopupDisplayTime{ 5.f }
	, m_TextTexturePtr{ new Texture { textToDisplay, "Poxast-R9Jjl.ttf", 30, Color4f(0.f,0.f,0.f,1.f) } }
	, m_WindowWidth{ windowWidth }
	, m_WindowHeight{ windowHeight }
{
	UpdateLocation();
}

PopUpText::~PopUpText()
{
	delete m_TextTexturePtr;
}

void PopUpText::Update(float elapsedSec)
{
	if (m_Display)
	{
		m_TimeElapsed += elapsedSec;
		std::cout << m_TimeElapsed << std::endl;
		if (m_TimeElapsed >= m_PopupDisplayTime)
		{
			m_Display = false;
			m_TimeElapsed = 0.0f;
		}
	}
}

void PopUpText::Draw() const
{
	if (m_Display)
	{
		m_TextTexturePtr->Draw(m_MyLocation);
	}
}

void PopUpText::SetDisplay(bool display)
{
	m_Display = display;
	if (display)
	{
		m_TimeElapsed = 0.0f;
	}
}

void PopUpText::UpdateString(std::string newString)
{
	delete m_TextTexturePtr;

	m_TextTexturePtr = new Texture{ newString, "Poxast-R9Jjl.ttf", 30, Color4f(0.f,0.f,0.f,1.f) };

	UpdateLocation();
}

void PopUpText::UpdateLocation()
{
	m_MyLocation.x = ((m_WindowWidth / 2.f) - m_TextTexturePtr->GetWidth() / 2.f);
	m_MyLocation.y = ((m_WindowHeight / 2.f) - m_TextTexturePtr->GetHeight() / 2.f) + 80.f;
}
