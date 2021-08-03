#ifndef OBJECT_H_
#define OBJECT_H_

#include "component.h"
#include "c_transform.h"

#include <SFML/Graphics.hpp> // remove later

#include <vector>
#include <memory>


class Object
{
private:
    std::vector<std::shared_ptr<Component>> components;
public:
    std::shared_ptr<C_Transform> transform;
public:
    Object();
    void Awake();
    // Awake is called when object created.
    // Use to ensure required components are present.
    void Start();
    // Start is called after Awake.
    // Use to init variables.
    void Update(float dt);
    void LateUpdate(float dt);
    // TODO: replace with Window class
    void Draw(sf::RenderWindow& window);

    template<typename T> std::shared_ptr<T> AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for(auto& exist_component : components)
        {
            if(std::dynamic_pointer_cast<T>(exist_component))
            {
                return std::dynamic_pointer_cast<T>(exist_component);
            }
        }

        std::shared_ptr<T> new_component = std::make_shared<T>(this);
        components.push_back(new_component);

        return new_component;
    }

    template<typename T> std::shared_ptr<T> GetComponent()
    {
        for(auto& exist_component : components)
        {
            if(std::dynamic_pointer_cast<T>(exist_component))
            {
                return std::dynamic_pointer_cast<T>(exist_component);
            }
        }
        
        return nullptr;
    }

};


#endif  // OBJECT_H_