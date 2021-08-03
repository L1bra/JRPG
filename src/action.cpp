#include "action.h"
#include <iostream>

PlayerAction::PlayerAction()
    :
    action_frame_texture(ResourceManager::loadTexture(Textures::ActionFrame, "src/res/background/action_frame.png")),
    action_frame_font(ResourceManager::loadFont(Fonts::Pixel, "src/res/fonts/PixellettersFull.ttf")),
    cursor_texture(ResourceManager::loadTexture(Textures::Cursor, "src/res/background/cursor_white.png")),
    // action_frame(sf::Vector2f(35.f, 40.f)),
    action_frame_sprite(*action_frame_texture),
    cursor_sprite(*cursor_texture),
    spawn_action_frame(false),
    entity(entity),
    // entities(entities),
    cursor_index(1)
{
    //action_frame.setScale({3.f, 3.f});
    //action_frame.setFillColor(sf::Color::White);
    //action_frame.setPosition(entity.m_Position);

    init_gui();
}

PlayerAction::~PlayerAction() {}


void PlayerAction::Input(sf::Keyboard::Key key_code)
{
    (void)key_code;
}

void PlayerAction::Update(float dt)
{
    (void)dt;
    update_buttons(cursor_pos);
}

void PlayerAction::Render(Window& window)
{
    if(spawn_action_frame)
    {
        window.draw(action_frame_sprite);
        render_buttons(window);
    }   

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
    // cursor_sprite.setPosition(entity.m_Position);
}

void PlayerAction::init_gui()
{
    // cursor
    init_cursor();

    // action frame
    action_frame_sprite.setScale({ 3.f, 3.f });
    sf::FloatRect fr = action_frame_sprite.getGlobalBounds();

    action_frame_buttons["ATTACK"] = new gui::Button(
        gui::p2pX(50.f, fr), gui::p2pY(10.f, fr),
        gui::p2pX(50.f, fr), gui::p2pY(50.f, fr),
        *action_frame_font, "Attack", gui::calcCharSize(fr)
    );

    action_frame_buttons["SPELL"] = new gui::Button(
        gui::p2pX(50.f, fr), gui::p2pY(20.f, fr),
        gui::p2pX(50.f, fr), gui::p2pY(50.f, fr),
        *action_frame_font, "Spell", gui::calcCharSize(fr)
    );

    action_frame_buttons["ITEM"] = new gui::Button(
        gui::p2pX(50.f, fr), gui::p2pY(30.f, fr),
        gui::p2pX(50.f, fr), gui::p2pY(50.f, fr),
        *action_frame_font, "Item", gui::calcCharSize(fr)
    );

    action_frame_buttons["DEF"] = new gui::Button(
        gui::p2pX(50.f, fr), gui::p2pY(40.f, fr),
        gui::p2pX(50.f, fr), gui::p2pY(50.f, fr),
        *action_frame_font, "Def", gui::calcCharSize(fr)
    );

    std::cout << "frame x: " << fr.width << " y: " << fr.height << "\n";

    std::cout << "ATTACK x: " << action_frame_buttons["ATTACK"]->get_pos().x << " y: " << action_frame_buttons["ATTACK"]->get_pos().y << "\n";
    std::cout << "SPELL x: " << action_frame_buttons["SPELL"]->get_pos().x << " y: " << action_frame_buttons["ATTACK"]->get_pos().y << "\n";
    std::cout << "ITEM x: " << action_frame_buttons["ITEM"]->get_pos().x << " y: " << action_frame_buttons["ATTACK"]->get_pos().y << "\n";
    std::cout << "DEF x: " << action_frame_buttons["DEF"]->get_pos().x << " y: " << action_frame_buttons["ATTACK"]->get_pos().y << "\n";
}

void PlayerAction::update_buttons(sf::Vector2f pos)
{
    for(auto& it : action_frame_buttons)
    {
        it.second->update(pos);
    }
}

void PlayerAction::render_buttons(Window& window)
{
    for(auto& it : action_frame_buttons)
    {
        it.second->render(window);
    }
}

void PlayerAction::free_buttons()
{
    for(auto& button : action_frame_buttons)
    {
        delete button.second;
    }

    action_frame_buttons.clear();
}


// AI




AIAction::AIAction()
    :
    entity(entity),
    is_ready(true)
{
    // (void)entities;
    //
}

AIAction::~AIAction() {}


void AIAction::Input(sf::Keyboard::Key key_code)
{
    (void)key_code;
}


void AIAction::Update(float dt)
{
    (void)dt;
    // update
}


void AIAction::Render(Window& window)
{
    (void)window;
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
