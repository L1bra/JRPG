#include "screen_splash_state.h"

ScreenSplash::ScreenSplash(GFX* gfx)
    :
    screen_texture(ResourceManager::loadTexture(Textures::LoadingScreen, "src/res/background/loading_screen.png")),
    screen_sprite(*screen_texture),
    gfx_data(gfx),
    vm(gfx_data->resolution),
    show_for_seconds(3.f),
    current_seconds(0.f)
{
}

ScreenSplash::~ScreenSplash()
{

}

void ScreenSplash::OnEnter()
{
    screen_sprite.setScale(vm.width / screen_sprite.getLocalBounds().width,
                                vm.height / screen_sprite.getLocalBounds().height);

    current_seconds = 0.f;
}

void ScreenSplash::OnExit()
{
}

void ScreenSplash::Input()
{

}

void ScreenSplash::Update(float elapsedTime)
{
    current_seconds += elapsedTime;
    if(current_seconds >= show_for_seconds)
    {
        gameMode().Push("mainmenu");
    }
}

void ScreenSplash::Render(Window& window)
{
    window.draw(screen_sprite);
}