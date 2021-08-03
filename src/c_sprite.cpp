#include "c_sprite.h"
#include "object.h"

C_Sprite::C_Sprite(Object* owner)
    :
    Component(owner)
{
}

void C_Sprite::Load(const std::string& path)
{
    texture_ptr = ResourceManager::loadTexture(Textures::Sprite, path);
    sprite.setTexture(*texture_ptr);
}

void C_Sprite::LateUpdate(float dt)
{
    sprite.setPosition(owner->transform->get_position());
}

void C_Sprite::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}