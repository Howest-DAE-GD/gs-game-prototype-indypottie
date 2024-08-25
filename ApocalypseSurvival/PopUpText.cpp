#include "pch.h"
#include "PopUpText.h"

PopUpText::PopUpText(const Point2f& location, std::string textToDisplay, float windowWidth, float windowHeight)
	: GameActor{ location }
	, m_MyText{ textToDisplay }
	, m_Display{ false }
	, m_TimeElapsed{ 0.f }
	, m_PopupDisplayTime{ 5.f }
	, m_TextColor{ Color4f(0.f,0.f,0.f,1.f) }
	, m_TextTexturePtr{ new Texture { textToDisplay, "Poxast-R9Jjl.ttf", 30, m_TextColor } }
	, m_WindowWidth{ windowWidth }
	, m_WindowHeight{ windowHeight }
	, m_IsWrappedText { false }
	, m_TextWidth { 0.f }
	, m_FontSize{ 30 }
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
		if (m_TimeElapsed >= m_PopupDisplayTime)
		{
			m_Display = false;
			m_TimeElapsed = 0.0f;
		}
	}
}

void PopUpText::Draw() const
{
	if (m_Display and !m_IsWrappedText)
	{
		m_TextTexturePtr->Draw(m_MyLocation);
	}
	else if (m_Display and m_IsWrappedText)
	{
		// Draw background for the pop-up (optional)
		//utils::SetColor(Color4f(0.f, 0.f, 0.f, 0.5f));
		//utils::FillRect(m_MyLocation.x, m_MyLocation.y, m_TextWidth, m_WrappedText.size() * 45.f);

		// Draw the wrapped text
		float yOffset = m_MyLocation.y + m_WrappedText.size() * 45.f;
		for (const auto& line : m_WrappedText)
		{
			Texture textTexture(line, "Poxast-R9Jjl.ttf", 15, m_TextColor);
			textTexture.Draw(Point2f(m_MyLocation.x, yOffset));
			yOffset -= 45.f;
		}
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
	if (m_IsWrappedText) return;

	delete m_TextTexturePtr;

	m_TextTexturePtr = new Texture{ newString, "Poxast-R9Jjl.ttf", m_FontSize, m_TextColor };

	UpdateLocation();
}

void PopUpText::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (!m_IsWrappedText) return;

	m_Display = false;
}

void PopUpText::UpdateLocation()
{
	m_MyLocation.x = ((m_WindowWidth / 2.f) - m_TextTexturePtr->GetWidth() / 2.f);
	m_MyLocation.y = ((m_WindowHeight / 2.f) - m_TextTexturePtr->GetHeight() / 2.f) + 80.f;
}

void PopUpText::WrapText(float width, const Point2f& location)
{
	m_IsWrappedText = true;
	m_TextWidth = width;

	m_MyLocation = location;

	const std::string& text{ m_MyText };

	std::istringstream InputText(text);
	std::string word;
	std::string line;
	float lineWidth {0.f};

	while (InputText >> word)
	{
		float wordWidth = Texture(word, "Poxast-R9Jjl.ttf", 15, m_TextColor).GetWidth();

		if (line.find("^") != std::string::npos)
		{
			line.erase(line.end() - 1);

			m_WrappedText.push_back(line);
			line.clear();
			lineWidth = 0.f;
		}
		else if (lineWidth + wordWidth > width)
		{
			m_WrappedText.push_back(line);
			line.clear();
			lineWidth = 0.f;
		}


		line += (line.empty() ? "" : " ") + word;
		lineWidth += wordWidth + Texture(" ", "Poxast-R9Jjl.ttf", 15, m_TextColor).GetWidth();
	}
	if (!line.empty())
	{
		m_WrappedText.push_back(line);
	}

}

void PopUpText::SetFontSize(int fontSize)
{
	m_FontSize = fontSize;
	UpdateString(m_MyText);
}

void PopUpText::SetColor(const Color4f& textColor)
{
	m_TextColor = textColor;
	UpdateString(m_MyText);
}
