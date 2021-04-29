#include "main_menu_state.h"

MainMenuState::MainMenuState(GFX* gfx)
    :
    m_MainMenuTexture(ResourceManager::loadTexture(Textures::MenuBackground, "src/res/background/menu_resume_state.png")),
    m_Font(ResourceManager::loadFont(Fonts::Arial, "src/res/fonts/PixellettersFull.ttf")),
    m_MainMenuSprite(*m_MainMenuTexture),
    cursor_pos({0.f, 0.f}),
    enter_pressed(false),
    is_closing(false),
    cursor_index(0),
    gfx_data(gfx),
    vm(gfx_data->resolution)
{
}

MainMenuState::~MainMenuState()
{
    free_buttons();
}

void MainMenuState::OnEnter()
{
    init_gui();
    reset_gui();
}


void MainMenuState::OnExit()
{
}

// @BUG: scalable window
void MainMenuState::init_gui()
{    
    m_MainMenuSprite.setScale(vm.width / m_MainMenuSprite.getLocalBounds().width, 
                            vm.height / m_MainMenuSprite.getLocalBounds().height);

    /*
        Resume (opt)
        New game
        save/load
        settings
        exit
    */

    buttons["NEW_GAME"] = new gui::Button(
        gui::p2pX(50.f, vm), gui::p2pY(40.f, vm),
        gui::p2pX(50.f, vm), gui::p2pY(40.f, vm),
        *m_Font, "New Game", gui::calcCharSize(vm)
    );

    buttons["SAVE_LOAD"] = new gui::Button(
        gui::p2pX(50.f, vm), gui::p2pY(50.f, vm),
        gui::p2pX(50.f, vm), gui::p2pY(40.f, vm),
        *m_Font, "Save/Load", gui::calcCharSize(vm)
    );

    buttons["SETTINGS"] = new gui::Button(
        gui::p2pX(50.f, vm), gui::p2pY(60.f, vm),
        gui::p2pX(50.f, vm), gui::p2pY(40.f, vm),
        *m_Font, "Settings", gui::calcCharSize(vm)
    );

    buttons["EXIT"] = new gui::Button(
        gui::p2pX(50.f, vm), gui::p2pY(70.f, vm),
        gui::p2pX(50.f, vm), gui::p2pY(40.f, vm),
        *m_Font, "Exit", gui::calcCharSize(vm)
    );
}

void MainMenuState::reset_gui()
{
    free_buttons();
    init_gui();
}

void MainMenuState::update_buttons(sf::Vector2f pos)
{
    for(auto& it: buttons)
    {
        it.second->update(pos);
    }
}

void MainMenuState::render_buttons(sf::RenderWindow& window)
{
    for(auto& it : buttons)
    {
        it.second->render(window);
    }
}


void MainMenuState::Input(sf::Keyboard::Key key_code)
{
    switch(key_code)
    {
        case sf::Keyboard::Escape:
        {
            if(gameMode().size() >= 2)
                gameMode().Pop();   // to the last state
        } break;

        case sf::Keyboard::Up:
        {
            if(cursor_index >= 0)
                cursor_index = (cursor_index - 1) % MAIN_MENU_ITEMS;
        } break;
        
        case sf::Keyboard::Down:
        {
            if(cursor_index <= MAIN_MENU_ITEMS)
                cursor_index = (cursor_index + 1) % MAIN_MENU_ITEMS;
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
            enter_pressed = true;
        } break;
    }
}

// TODO: update buttons then update state
void MainMenuState::Update(float elapsedTime)
{
    switch(cursor_index)
    {
        case BTN_MENU_PLAY:
        {
            cursor_pos = buttons["NEW_GAME"]->get_pos();
            if(enter_pressed)
            {                
                do
                {
                    gameMode().Pop();
                } while (gameMode().size() != 0);
                
                enter_pressed = false;

                gameMode().Push("worldmap");
            }
        } break;

        case BTN_MENU_SAVE:
        {
            cursor_pos = buttons["SAVE_LOAD"]->get_pos();
            if(enter_pressed)
            {
                //
                enter_pressed = false;
            }
        } break;

        case BTN_MENU_SETTINGS:
        {
            cursor_pos = buttons["SETTINGS"]->get_pos();
            if(enter_pressed)
            {
                //
                enter_pressed = false;
            }
        } break;

        case BTN_MENU_EXIT:
        {
            cursor_pos = buttons["EXIT"]->get_pos();
            if(enter_pressed)
            {
                is_closing = true;
                enter_pressed = false;
            }
        } break;

        default: {} break;
    }

    update_buttons(cursor_pos);
}


void MainMenuState::Render(sf::RenderWindow& window)
{
    if(is_closing)
        window.close();
        
    window.draw(m_MainMenuSprite);
    render_buttons(window);
}

void MainMenuState::free_buttons()
{
    for(auto& it : buttons)
    {
        delete it.second;
    }
    buttons.clear();
}