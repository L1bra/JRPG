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
    
    init_player_entity();
    spawn_enemy();
}


void WorldMapState::OnExit() { /* on exit */ }


void WorldMapState::Input(sf::Keyboard::Key key_code)   // TODO: implement paravozik-style
{
    switch(key_code)
    {
        case sf::Keyboard::Escape:
        {    
            gameMode().Push("mainmenu");
        } break;
    }
    
    //  real time input for smooth movement
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {   
        entities[WorldMapState::PLAYER_INDEX].move(sf::Keyboard::Right);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        entities[WorldMapState::PLAYER_INDEX].move(sf::Keyboard::Left);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        entities[WorldMapState::PLAYER_INDEX].move(sf::Keyboard::Up);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        entities[WorldMapState::PLAYER_INDEX].move(sf::Keyboard::Down);
    }
    else
    {
        entities[WorldMapState::PLAYER_INDEX].stop();
    }
}


void WorldMapState::Update(float elapsedTime)
{    
    if(entities[WorldMapState::PLAYER_INDEX].m_Position.x >= m_WorldMapSprite.getGlobalBounds().width)
    {
        gameMode().Push("localmap");
    }


    for(auto &entity : entities)
    {
        entity.update(elapsedTime);
    }

    for(auto& enemy : enemies)  // TODO: FIX ME !
    {
        if(entities[WorldMapState::PLAYER_INDEX].m_Sprite.getGlobalBounds().intersects(enemy.m_Sprite.getGlobalBounds()))
        {
            gameMode().Push("battle");
        }

        enemy.update(elapsedTime);
    }
}


void WorldMapState::Render(sf::RenderWindow& window)
{       
    window.draw(m_WorldMapSprite);

    for(auto &entity : entities)
    {
        entity.draw(window);
    }

    for(auto& enemy : enemies)  // FIXME !!!
    {
        enemy.draw(window);
    }
}


void WorldMapState::init_player_entity()
{
    entities[WorldMapState::PLAYER_INDEX] = init_entity({gui::p2pX(2.f, vm), gui::p2pY(70.f, vm)}, "src/res/sprites/magic0.png", true);
}


void WorldMapState::spawn_enemy()
{
    if(enemies.size() < 5)
    {
        sf::Vector2f player_position = entities[WorldMapState::PLAYER_INDEX].get_position();
        sf::Vector2f enemy_position(0.f, 0.f);
        for(int i = 0; i < (WorldMapState::MAX_ENTITIES - 1); i++)
        {
            do
            {
                enemy_position.x = Random::float_range(0, vm.width);
                enemy_position.y = Random::float_range(0, vm.height);
            } while (enemy_position == player_position);
            
            float enemy_spawn_dir = Random::float_range(0, 3);

            Entity enemy = init_entity(enemy_position, "src/res/sprites/enemy.png");
            enemies.push_back(std::move(enemy));
            
            switch((int)enemy_spawn_dir)
            {
                case 0:  entities[WorldMapState::ENEMY_OFFSET + i].m_Sprite.setTextureRect(sf::IntRect(0, 21, 24, 21)); break;
                case 1:  entities[WorldMapState::ENEMY_OFFSET + i].m_Sprite.setTextureRect(sf::IntRect(0, 0, 24, 24)); break;
                case 2:  entities[WorldMapState::ENEMY_OFFSET + i].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24)); break;
                case 3:  entities[WorldMapState::ENEMY_OFFSET + i].m_Sprite.setTextureRect(sf::IntRect(24, 21, 24, 21)); break;
            }
        }
    }
}




// move to battle state 
#if 0

void WorldMapState::kill_entity(Entity& entity)
{
    if(entity.m_State == Entity_state::Alive)
    {
        entity.m_State = Entity_state::Dead;
    }
}


void WorldMapState::damage_entity(Entity& entity, int amount)
{
    entity.hp -= amount;
    if(entity.hp <= 0)
    {
        kill_entity(entity);
    }
}



void WorldMapState::spawn_arrow(sf::Vector2f party_member_pos) // to battle state ?
{
    entities[ARROW_ENTITY_OFFSET] = init_entity(party_member_pos, "src/res/sprites/arrow.png");
}


void WorldMapState::move_arrow(sf::Keyboard::Key key_code)
{
    switch(key_code) 
    {
        case sf::Keyboard::Left:
        {
            sf::Vector2f current_arrow_pos = entities[ARROW_ENTITY_OFFSET].m_Position;
            switch(m_Choose_state)
            {
                case Choose_state::Friend:
                {
                    if(current_arrow_pos.x == entities[PLAYER_ENTITY_INDEX - 1].m_Position.x)
                    {
                        entities[ARROW_ENTITY_OFFSET].m_Position = {entities[PLAYER_ENTITY_INDEX - 2].m_Position.x, entities[PLAYER_ENTITY_INDEX - 2].m_Position.y - 40};
                    }
                    else if(current_arrow_pos.x == entities[PLAYER_ENTITY_INDEX - 0].m_Position.x)
                    {
                        entities[ARROW_ENTITY_OFFSET].m_Position = {entities[PLAYER_ENTITY_INDEX - 1].m_Position.x, entities[PLAYER_ENTITY_INDEX - 1].m_Position.y - 40};
                    }
                } break;

                case Choose_state::Enemy:
                {
                    if(current_arrow_pos.x == entities[ENEMY_ENTITY_OFFSET + 1].m_Position.x)
                    {
                        entities[ARROW_ENTITY_OFFSET].m_Position = {entities[ENEMY_ENTITY_OFFSET].m_Position.x, entities[ENEMY_ENTITY_OFFSET].m_Position.y - 40};
                    }
                } break;
            };
        } break;

        case sf::Keyboard::Right:
        {
            sf::Vector2f current_arrow_pos = entities[ARROW_ENTITY_OFFSET].m_Position;
            switch(m_Choose_state)
            {
                case Choose_state::Friend:
                {
                    if(current_arrow_pos.x == entities[PLAYER_ENTITY_INDEX - 2].m_Position.x)
                    {
                        entities[ARROW_ENTITY_OFFSET].m_Position = {entities[PLAYER_ENTITY_INDEX - 1].m_Position.x, entities[PLAYER_ENTITY_INDEX - 1].m_Position.y - 40};
                    }
                    else if(current_arrow_pos.x == entities[PLAYER_ENTITY_INDEX - 1].m_Position.x)
                    {
                        entities[ARROW_ENTITY_OFFSET].m_Position = {entities[PLAYER_ENTITY_INDEX].m_Position.x, entities[PLAYER_ENTITY_INDEX].m_Position.y - 40};
                    }
                } break;

                case Choose_state::Enemy:
                {
                    if(current_arrow_pos.x == entities[ENEMY_ENTITY_OFFSET].m_Position.x)
                    {
                        entities[ARROW_ENTITY_OFFSET].m_Position = {entities[ENEMY_ENTITY_OFFSET + 1].m_Position.x, entities[ENEMY_ENTITY_OFFSET + 1].m_Position.y - 40};
                    }
                } break;
            };
        } break;
    }
}

Entity WorldMapState::get_current_entity()
{
    sf::Vector2f arrow_pos = get_current_arrow_pos();
    for(size_t i = 0; i <= (ENEMY_ENTITY_OFFSET + 1); i++)
    {
        if(arrow_pos == entities[i].m_Position)
        {
            return entities[i];
        }
    }
}

sf::Vector2f WorldMapState::get_current_arrow_pos()
{
    return entities[ARROW_ENTITY_OFFSET].m_Position;
}

#endif