#include "label.h"


namespace GUI
{
	Label::Label(const std::string& text, const FontHolder& fonts)
		:
		m_text(text, fonts.get(Fonts::Main), 16)
	{
	}

	bool Label::is_selectable() const
	{
		return false;
	}

	void Label::handle_event(const sf::Event& event)
	{
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(m_text, states);
	}

	void Label::set_text(const std::string& text)
	{
		m_text.setString(text);
	}
}