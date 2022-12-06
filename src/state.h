#pragma once

#include "window.h"
#include "state_identifier.h"
#include "resource_identifier.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


namespace sf
{
	class RenderWindow;
}

class StateStack;
class Player;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(Window& window, TextureHolder& textures, FontHolder& fonts, Player& player);

		Window* m_window;
		TextureHolder* m_textures;
		FontHolder* m_fonts;
		Player* m_player;
	};

public:
	State(StateStack& stack, Context context);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handle_event(const sf::Event& event) = 0;

protected:
	void request_stack_push(States::ID state_id);
	void request_stack_pop();
	void request_state_clear();

	Context get_context() const;
private:
	StateStack* m_stack;
	Context m_context;
};