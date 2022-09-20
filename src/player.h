#pragma once

#include "command.h"
#include "command_queue.h"
#include "magic.h"

#include <SFML/Window/Event.hpp>

#include <map>
#include <string>
#include <algorithm>


class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ActionCount
	};

private:
	std::map<sf::Keyboard::Key, Action> m_key_binding;
	std::map<Action, Command> m_action_binding;
private:
	void initialize_actions();
	static bool is_realtime_action(Action action);
public:
	Player();

	void handle_event(const sf::Event& event, CommandQueue& commands);
	void handle_realtime_input(CommandQueue& commands);

	void assign_key(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key get_assigned_key(Action action) const;
};