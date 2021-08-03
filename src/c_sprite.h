#ifndef C_SPRITE_H_
#define C_SPRITE_H_

#include "resource_manager.h"
#include "component.h"

class C_Sprite : public Component
{
public:
    C_Sprite(Object* owner);

    void Load(const std::string& path);
    void LateUpdate(float dt) override;
    void Draw(sf::RenderWindow& window) override; 
private:
    std::shared_ptr<sf::Texture> texture_ptr;
    sf::Sprite sprite;
};

#endif  // C_SPRITE_H_