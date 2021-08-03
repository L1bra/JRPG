#include "battle_state.h"

BattleState::BattleState(GFX* gfx)
    :
    m_BattleTexture(ResourceManager::loadTexture(Textures::BattleBackground, "src/res/background/battle_state.png")),
    m_BattleSprite(*m_BattleTexture),
    battleMode(new StateMachine()),
    gfx_data(gfx),
    vm(gfx_data->resolution)
{
    m_BattleSprite.setScale(vm.width / m_BattleSprite.getLocalBounds().width,
                                vm.height / m_BattleSprite.getLocalBounds().height);

    BLUE_SPAWN_POSITION = {gui::p2pX(68.f, vm), gui::p2pY(65.f, vm)};
    RED_SPAWN_POSITION = {gui::p2pX(65.f, vm), gui::p2pY(60.f, vm)};
    YELLOW_SPAWN_POSITION = {gui::p2pX(63.f, vm), gui::p2pY(56.f, vm)};
}

BattleState::~BattleState() 
{

}

void BattleState::OnEnter()
{
    battle_init();

    battleMode->Push("tick");
}

void BattleState::OnExit()
{
    free_stuff();
}

void BattleState::battle_init()
{
    init_party_entities();
    init_enemy_entities();

    // for(auto& e : entities)
    // {
    //     queue.enqueue(e);

    //     /*
    //         Default size of our custom Queue is 10, we have 3 entities on both sides 
    //         so it is quite enough for us.

    //         NOTE: change if entities in battle > 10
    //     */

    //     if(e.controllable)
    //     {
    //         PlayerAction* action = new PlayerAction(e, entities);
    //         m_Actions.push_back(action);
    //     }
    //     else
    //     {
    //         AIAction* action = new AIAction(e, entities);
    //         m_Actions.push_back(action);
    //     }
    // }
}

void BattleState::free_stuff()
{
    // dequeue
    // // std::size_t queue_size = queue.get_size();
    // for(std::size_t i = 0; i < queue_size; i++)
    // {
    //     queue.dequeue();
    // }

    // // actions
    // for(auto& action : m_Actions)
    // {
    //     delete action;
    // }

    // // battle state machine
    // delete battleMode;
}

void BattleState::Input()
{
    // switch(key_code)
    // {
    //     case sf::Keyboard::Escape:
    //     {    
    //         gameMode().Push("mainmenu");
    //     } break;
    // }

    battleMode->Input();
}


// sleep

// #include <chrono>
// #include <thread>
// std::this_thread::sleep_for(std::chrono::milliseconds(x));

void BattleState::Update(float elapsedTime)
{
    // for(auto& entity : entities)
    // {
    //     entity.update(elapsedTime);
    // }

    battleMode->Update(elapsedTime);
}

void BattleState::Render(Window& window)
{
    window.draw(m_BattleSprite);
    
    // for(auto& entity : entities)
    // {
    //     entity.draw(window);
    // }

    battleMode->Render(window);
}

void BattleState::init_party_entities()
{
    // // BLUE
    // entities[BattleState::PLAYER_INDEX + 0] = init_entity({gui::p2pX(70.f, vm), gui::p2pY(65.f, vm)}, "src/res/sprites/magic0.png", true);
    // entities[BattleState::PLAYER_INDEX + 0].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
    
    // // RED
    // entities[BattleState::PLAYER_INDEX + 1] = init_entity({gui::p2pX(65.f, vm), gui::p2pY(60.f, vm)}, "src/res/sprites/magic1.png", true);
    // entities[BattleState::PLAYER_INDEX + 1].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
    
    // // YELLOW
    // entities[BattleState::PLAYER_INDEX + 2] = init_entity({gui::p2pX(60.f, vm), gui::p2pY(55.f, vm)}, "src/res/sprites/magic2.png", true);
    // entities[BattleState::PLAYER_INDEX + 2].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
}

void BattleState::init_enemy_entities()
{
    // entities[BattleState::ENEMY_OFFSET + 0] = init_entity({gui::p2pX(40.f, vm), gui::p2pY(55.f, vm)}, "src/res/sprites/enemy.png");
    // entities[BattleState::ENEMY_OFFSET + 1] = init_entity({gui::p2pX(35.f, vm), gui::p2pY(60.f, vm)}, "src/res/sprites/enemy.png");
    // entities[BattleState::ENEMY_OFFSET + 2] = init_entity({gui::p2pX(30.f, vm), gui::p2pY(65.f, vm)}, "src/res/sprites/enemy.png");
}