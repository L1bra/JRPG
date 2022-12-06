#pragma once

#include "player.h"
#include "window.h"
#include "resource_identifier.h"
#include "sprite_node.h"
#include "command.h"
#include "command_queue.h"
#include "utility.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>


class WorldMapState
{
private:
    enum Layer
    {
        Background,
        Ground,
        LayerCount
    };

    Window& m_window;
    sf::View m_world_view;
    TextureHolder m_textures;

    SceneNode m_scene_graph;
    std::array<SceneNode*, Layer::LayerCount> m_scene_layers;
    CommandQueue m_command_queue;

    sf::FloatRect m_world_bounds;
    sf::Vector2f m_spawn_position;
    float m_scroll_speed;
    PlayerMagic* m_player;
private:
    void load_textures();
    void build_scene();

    void adapt_player_position();
    void adapt_player_velocity();
public:
    WorldMapState(Window& window);
    ~WorldMapState();

    void update(sf::Time dt);
    void draw();

    CommandQueue& get_command_queue();
};