#ifndef MAIN_MENU_STATE_H_
#define MAIN_MENU_STATE_H_

#include "state_machine.h"
#include "gui.h"
#include "gfx.h"
#include "input.h"

const uint8_t MAIN_MENU_ITEMS = 4;

class MainMenuState : public State
{
private:
    enum BTN_MENU { BTN_MENU_PLAY = 0, BTN_MENU_SAVE, BTN_MENU_SETTINGS, BTN_MENU_EXIT };

    sf::RectangleShape m_Background;
    std::shared_ptr<sf::Font> m_Font;

    GFX* gfx_data;
    sf::VideoMode& vm;
    InputHandler input;

    std::map<std::string, gui::Button*> buttons;
    
    sf::Vector2f cursor_pos;
    unsigned int cursor_index;

    bool enter_pressed;
    bool is_closing;
private:
    void init_gui();
    void reset_gui();

    void update_buttons(sf::Vector2f pos);
    void render_buttons(sf::RenderWindow& window);
    void free_buttons();
    
public:
    MainMenuState(GFX* gfx);
    ~MainMenuState();

    void Input() override;
    void Update(float elapsedTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnEnter() override;
    void OnExit() override;
};

#endif  // MAIN_MENU_STATE_H_