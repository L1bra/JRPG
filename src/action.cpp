#include "action.h"
#include <iostream>

PlayerAction::PlayerAction(Entity& entity, const std::array<Entity, MAX_ENTITIES>& entities)
    :
    //action_frame_texture(ResourceManager::loadTexture(Textures::ActionFrame, "src/res/background/action_frame.png")),
    cursor_texture(ResourceManager::loadTexture(Textures::Cursor, "src/res/background/cursor_white.png")),
    action_frame(sf::Vector2f(35.f, 40.f)),
    cursor_sprite(*cursor_texture),
    spawn_action_frame(false),
    is_ready(false),
    entity(entity),
    entities(entities),
    cursor_index(1)
{
    //action_frame.setScale({3.f, 3.f});
    //action_frame.setFillColor(sf::Color::White);
    //action_frame.setPosition(entity.m_Position);
}

PlayerAction::~PlayerAction() {}


void PlayerAction::Input(sf::Keyboard::Key key_code)
{
    // move cursor
    switch(key_code)
    {
        case sf::Keyboard::Up:
        {
            if(cursor_index < MAX_ENTITY_INDEX)
                cursor_index = (cursor_index + 1) % ENTITIES;
        } break;
        
        case sf::Keyboard::Down:
        {
            if(cursor_index >= 0)
                cursor_index = (cursor_index - 1) % ENTITIES;
        } break;

        case sf::Keyboard::Left:
        {
            //
        } break;

        case sf::Keyboard::Right:
        {
            //
        } break;

        case sf::Keyboard::Enter:
        {
            if(!spawn_action_frame)
                spawn_action_frame = true;
            else
                spawn_action_frame = false;            
        } break;
    }
}

void PlayerAction::Update(float dt)
{
    cursor_sprite.setPosition({ entities[cursor_index].m_Position.x + CURSOR_OFFSET, entities[cursor_index].m_Position.y });
    
    if(spawn_action_frame)
        action_frame.setPosition({ cursor_sprite.getPosition().x - CURSOR_OFFSET, cursor_sprite.getPosition().y });
}

void PlayerAction::Render(sf::RenderWindow& window)
{
    if(spawn_action_frame)
        window.draw(action_frame);
    window.draw(cursor_sprite);
}

void PlayerAction::TimeRemaining()
{
    //
}

void PlayerAction::Decide()
{
    //
}

bool PlayerAction::isReady()
{
    return is_ready;
}

void PlayerAction::init_cursor()
{
    cursor_sprite.setPosition(entity.m_Position);
}

void PlayerAction::init_gui()
{
    // cursor
    init_cursor();

    // action frame
    action_frame.setScale({ 3.f, 3.f });
    action_frame.setFillColor(sf::Color::White);
}




// AI




AIAction::AIAction(Entity& entity, const std::array<Entity, MAX_ENTITIES>& entities)
    :
    entity(entity),
    is_ready(true)
{
    //
}

AIAction::~AIAction() {}


void AIAction::Input(sf::Keyboard::Key key_code)
{
}


void AIAction::Update(float dt)
{
    // update
}


void AIAction::Render(sf::RenderWindow& window)
{
    
}

void AIAction::TimeRemaining()
{
    //
}

void AIAction::Decide()
{
    //
}

bool AIAction::isReady()
{
    return is_ready;
}
