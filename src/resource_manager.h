#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>  // unordered ?
#include <assert.h>

template<typename Resource, typename Identifier>
class ResourceManager
{
private:
    std::map<Identifier, std::unique_ptr<Resource>> m_resource_map;
public:
    void load(Identifier id, const std::string& filename);

    // sf::Shader 
    template<typename Parameter>
    void load(Identifier id, const std::string& filename, const Parameter& parameter);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;
};


template<typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceManager::load - Failed to load: " + filename);

    auto inserted = m_resource_map.insert(std::make_pair(id, std::move(resource)));
    // TODO;
    //assert(inserted.second);
}

template<typename Resource, typename Identifier>
template<typename Parameter>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& parameter)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, parameter))
        throw std::runtime_error("ResourceManager::load - Failed to load: " + filename);

    auto inserted = m_resource_map.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template<typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
    auto found = m_resource_map.find(id);
    //assert(found != m_resource_map.end());

    return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
    auto found = m_resource_map.find(id);
    assert(found != m_resource_map.end());

    return *found->second;
}