#ifndef LOCAL_MAP_STATE_H_
#define LOCAL_MAP_STATE_H_

#include "state_machine.h"
#include "entity.h"
#include "gui.h"
#include "gfx.h"

class LocalMapState : public State
{
private:
    enum 
    {
        PLAYER_INDEX = 0,
        ENEMY_OFFSET = 3,
        MAX_ENTITIES = 4
    };

    std::shared_ptr<sf::Texture> m_LocalMapTexture;
    sf::Sprite m_LocalMapSprite;

    GFX* gfx_data;
    const sf::VideoMode& vm;
    Entity entities[MAX_ENTITIES];
private:
    void init_party_entities();
public:
    LocalMapState(GFX* gfx);
    ~LocalMapState();

    void Input(sf::Keyboard::Key key_code) override;
    void Update(float elapsedTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnEnter() override;
    void OnExit() override;
};


#endif  // LOCAL_MAP_STATE_H_