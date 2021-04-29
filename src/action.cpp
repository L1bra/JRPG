#include "action.h"
#include <iostream>

PlayerAction::PlayerAction(Entity& entity, const std::array<Entity, MAX_ENTITIES> entities)
    :
    action_frame_texture(ResourceManager::loadTexture(Textures::ActionFrame, "src/res/background/action_frame.png")),
    cursor_texture(ResourceManager::loadTexture(Textures::Cursor, "src/res/background/cursor.png")),
    action_frame_sprite(*action_frame_texture),
    cursor_sprite(*cursor_texture),
    spawn_action_frame(false),
    is_ready(false),
    entity(entity),
    entities(entities),
    cursor_index(1)
{
    action_frame_sprite.setScale({3.f, 3.f});
    action_frame_sprite.setPosition(entity.m_Position);

    cursor_init();
}

PlayerAction::~PlayerAction() {}


void PlayerAction::Input(sf::Keyboard::Key key_code)
{
    // move cursor
    switch(key_code)
    {
        case sf::Keyboard::Up:
        {
            if(cursor_index >= 0)
                cursor_index = (cursor_index - 1) % ENTITIES;
        } break;
        
        case sf::Keyboard::Down:
        {
            if(cursor_index <= ENTITIES)
                cursor_index = (cursor_index + 1) % ENTITIES;
        } break;

        case sf::Keyboard::Left:
        {
            
        } break;

        case sf::Keyboard::Right:
        {
            
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
    cursor_sprite.setPosition(entities[cursor_index].m_Position);
}

void PlayerAction::Render(sf::RenderWindow& window)
{
    if(spawn_action_frame)
        window.draw(action_frame_sprite);
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

void PlayerAction::cursor_init()
{
    cursor_sprite.setPosition(entity.m_Position);
}




// AI




AIAction::AIAction(Entity& entity, const std::array<Entity, MAX_ENTITIES> entities)
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
