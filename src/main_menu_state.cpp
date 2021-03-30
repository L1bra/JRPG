#include "main_menu_state.h"

MainMenuState::MainMenuState()
    :
    m_MainMenuTexture(ResourceManager::loadTexture(Textures::MenuBackground, "src/res/background/menu_resume_state.png")),
    m_MenuCursorTexture(ResourceManager::loadTexture(Textures::MenuSettings, "src/res/background/menu_cursor.png")),
    m_Font(ResourceManager::loadFont(Fonts::Pixel, "src/res/fonts/PixelLettersFull.ttf")),
    BUTTON_OFFSET(16.f),
    isClosing(false)
{
}

MainMenuState::~MainMenuState() {}

void MainMenuState::TimeRemaining() {}
void MainMenuState::Decide() {}
bool MainMenuState::isReady() { return true; }; // ???


void MainMenuState::OnEnter()
{
    init_gui();
    reset_gui();
}


void MainMenuState::OnExit()
{
    free_buttons();
}


// resume = {690.f, 264.f};
// new_game = {618.f, 444.f};
// save_load = {564.f, 624.f};
// settings = {654.f, 804.f};
// exit = {834.f, 984.f};

void MainMenuState::init_gui()
{
    const sf::VideoMode& vm = sf::VideoMode::getDesktopMode();
    m_MainMenuSprite.setTexture(*m_MainMenuTexture);

    m_MenuCursorSprite.setTexture(*m_MenuCursorTexture);
    m_MenuCursorSprite.setTextureRect(sf::IntRect(0, 0, button_coord.new_game_cursor, 1));
    m_MenuCursorSprite.setScale(6.f, 6.f);                                                                    // scale to native
    m_MenuCursorSprite.setPosition({button_coord.new_game.x, button_coord.new_game.y + BUTTON_OFFSET});       // New game button coords

    m_MainMenuSprite.setScale(vm.width / m_MainMenuSprite.getLocalBounds().width, 
                            vm.height / m_MainMenuSprite.getLocalBounds().height);

    /*
        Resume (opt)
        New game
        save/load
        settings
        exit
    */

	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(15.6f, vm), gui::p2pY(30.f, vm), 
		gui::p2pX(0.f, vm), gui::p2pY(0.f, vm),
		*m_Font, "New Game", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void MainMenuState::reset_gui()
{
    free_buttons();
    init_gui();
}

void MainMenuState::update_buttons()
{
    //
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

        case sf::Keyboard::Up:  // TODO: "+ BUTTON_OFFSET" idea is awful 
        {
            if(m_MenuCursorSprite.getPosition().y == button_coord.new_game.y + BUTTON_OFFSET)
            {
                m_MenuCursorSprite.setPosition({button_coord.resume.x, button_coord.resume.y + BUTTON_OFFSET});
            }
            else if(m_MenuCursorSprite.getPosition().y == button_coord.save_load.y + BUTTON_OFFSET)
            {
                m_MenuCursorSprite.setPosition({button_coord.new_game.x, button_coord.new_game.y + BUTTON_OFFSET});
            }
            else if(m_MenuCursorSprite.getPosition().y == button_coord.settings.y + BUTTON_OFFSET)
            {
                m_MenuCursorSprite.setPosition({button_coord.save_load.x, button_coord.save_load.y + BUTTON_OFFSET});
            }
            else if(m_MenuCursorSprite.getPosition().y == button_coord.exit.y + BUTTON_OFFSET)
            {
                m_MenuCursorSprite.setPosition({button_coord.settings.x, button_coord.settings.y + BUTTON_OFFSET});
            }
        } break;
        
        case sf::Keyboard::Down:
        {
            if(m_MenuCursorSprite.getPosition().y == button_coord.resume.y + BUTTON_OFFSET)
            {
                m_MenuCursorSprite.setPosition({button_coord.new_game.x, button_coord.new_game.y + BUTTON_OFFSET});
            }
            else if(m_MenuCursorSprite.getPosition().y == button_coord.new_game.y + BUTTON_OFFSET)
            {
                m_MenuCursorSprite.setPosition({button_coord.save_load.x, button_coord.save_load.y + BUTTON_OFFSET});
            }
            else if(m_MenuCursorSprite.getPosition().y == button_coord.save_load.y + BUTTON_OFFSET)
            {
                m_MenuCursorSprite.setPosition({button_coord.settings.x, button_coord.settings.y + BUTTON_OFFSET});
            }
            else if(m_MenuCursorSprite.getPosition().y == button_coord.settings.y + BUTTON_OFFSET)
            {
                m_MenuCursorSprite.setPosition({button_coord.exit.x, button_coord.exit.y + BUTTON_OFFSET});
            }
        } break;
        
        case sf::Keyboard::Left:
        {
            //
        } break;

        case sf::Keyboard::Right:
        {
            //
        } break;

        case sf::Keyboard::Enter:   // TODO: add another buttons
        {
            if(m_MenuCursorSprite.getPosition().y == button_coord.resume.y + BUTTON_OFFSET)
            {
                // TODO: Hide resume button or print something like "there is no to resume u idiot..."
                if(gameMode().size() >= 2)
                    gameMode().Pop();   // to the last state
            }
            else if(m_MenuCursorSprite.getPosition().y == button_coord.new_game.y + BUTTON_OFFSET)
            {
                do
                {
                    gameMode().Pop();
                } while ( gameMode().size() != 0);

                gameMode().Push("worldmap");
            }
            else if(m_MenuCursorSprite.getPosition().y == button_coord.save_load.y + BUTTON_OFFSET)
            {
                // TODO: save/load
            }
            else if(m_MenuCursorSprite.getPosition().y == button_coord.settings.y + BUTTON_OFFSET)
            {
                // TODO: settings
            }
            else if(m_MenuCursorSprite.getPosition().y == button_coord.exit.y + BUTTON_OFFSET)
            {
                isClosing = true;
            }
        } break;

    }
}


void MainMenuState::Update(float elapsedTime)
{
    if(m_MenuCursorSprite.getPosition().y == button_coord.resume.y + BUTTON_OFFSET)
    {
        m_MenuCursorSprite.setTextureRect(sf::IntRect(0, 0, button_coord.resume_cursor, 1));
    }
    else if(m_MenuCursorSprite.getPosition().y == button_coord.new_game.y + BUTTON_OFFSET)
    {
        m_MenuCursorSprite.setTextureRect(sf::IntRect(0, 0, button_coord.new_game_cursor, 1));
    }
    else if(m_MenuCursorSprite.getPosition().y == button_coord.save_load.y + BUTTON_OFFSET)
    {
        m_MenuCursorSprite.setTextureRect(sf::IntRect(0, 0, button_coord.save_load_cursor, 1));
    }
    else if(m_MenuCursorSprite.getPosition().y == button_coord.settings.y + BUTTON_OFFSET)
    {
        m_MenuCursorSprite.setTextureRect(sf::IntRect(0, 0, button_coord.settings_cursor, 1));
    }
    else if(m_MenuCursorSprite.getPosition().y == button_coord.exit.y + BUTTON_OFFSET)
    {
        m_MenuCursorSprite.setTextureRect(sf::IntRect(0, 0, button_coord.exit_cursor, 1));
    }
}


void MainMenuState::Render(sf::RenderWindow& window)
{
    if(isClosing) // ???
        window.close();
        
    window.draw(m_MainMenuSprite);
    window.draw(m_MenuCursorSprite);
}

void MainMenuState::free_buttons()
{
    for(auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
    buttons.clear();
}