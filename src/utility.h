#pragma once

// center_origin
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

// to_string
#include <sstream>

// 
#include <cmath>


namespace sf
{
	class Sprite;
	class Text;
}


namespace gui
{
	template<typename T>
	void center_origin(T& ent)
	{
		sf::FloatRect bounds = ent.getLocalBounds();
		ent.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	template<typename T>
	float p2px(const float p, const T& vm)
	{
		return std::floor(static_cast<float>(vm.width) * (p / 100.f));
	}

	template<typename T>
	float p2py(const float p, const T& vm)
	{
		return std::floor(static_cast<float>(vm.height) * (p / 100.f));
	}

	template<typename T>
	unsigned cacl_char_size(const T& vm, const unsigned mod = 60)
	{
		return static_cast<unsigned>((vm.width + vm.height) / mod);
	}
}

// since std::to_string doesnt work on mingw we have to implement
// our own to support all platform
template<typename T>
std::string to_string(const T& value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}