#ifndef ACTION_H_
#define ACTION_H_

#include "state_machine.h"
#include "entity.h"
#include "random_gen.h"
#include "gui.h"

#include <array>


// TODO: resolve identical name conflict
static const std::size_t MAX_ENTITY_INDEX = 2;   // MAX ENTITY INDEX
static const std::size_t ENTITIES = 3;
static const std::size_t MAX_ENTITIES = 6;
static const std::size_t MAX_ACTION_BTN = 4;
static const double CURSOR_OFFSET = 40.f;

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
    enum class ACTION_BTN { ATTACK = 0, SPELL, ITEM, DEF };

    //std::shared_ptr<sf::Texture> action_frame_texture;
    //sf::Sprite action_frame_sprite;
    sf::RectangleShape action_frame;
    std::map<std::string, gui::Button*> action_frame_buttons;

    std::shared_ptr<sf::Texture> cursor_texture;
    sf::Sprite cursor_sprite;
    unsigned int cursor_index;

    Entity& entity;
    const std::array<Entity, MAX_ENTITIES> entities;

    bool spawn_action_frame;
public:
    bool is_ready;
private:
    void init_gui();
    void init_cursor();
public:
    PlayerAction(Entity& entity, const std::array<Entity, MAX_ENTITIES>& entities);
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
    AIAction(Entity& entity, const std::array<Entity, MAX_ENTITIES>& entities);
    ~AIAction();

    void Input(sf::Keyboard::Key key_code) override;
    void Render(sf::RenderWindow& window) override;
    void Update(float dt) override;

    void TimeRemaining() override;
    void Decide() override;
    bool isReady() override;
};


#endif  // ACTION_H_