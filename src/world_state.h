#pragma once

#include "state.h"
#include "player.h"
#include "utility.h"
#include "sprite_node.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <LDtkLoader/Project.hpp>
#include "tile_map.h"


class WorldState : public State
{
private:
    enum Layer
    {
        Background,
        Ground,
        LayerCount
    };
public:
    WorldState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handle_event(const sf::Event& event);

    void load_textures();
    void build_scene();

    void adapt_player_position();
    void adapt_player_velocity();
    // TODO:
    CommandQueue& get_command_queue();

private:
    ldtk::Project& m_ldtk_project;
    TileMap m_tile_map;
    Player& m_player;
    PlayerMagic* m_player_entity;

    Window& m_window;
    sf::View m_world_view;
    TextureHolder m_textures;

    SceneNode m_scene_graph;
    std::array<SceneNode*, Layer::LayerCount> m_scene_layers;
    CommandQueue m_command_queue;

    sf::FloatRect m_world_bounds;
    sf::Vector2f m_spawn_position;
    float m_scroll_speed;
};