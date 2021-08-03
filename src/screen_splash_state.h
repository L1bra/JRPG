#ifndef SCREEN_SPASH_H_
#define SCREEN_SPASH_H_

#include <SFML/Graphics.hpp>
#include "state_machine.h"
#include "gfx.h"

class ScreenSplash : public State
{
private:
    std::shared_ptr<sf::Texture> screen_texture;
    sf::Sprite screen_sprite;
    
    GFX* gfx_data;
    sf::VideoMode& vm;

    float show_for_seconds;
    float current_seconds;
public:
    ScreenSplash(GFX* gfx);
    ~ScreenSplash();

    void Input() override;
    void Update(float elapsedTime) override;
    void Render(Window& window) override;
    void OnEnter() override;
    void OnExit() override;
};


#endif  // SCREEN_SPASH_H_