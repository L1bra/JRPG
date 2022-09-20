#pragma once

// Forward declaration of SFML types
namespace sf
{
	class Texture;
}

namespace Textures
{
	enum ID
	{
        // background (temp)
        LoadingBackground,
        MainMenuBackground,
        WorldBackground,
        LocalBackground,
        BattleBackground,

        // entities
        MAGIC0,
        MAGIC1,
        MAGIC2,
        ENEMY
	};
}   

// Forward declaration and few typedefs
template<typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureHolder;