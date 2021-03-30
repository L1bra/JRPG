#include "battle_state.h"

void free_state(void* ptr)
{
    delete ptr;
}

typedef struct 
{
    sf::Vector2f blue = {1300.f, 700.f};
    sf::Vector2f red = {1250.f, 650.f};
    sf::Vector2f yellow = {1200.f, 600.f};
} party_coord_t;

party_coord_t party_coord = {};

// FIX WHAT ABOVE


BattleState::BattleState()
    :
    m_BattleTexture(ResourceManager::loadTexture(Textures::BattleBackground, "src/res/background/battle_state.png")),
    battleMode(new StateMachine()),
    battle_tick(new BattleTick(battleMode)),
    battle_execute(new BattleExecute(battleMode))
{
    m_BattleSprite.setTexture(*m_BattleTexture);

    sf::Vector2f targetSize(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    m_BattleSprite.setScale(targetSize.x / m_BattleSprite.getLocalBounds().width,
                                targetSize.y / m_BattleSprite.getLocalBounds().height);

    battleMode->Add("tick", battle_tick);
    battleMode->Add("execute", battle_execute);

    init_party_entities();
    init_enemy_entities();
}

BattleState::~BattleState() 
{
    delete battle_tick;
    delete battle_execute;
    delete battleMode;    
}

void BattleState::OnEnter()
{
    static_assert(sizeof(battleMode->size()), "[Battle state]: sm size is zero");
    // battleMode->Push("tick");

}

void BattleState::OnExit()
{
    while(battleMode->size() != 0)
    {
        battleMode->Pop();
    }
}

void BattleState::Input(sf::Keyboard::Key key_code)
{
    // TODO: local pass input to local sm
    switch(key_code)
    {
        case sf::Keyboard::Escape:
        {    
            gameMode().Push("mainmenu");
        } break;

        case sf::Keyboard::Enter:
        {
            battleMode->Push("tick");
        } break;
    }
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

    // draw action
    battleMode->Render(window);
}

void BattleState::init_party_entities()
{
    entities[PLAYER_ENTITY_INDEX - 2] = init_entity(party_coord.blue, "src/res/sprites/magic0.png");
    entities[PLAYER_ENTITY_INDEX - 2].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
    
    entities[PLAYER_ENTITY_INDEX - 1] = init_entity(party_coord.red, "src/res/sprites/magic1.png");
    entities[PLAYER_ENTITY_INDEX - 1].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
    
    entities[PLAYER_ENTITY_INDEX - 0] = init_entity(party_coord.yellow, "src/res/sprites/magic2.png");
    entities[PLAYER_ENTITY_INDEX - 0].m_Sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
}

void BattleState::init_enemy_entities()
{
    entities[PLAYER_ENTITY_INDEX + 1] = init_entity({(party_coord.blue.y - 300), party_coord.blue.y}, "src/res/sprites/enemy.png");
    entities[PLAYER_ENTITY_INDEX + 2] = init_entity({(party_coord.red.y - 200), party_coord.red.y}, "src/res/sprites/enemy.png");
    entities[PLAYER_ENTITY_INDEX + 3] = init_entity({(party_coord.yellow.y - 100), party_coord.yellow.y}, "src/res/sprites/enemy.png");
}

void BattleState::TimeRemaining() {}
void BattleState::Decide() {}
bool BattleState::isReady() { return true; } // ???


// tick

BattleTick::BattleTick(StateMachine* bm)
    :
    m_ActionFrameTexture(ResourceManager::loadTexture(Textures::ActionFrame, "src/res/background/action_frame.png")),
    m_ActionFrameSprite(*m_ActionFrameTexture),
    battleMode(battleMode)
{
    // scale action frame and set default position
    // TODO: replace numbers 
    m_ActionFrameSprite.setScale({3.f, 3.f});
    m_ActionFrameSprite.setPosition({1340.f, 600.f});
}

BattleTick::~BattleTick() {}

void BattleTick::OnEnter() {}
void BattleTick::OnExit() {}

void BattleTick::TimeRemaining() {}
void BattleTick::Decide() {}
bool BattleTick::isReady() { return true; } // ???


void BattleTick::Input(sf::Keyboard::Key key_code)
{
    // move cursor
    switch(key_code)
    {
        case sf::Keyboard::Up:
        {
            
        } break;
        
        case sf::Keyboard::Down:
        {
            
        } break;

        case sf::Keyboard::Left:
        {
            
        } break;

        case sf::Keyboard::Right:
        {
            
        } break;

        case sf::Keyboard::Escape:
        {
            battleMode->Pop();
        } break;
    }
}

void BattleTick::Update(float elapsedTime)
{
    //
}

void BattleTick::Render(sf::RenderWindow& window)
{
    window.draw(m_ActionFrameSprite);
}


// execute 

BattleExecute::BattleExecute(StateMachine* bm)
    :
    battleMode(bm)
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

void BattleExecute::TimeRemaining() {}
void BattleExecute::Decide() {}
bool BattleExecute::isReady() { return true; } // ???


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
