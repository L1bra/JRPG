#ifndef WORLD_MAP_STATE_H_
#define WORLD_MAP_STATE_H_

#include "state_machine.h"
#include "random_gen.h"
#include "entity.h"
#include "gui.h"
#include "gfx.h"
#include "list.h"

#include "input.h"

#include <array>


enum class Choose_state : uint8_t
{
    Friend = 0,
    Enemy
};


class WorldMapState : public State
{
private:
    // const
    enum
    {
        // general
        PLAYER_INDEX = 0,
        ENEMY_OFFSET = 2,
        MAX_ENTITIES = 8,
        MAX_PARTY_ENTITIES = 3,

        
        // party
        BLUE_INDEX = 0,
        RED_INDEX = 1,
        YELLOW_INDEX = 2
    };

    InputHandler input;

    sf::Vector2f PLAYER_SPAWN_POSITION;

    // other
    std::shared_ptr<sf::Texture> m_WorldMapTexture;
    sf::Sprite m_WorldMapSprite;

    sf::Sprite m_ArrowSprite;
    std::shared_ptr<sf::Texture> m_ArrowTexture;

    sf::Text text;
    std::shared_ptr<sf::Font> m_Font;

    GFX* gfx_data;
    const sf::VideoMode& vm;  // think

    Choose_state m_Choose_state;

    bool arrow_spawned; // need better solution
    bool enemy_spawned;
    bool text_drawn;

    // Entity entities[MAX_ENTITIES];
    // std::vector<Entity> enemies;
private:
    void kill_entity(Entity& entity);   // TODO
    void damage_entity(Entity& entity, int amount);
    // Entity get_current_entity();

    void spawn_enemy();
    void init_party_entity();
    void update_positions();
public:
    WorldMapState(GFX* gfx);
    ~WorldMapState();

    void Input() override;
    void Update(float elapsedTime) override;
    void Render(Window& window) override;
    void OnEnter() override;
    void OnExit() override;
};

#endif  // WORLD_MAP_STATE_H_