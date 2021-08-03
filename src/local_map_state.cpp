#include "local_map_state.h"
#include "resource_manager.h"

// forcing myself to write comments so ...

LocalMapState::LocalMapState(GFX* gfx)
    :
    m_LocalMapTexture(ResourceManager::loadTexture(Textures::LocalBackground, "src/res/background/localmap_state.png")),
    m_LocalMapSprite(*m_LocalMapTexture),
    gfx_data(gfx),
    vm(gfx_data->resolution)
{
    // on enter stuff
}

LocalMapState::~LocalMapState() { /* destructor lmao */ }

void LocalMapState::OnEnter()
{
    m_LocalMapSprite.setScale(vm.width / m_LocalMapSprite.getLocalBounds().width,
                                vm.height / m_LocalMapSprite.getLocalBounds().height);
    init_party_entities();
}

void LocalMapState::OnExit() { /* on exit params */ }


void LocalMapState::Input()
{
    // switch(key_code)
    // {
    //     case sf::Keyboard::Escape:
    //     {    
    //         gameMode().Push("mainmenu");
    //     } break;

    //     case sf::Keyboard::M:
    //     {
    //         gameMode().Pop();   // to world state
    //     }
    // }

    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    // {   
    //     // entities[LocalMapState::PLAYER_INDEX].move(dir_state::RIGHT);
    // }
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    // {
    //     // entities[LocalMapState::PLAYER_INDEX].move(dir_state::LEFT);
    // }
    // else
    // {
    //     // entities[LocalMapState::PLAYER_INDEX].stop();
    // }
    
}

void LocalMapState::Update(float elapsedTime)   // spawn one enemy 
{
    (void)elapsedTime;
    // if(entities[LocalMapState::PLAYER_INDEX].get_position().x >= m_LocalMapSprite.getGlobalBounds().width)
    // {
    //     gameMode().Push("battle");
    // }

    // @TODO: FIX ME
    // for(auto& entity : entities)
    // {
    //     if((entities[LocalMapState::PLAYER_INDEX].m_Position.x - entities[LocalMapState::PLAYER_INDEX + 1].m_Position.x) > 40.f)
    //     {
    //         entities[LocalMapState::PLAYER_INDEX + 1].m_Sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
    //         entities[LocalMapState::PLAYER_INDEX + 2].m_Sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));

    //         entities[LocalMapState::PLAYER_INDEX + 1].m_Position.x += 400.f * elapsedTime;
    //         entities[LocalMapState::PLAYER_INDEX + 2].m_Position.x += 400.f * elapsedTime;
    //     }
    //     else if((entities[LocalMapState::PLAYER_INDEX].m_Position.x - entities[LocalMapState::PLAYER_INDEX + 2].m_Position.x) < -40.f)
    //     {
    //         entities[LocalMapState::PLAYER_INDEX + 1].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
    //         entities[LocalMapState::PLAYER_INDEX + 2].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));

    //         entities[LocalMapState::PLAYER_INDEX + 1].m_Position.x -= 400.f * elapsedTime;
    //         entities[LocalMapState::PLAYER_INDEX + 2].m_Position.x -= 400.f * elapsedTime;
    //     }

    //     entity.update(elapsedTime);
    // }

    // if(entities[LocalMapState::PLAYER_INDEX].get_position().x <= 0.f)
    // {
    //     gameMode().Pop();
    // }
}

void LocalMapState::Render(Window& window)
{
    window.draw(m_LocalMapSprite);

    // for(const auto& entity : entities)
    // {
    //     entity.draw(window);
    // }
}


void LocalMapState::init_party_entities()
{
    // entities[LocalMapState::PLAYER_INDEX + 0] = init_entity({gui::p2pX(2.f, vm), gui::p2pY(70.f, vm)}, "src/res/sprites/magic0.png", true);
    // entities[LocalMapState::PLAYER_INDEX + 1] = init_entity({gui::p2pX(4.f, vm), gui::p2pY(70.f, vm)}, "src/res/sprites/magic1.png", true);
    // entities[LocalMapState::PLAYER_INDEX + 2] = init_entity({gui::p2pX(6.f, vm), gui::p2pY(70.f, vm)}, "src/res/sprites/magic2.png", true);
}