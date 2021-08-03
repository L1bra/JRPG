#include "object.h"

Object::Object()
{
    transform = AddComponent<C_Transform>();
}

void Object::Awake()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Awake();
    }
}

void Object::Start()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Start();
    }
}

void Object::Update(float dt)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Update(dt);
    }
}

void Object::LateUpdate(float dt)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->LateUpdate(dt);
    }
}


void Object::Draw(sf::RenderWindow& window)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Draw(window);
    }
}