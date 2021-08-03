#include "world_map_state.h"


WorldMapState::WorldMapState(GFX* gfx)
    :
    m_WorldMapTexture(ResourceManager::loadTexture(Textures::WorldBackground, "src/res/background/background0.png")),
    m_WorldMapSprite(*m_WorldMapTexture),
    gfx_data(gfx),
    vm(gfx_data->resolution)
{
#if DEBUG
    int s = *(&entities + 1) - entities;
    printf("size of entities: %d\n", s);
#endif
}

WorldMapState::~WorldMapState() {}


void WorldMapState::OnEnter()
{
    m_WorldMapSprite.setScale(vm.width / m_WorldMapSprite.getLocalBounds().width,
                                vm.height / m_WorldMapSprite.getLocalBounds().height);
    
    init_party_entity();
    spawn_enemy();
}


void WorldMapState::OnExit() { /* on exit */ }


void WorldMapState::Input()   // TODO: implement paravozik-style
{
    // switch(key_code)
    // {
    //     case sf::Keyboard::Escape:
    //     {    
    //         gameMode().Push("mainmenu");
    //     } break;
    // }

    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    // {   
    //     entities[WorldMapState::PLAYER_INDEX].move(dir_state::RIGHT);
    // }
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    // {
    //     entities[WorldMapState::PLAYER_INDEX].move(dir_state::LEFT);
    // }
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    // {
    //     entities[WorldMapState::PLAYER_INDEX].move(dir_state::UP);
    // }
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    // {
    //     entities[WorldMapState::PLAYER_INDEX].move(dir_state::DOWN);
    // }
    // else
    // {
    //     entities[WorldMapState::PLAYER_INDEX].stop();
    // }

    // Command* command = input.handle_input();
    // if(command)
    // {
    //     command->execute(entities[WorldMapState::PLAYER_INDEX]);
    // }
}


void WorldMapState::update_positions()
{
    // for(int i = MAX_PARTY_ENTITIES - 2; i >= 0; i--)
    // {
    //     entities[i + 1].dir = entities[i].dir;

    //     if(!entities[i].controllable)
    //     {
    //         if(entities[i].m_Position.x - entities[i + 1].m_Position.x != 40.f || entities[i].m_Position.y - entities[i + 1].m_Position.y != 40.f)
    //         {
    //             if(entities[i].dir.x > 0)
    //             {
    //                 entities[i].move(dir_state::RIGHT);
    //             }
    //             else if (entities[i].dir.x < 0)
    //             {
    //                 entities[i].move(dir_state::LEFT);
    //             }
    //             else if (entities[i].dir.y > 0)
    //             {
    //                 entities[i].move(dir_state::DOWN);
    //             }
    //             else if (entities[i].dir.y < 0)
    //             {
    //                 entities[i].move(dir_state::UP);
    //             }
    //             else
    //             {
    //                 entities[i].stop();
    //             }
    //         }
    //         else
    //         {
    //             entities[i].stop();
    //         }
            
    //     }
    // }
}

void WorldMapState::Update(float elapsedTime)
{
    (void)elapsedTime;
    // update_positions();

    // if(entities[WorldMapState::PLAYER_INDEX].m_Position.x >= m_WorldMapSprite.getGlobalBounds().width)
    // {
    //     gameMode().Push("localmap");
    // }

    // for(auto &entity : entities)
    // {
    //     entity.update(elapsedTime);
    // }

    // for(auto& enemy : enemies)  // TODO: FIX ME !
    // {
    //     if(entities[WorldMapState::PLAYER_INDEX].m_Sprite.getGlobalBounds().intersects(enemy.m_Sprite.getGlobalBounds()))
    //     {
    //         gameMode().Push("battle");
    //     }

    //     enemy.update(elapsedTime);
    // }
}


void WorldMapState::Render(Window& window)
{       
    window.draw(m_WorldMapSprite);

    // for(auto &entity : entities)
    // {
    //     entity.draw(window);
    // }

    // for(auto& enemy : enemies)  // FIXME !!!
    // {
    //     enemy.draw(window);
    // }
}


void WorldMapState::init_party_entity()
{
    // entities[WorldMapState::PLAYER_INDEX + 0] = init_entity({gui::p2pX(6.f, vm), gui::p2pY(70.f, vm)}, "src/res/sprites/magic0.png", true);
    // entities[WorldMapState::PLAYER_INDEX + 1] = init_entity({gui::p2pX(4.f, vm), gui::p2pY(70.f, vm)}, "src/res/sprites/magic1.png", false);    
    // entities[WorldMapState::PLAYER_INDEX + 2] = init_entity({gui::p2pX(2.f, vm), gui::p2pY(70.f, vm)}, "src/res/sprites/magic2.png", false);
}




void WorldMapState::spawn_enemy()
{
    // if(enemies.size() < 5)
    // {
    //     sf::Vector2f player_position = entities[WorldMapState::PLAYER_INDEX].get_position();
    //     sf::Vector2f enemy_position(0.f, 0.f);
    //     for(int i = 0; i < (WorldMapState::MAX_ENTITIES - 1); i++)
    //     {
    //         do
    //         {
    //             enemy_position.x = Random::float_range(0, vm.width);
    //             enemy_position.y = Random::float_range(0, vm.height);
    //         } while (enemy_position == player_position);
            
    //         float enemy_spawn_dir = Random::float_range(0, 3);

    //         // Entity enemy = init_entity(enemy_position, "src/res/sprites/enemy.png", false);
    //         enemies.push_back(std::move(enemy));
            
    //         switch((int)enemy_spawn_dir)
    //         {
    //             case 0:  entities[WorldMapState::ENEMY_OFFSET + i].m_Sprite.setTextureRect(sf::IntRect(0, 21, 24, 21)); break;
    //             case 1:  entities[WorldMapState::ENEMY_OFFSET + i].m_Sprite.setTextureRect(sf::IntRect(0, 0, 24, 24)); break;
    //             case 2:  entities[WorldMapState::ENEMY_OFFSET + i].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24)); break;
    //             case 3:  entities[WorldMapState::ENEMY_OFFSET + i].m_Sprite.setTextureRect(sf::IntRect(24, 21, 24, 21)); break;
    //         }
    //     }
    // }
}