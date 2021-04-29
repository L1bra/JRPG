#ifndef ACTION_H_
#define ACTION_H_

#include "state_machine.h"
#include "entity.h"
#include "random_gen.h"

#include <array>


static const std::size_t ENTITIES = 3;
static const std::size_t MAX_ENTITIES = 6;

enum class Action_name : uint8_t
{
    Attack = 0,
    Spell,
    Item,
    Def,
};


class Action
{
public:
    virtual ~Action() {};

    virtual void Input(sf::Keyboard::Key key_code) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

    virtual void TimeRemaining() = 0;
    virtual void Decide() = 0;
    virtual bool isReady() = 0;
};


class PlayerAction : public Action
{
private:
    std::shared_ptr<sf::Texture> action_frame_texture;
    sf::Sprite action_frame_sprite;

    std::shared_ptr<sf::Texture> cursor_texture;
    sf::Sprite cursor_sprite;
    unsigned int cursor_index;

    Entity& entity;
    const std::array<Entity, MAX_ENTITIES> entities;

    bool spawn_action_frame;
public:
    bool is_ready;
private:
    void cursor_init();
public:
    PlayerAction(Entity& entity, const std::array<Entity, MAX_ENTITIES> entities);
    ~PlayerAction();

    void Input(sf::Keyboard::Key key_code) override;
    void Render(sf::RenderWindow& window) override;
    void Update(float dt) override;

    void TimeRemaining() override;
    void Decide() override;
    bool isReady() override;
};


class AIAction : public Action
{
private:
    std::shared_ptr<sf::Texture> m_AIActionTexture;
    sf::Sprite m_AIActionSprite;

    Entity& entity;
public:
    bool is_ready;
public:
    AIAction(Entity& entity, const std::array<Entity, MAX_ENTITIES> entities);
    ~AIAction();

    void Input(sf::Keyboard::Key key_code) override;
    void Render(sf::RenderWindow& window) override;
    void Update(float dt) override;

    void TimeRemaining() override;
    void Decide() override;
    bool isReady() override;
};


#endif  // ACTION_H_