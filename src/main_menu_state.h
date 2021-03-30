#ifndef MAIN_MENU_STATE_H_
#define MAIN_MENU_STATE_H_

#include "state_machine.h"
#include "gui.h"


// TODO: move to src file
struct button
{
    sf::Vector2f resume = {690.f, 264.f};
    float resume_cursor = 90.f;

    sf::Vector2f new_game = {618.f, 444.f};
    float new_game_cursor = 114.f;

    sf::Vector2f save_load = {564.f, 624.f};
    float save_load_cursor = 129.f;

    sf::Vector2f settings = {654.f, 804.f};
    float settings_cursor = 102.f;
    
    sf::Vector2f exit = {834.f, 984.f};
    float exit_cursor = 42.f;
};


class MainMenuState : public State
{
private:
    void init_gui();
    void reset_gui();

    void update_buttons();
    void render_buttons(sf::RenderWindow& window);
    void free_buttons();
    
public:
    MainMenuState();
    ~MainMenuState();

    void Input(sf::Keyboard::Key key_code);
    void Update(float elapsedTime);
    void Render(sf::RenderWindow& window);
    void OnEnter();
    void OnExit();

    void TimeRemaining();
    void Decide();
    bool isReady();

private:
    std::shared_ptr<sf::Texture> m_MainMenuTexture;
    sf::Sprite m_MainMenuSprite;

    std::shared_ptr<sf::Texture> m_MenuCursorTexture;
    sf::Sprite m_MenuCursorSprite;

    std::shared_ptr<sf::Font> m_Font;

    std::map<std::string, gui::Button*> buttons;

    button button_coord;
    const float BUTTON_OFFSET;

    bool isClosing;
};

#endif  // MAIN_MENU_STATE_H_