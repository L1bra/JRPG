#include "main_menu_state.h"

MainMenuState::MainMenuState(GFX* gfx)
    :
    m_Font(ResourceManager::loadFont(Fonts::Pixel, "src/res/fonts/PixellettersFull.ttf")),
    gfx_data(gfx),
    vm(gfx_data->resolution),
    // cursor_pos({0.f, 0.f}),
    cursor_index(0),
    enter_pressed(false),
    is_closing(false)
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

    cursor = std::make_shared<Object>();
    auto cursor_movement = cursor->AddComponent<C_KeyboardInput>();
    cursor_movement->set_input(&input);
}


void MainMenuState::OnExit()
{
}


void MainMenuState::Input()
{
    input.update();

    // if(input.is_key_down(InputHandler::Key::UP))
    // {
    //     printf("up pressed! (no)\n");
    //     cursor_index = (cursor_index - 1) % MAIN_MENU_ITEMS;
    // }

    // if(input.is_key_down(InputHandler::Key::DOWN))
    // {
    //     printf("down pressed! (no)\n");
    //     cursor_index = (cursor_index + 1) % MAIN_MENU_ITEMS;
    // }

//     if(input.is_key_down(InputHandler::Key::ENTER))
//     {
//         printf("enter pressed! (no)\n");
//         enter_pressed = true;
//         // enter_pressed = !enter_pressed;
//     }

//     if(input.is_key_down(InputHandler::Key::ESC))
//     {
//         printf("esc pressed! (no)\n");
//     }
}

// TODO: update buttons then update state
void MainMenuState::Update(float elapsedTime)
{
    cursor->Update(elapsedTime);
    cursor->LateUpdate(elapsedTime);

    update_buttons();
}


void MainMenuState::Render(Window& window)
{
    // if(is_closing)
    //     window.close();
        
    window.draw(m_Background);
    render_buttons(window);
}

// @BUG: scalable window
void MainMenuState::init_gui()
{
    m_Background.setSize({320.f, 180.f});
    m_Background.setScale(vm.width / m_Background.getLocalBounds().width, 
                    vm.height / m_Background.getLocalBounds().height);
    m_Background.setFillColor(sf::Color::Black);

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

void MainMenuState::update_buttons()
{
    switch(cursor->transform->get_index())
    {
        case BTN_MENU_PLAY:
        {
            cursor->transform->set_position(buttons["NEW_GAME"]->get_pos());
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
            cursor->transform->set_position(buttons["SAVE_LOAD"]->get_pos());
            if(enter_pressed)
            {
                //
                enter_pressed = false;
            }
        } break;

        case BTN_MENU_SETTINGS:
        {
            cursor->transform->set_position(buttons["SETTINGS"]->get_pos());
            if(enter_pressed)
            {
                //
                enter_pressed = false;
            }
        } break;

        case BTN_MENU_EXIT:
        {
            cursor->transform->set_position(buttons["EXIT"]->get_pos());
            if(enter_pressed)
            {
                is_closing = true;
                enter_pressed = false;
            }
        } break;

        default: {} break;
    }

    // printf("position after switch: %f %f\n", cursor->transform->get_position().x, cursor->transform->get_position().y);

    for(auto& it: buttons)
    {
        it.second->update(cursor->transform->get_position());
    }
}

void MainMenuState::render_buttons(Window& window)
{
    for(auto& it : buttons)
    {
        it.second->render(window);
    }
}

void MainMenuState::free_buttons()
{
    for(auto& it : buttons)
    {
        delete it.second;
    }
    buttons.clear();
}