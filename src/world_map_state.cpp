#include "world_map_state.h"

WorldMapState::WorldMapState(Window& window)
	:
	m_window(window),
	m_world_view(window.get_default_view()),
	m_textures(),
	m_scene_graph(),
	m_scene_layers(),
	m_world_bounds(0.f, 0.f, m_world_view.getSize().x, 2000.f), // TODO
	m_spawn_position({ gui::p2pX(6.f, m_window.get_gfx().resolution),
		gui::p2pY(70.f, m_window.get_gfx().resolution) }),
	m_scroll_speed(-50.f),
	m_player(nullptr)
{
	load_textures();
	build_scene();

	m_world_view.setCenter(m_spawn_position);
}

WorldMapState::~WorldMapState()
{

}

void WorldMapState::update(sf::Time dt)
{
	// Scroll the world
	m_world_view.move(0.f, m_scroll_speed * dt.asSeconds());
	m_player->set_velocity(0.f, 0.f);
	
	// Forward commands to the scene graph
	while (!m_command_queue.is_empty())
	{
		m_scene_graph.on_command(m_command_queue.pop(), dt);
	}

	adapt_player_velocity();

	// Apply movement
	m_scene_graph.update(dt);
	adapt_player_position();
}

void WorldMapState::draw()
{
	m_window.set_view(m_world_view);
	// Window class internally calls SceneNode::draw() function
	m_window.draw(m_scene_graph);
}

void WorldMapState::load_textures()
{
	m_textures.load(Textures::WorldBackground, "res/background/background0.png");
	m_textures.load(Textures::MAGIC0, "res/sprites/magic0.png");
	m_textures.load(Textures::ENEMY, "res/sprites/enemy.png");
}

void WorldMapState::build_scene()
{
	for (std::size_t i = 0; i < Layer::LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		m_scene_layers[i] = layer.get();
		m_scene_graph.attach_child(std::move(layer));
	}

	sf::Texture& texture = m_textures.get(Textures::WorldBackground);
	sf::IntRect texture_rect(m_world_bounds);
	texture.setRepeated(true);

	// Add background sprite
	std::unique_ptr<SpriteNode> background_sprite(new SpriteNode(texture, texture_rect));
	background_sprite->setPosition(m_world_bounds.left, m_world_bounds.top);
	m_scene_layers[Layer::Background]->attach_child(std::move(background_sprite));

	// Add player
	std::unique_ptr<PlayerMagic> magic(new PlayerMagic(m_textures));
	m_player = magic.get();
	m_player->setPosition(m_spawn_position);
	m_player->set_velocity(40.f, m_scroll_speed);
	m_scene_layers[Layer::Ground]->attach_child(std::move(magic));
}

CommandQueue& WorldMapState::get_command_queue()
{
	return m_command_queue;
}

void WorldMapState::adapt_player_position()
{
	// Keep player's position inside the screen bounds, at least border_distance units from the border
	sf::FloatRect view_bounds(m_world_view.getCenter() - m_world_view.getSize() / 2.f, m_world_view.getSize());
	const float border_distance = 40.f;

	sf::Vector2f position = m_player->getPosition();
	position.x = std::max(position.x, view_bounds.left + border_distance);
	position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
	position.y = std::max(position.y, view_bounds.top + border_distance);
	position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);
	m_player->setPosition(position);
}

void WorldMapState::adapt_player_velocity()
{
	sf::Vector2f velocity = m_player->get_velocity();

	// if moving diagonally, reduce velocity (to have the same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		m_player->set_velocity(velocity / std::sqrt(2.f));

	// add scrolling velocity
	m_player->accelerate(0.f, m_scroll_speed);
}