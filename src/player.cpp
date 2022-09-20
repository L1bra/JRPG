#include "player.h"


struct MagicMover
{
	sf::Vector2f m_velocity;

	MagicMover(float vx, float vy)
		:
		m_velocity(vx, vy)
	{
	}

	void operator() (PlayerMagic& magic, sf::Time) const
	{
		magic.accelerate(m_velocity);
	}
};

Player::Player()
{
	// Set initial key binding
	m_key_binding[sf::Keyboard::Left] = MoveLeft;
	m_key_binding[sf::Keyboard::Right] = MoveRight;
	m_key_binding[sf::Keyboard::Up] = MoveUp;
	m_key_binding[sf::Keyboard::Down] = MoveDown;

	// Set initial action bindings
	initialize_actions();

	// Assign all categories to player's entity
	for (auto& pair : m_action_binding)
		pair.second.category = Category::PlayerEntity;
}

void Player::handle_event(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding trigger command if so
		auto found = m_key_binding.find(event.key.code);
		if (found != m_key_binding.end() && !is_realtime_action(found->second))
		{
			commands.push(m_action_binding[found->second]);
		}
	}
}

void Player::handle_realtime_input(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for (auto& pair : m_key_binding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && is_realtime_action(pair.second))
		{
			commands.push(m_action_binding[pair.second]);
		}
	}
}

void Player::assign_key(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto it = m_key_binding.begin(); it != m_key_binding.end();)
	{
		if (it->second == action)
			m_key_binding.erase(it++);
		else
			++it;
	}

	// Insert new binding
	m_key_binding[key] = action;
}

sf::Keyboard::Key Player::get_assigned_key(Action action) const
{
	for (auto& pair : m_key_binding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initialize_actions()
{
	const float player_speed = 200.f;

	m_action_binding[MoveLeft].action	= derived_action<PlayerMagic>(MagicMover(-player_speed, 0.f));
	m_action_binding[MoveRight].action	= derived_action<PlayerMagic>(MagicMover(+player_speed, 0.f));
	m_action_binding[MoveUp].action		= derived_action<PlayerMagic>(MagicMover(0.f, -player_speed));
	m_action_binding[MoveDown].action	= derived_action<PlayerMagic>(MagicMover(0.f, +player_speed));
}

bool Player::is_realtime_action(Action action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveUp:
		case MoveDown:
				return true;
		default:
				return false;
	}
}