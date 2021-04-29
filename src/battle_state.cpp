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

    for(auto& e : entities)
    {
        queue.enqueue(e);

        /*
            Default size of our custom Queue is 10, we have 3 entities on both sides 
            so it is quite enough for us.

            NOTE: change if entities in battle > 10
        */

        if(e.player_contolled)
        {
            PlayerAction* action = new PlayerAction(e, entities);
            m_Actions.push_back(action);
        }
        else
        {
            AIAction* action = new AIAction(e, entities);
            m_Actions.push_back(action);
        }
    }

    battleMode->Add("tick", new BattleTick(battleMode, m_Actions));
    battleMode->Add("execute", new BattleExecute(battleMode, m_Actions));
}

void BattleState::free_stuff()
{
    // dequeue
    std::size_t queue_size = queue.get_size();
    for(std::size_t i = 0; i < queue_size; i++)
    {
        queue.dequeue();
    }

    // // actions
    // for(auto& action : m_Actions)
    // {
    //     delete action;
    // }

    // // battle state machine
    // delete battleMode;
}

void BattleState::Input(sf::Keyboard::Key key_code)
{
    switch(key_code)
    {
        case sf::Keyboard::Escape:
        {    
            gameMode().Push("mainmenu");
        } break;
    }

    battleMode->Input(key_code);
}


// sleep

// #include <chrono>
// #include <thread>
// std::this_thread::sleep_for(std::chrono::milliseconds(x));

void BattleState::Update(float elapsedTime)
{
    for(auto& entity : entities)
    {
        entity.update(elapsedTime);
    }

    battleMode->Update(elapsedTime);
}

void BattleState::Render(sf::RenderWindow& window)
{
    window.draw(m_BattleSprite);
    
    for(auto& entity : entities)
    {
        entity.draw(window);
    }

    battleMode->Render(window);
}

void BattleState::init_party_entities()
{
    // BLUE
    entities[BattleState::PLAYER_INDEX + 0] = init_entity({gui::p2pX(70.f, vm), gui::p2pY(65.f, vm)}, "src/res/sprites/magic0.png", true);
    entities[BattleState::PLAYER_INDEX + 0].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
    
    // RED
    entities[BattleState::PLAYER_INDEX + 1] = init_entity({gui::p2pX(65.f, vm), gui::p2pY(60.f, vm)}, "src/res/sprites/magic1.png", true);
    entities[BattleState::PLAYER_INDEX + 1].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
    
    // YELLOW
    entities[BattleState::PLAYER_INDEX + 2] = init_entity({gui::p2pX(60.f, vm), gui::p2pY(55.f, vm)}, "src/res/sprites/magic2.png", true);
    entities[BattleState::PLAYER_INDEX + 2].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
}

void BattleState::init_enemy_entities()
{
    entities[BattleState::ENEMY_OFFSET + 0] = init_entity({gui::p2pX(40.f, vm), gui::p2pY(55.f, vm)}, "src/res/sprites/enemy.png");
    entities[BattleState::ENEMY_OFFSET + 1] = init_entity({gui::p2pX(35.f, vm), gui::p2pY(60.f, vm)}, "src/res/sprites/enemy.png");
    entities[BattleState::ENEMY_OFFSET + 2] = init_entity({gui::p2pX(30.f, vm), gui::p2pY(65.f, vm)}, "src/res/sprites/enemy.png");
}




//                 BATTLE TICK




BattleTick::BattleTick(StateMachine* battleMode, std::vector<Action*> battle_actions)
    :
    battleMode(battleMode),
    battle_actions(battle_actions),
    top_action(battle_actions.back())
{

}

BattleTick::~BattleTick() {}

void BattleTick::OnEnter() {}
void BattleTick::OnExit() {}


void BattleTick::Input(sf::Keyboard::Key key_code)
{
    if(top_action == nullptr)
        printf("top action == nullptr\n");
    top_action->Input(key_code);
}

void BattleTick::Update(float elapsedTime)
{
    // for(auto& action : battle_actions)
    // {
    //     action->Update(elapsedTime);
    // }

    top_action->Update(elapsedTime);

    // skip all enemies action (FIX THIS)
    if(top_action->isReady())
    {
        // TODO:
        delete battle_actions.back();
        battle_actions.pop_back();
        // battleMode->Push("execute"); // pass top action?
        top_action = battle_actions.back();
    }
}

void BattleTick::Render(sf::RenderWindow& window)
{
    top_action->Render(window);
}


// execute 

BattleExecute::BattleExecute(StateMachine* battleMode, std::vector<Action*> battle_actions)
{
    //
}

BattleExecute::~BattleExecute()
{
    //
}

void BattleExecute::OnEnter()
{
    //
}

void BattleExecute::OnExit() {}


void BattleExecute::Input(sf::Keyboard::Key key_code)
{
    //
}

void BattleExecute::Update(float elapsedTime)
{
    //
}

void BattleExecute::Render(sf::RenderWindow& window)
{
    //
}


//  battle menu state

BattleMenuState::BattleMenuState()
{
    //
}

BattleMenuState::~BattleMenuState()
{
    //
}

void BattleMenuState::OnEnter()
{
    //
}

void BattleMenuState::OnExit() {}


void BattleMenuState::Input(sf::Keyboard::Key key_code)
{
    //
}

void BattleMenuState::Update(float elapsedTime)
{
    //
}

void BattleMenuState::Render(sf::RenderWindow& window)
{
    //
}

// battle animation state

BattleAnimationState::BattleAnimationState()
{
    //
}

BattleAnimationState::~BattleAnimationState()
{
    //
}

void BattleAnimationState::OnEnter()
{
    //
}

void BattleAnimationState::OnExit() {}


void BattleAnimationState::Input(sf::Keyboard::Key key_code)
{
    //
}

void BattleAnimationState::Update(float elapsedTime)
{
    //
}

void BattleAnimationState::Render(sf::RenderWindow& window)
{
    //
}
