#ifndef ACTION_H_
#define ACTION_H_

#include "state_machine.h"
#include "entity.h"
#include "random_gen.h"
#include "gui.h"


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
    virtual void Render(Window& window) = 0;

    virtual void TimeRemaining() = 0;
    virtual void Decide() = 0;
    virtual bool isReady() = 0;
};


class PlayerAction : public Action
{
private:
    enum ACTION_BTN { ATTACK = 0, SPELL, ITEM, DEF };

    std::shared_ptr<sf::Texture> action_frame_texture;
    std::shared_ptr<sf::Font> action_frame_font;
    std::shared_ptr<sf::Texture> cursor_texture;
    sf::Sprite action_frame_sprite;
    sf::Sprite cursor_sprite;
    bool spawn_action_frame;

    // sf::RectangleShape action_frame;
    std::map<std::string, gui::Button*> action_frame_buttons;
    Entity& entity;
    // const std::array<Entity, MAX_ENTITIES> entities;

    unsigned int cursor_index;
    sf::Vector2f cursor_pos;

    bool enter_pressed;
public:
    bool is_ready;
private:
    void init_gui();
    void init_cursor();

    void update_buttons(sf::Vector2f pos);
    void render_buttons(Window& window);
    void free_buttons();
public:
    PlayerAction();
    ~PlayerAction();

    void Input(sf::Keyboard::Key key_code) override;
    void Render(Window& window) override;
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
    AIAction();
    ~AIAction();

    void Input(sf::Keyboard::Key key_code) override;
    void Render(Window& window) override;
    void Update(float dt) override;

    void TimeRemaining() override;
    void Decide() override;
    bool isReady() override;
};


#endif  // ACTION_H_