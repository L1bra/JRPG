#pragma once

#include "state.h"
#include "world_map_state.h"
#include "player.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);
	~GameState();

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handle_event(const sf::Event& event);

private:
	WorldMapState m_world;
	Player& m_player;
};