#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <deque>
#include <cassert>

using SpriteID = size_t;

class SpriteManager
{
    public:
        SpriteManager() = default;

        SpriteManager(const SpriteManager&) = delete;
        SpriteManager& operator=(const SpriteManager&) = delete;

        SpriteManager(SpriteManager&&) = default;
        SpriteManager& operator=(SpriteManager&&) = default;

        sf::Texture& registerTexture(const std::string& filepath)
        {
            return textureMap.try_emplace(filepath, filepath).first->second;
        }
        
        template <typename... Args>
        SpriteID createSprite(Args&&... args)
        {
            spriteList.emplace_back(std::forward<Args>(args)...);
            return spriteList.size()-1;
        }

        Sprite& getSprite(SpriteID id)
        {
            assert(id <spriteList.size());
            return spriteList[id];
        }
 
        const Sprite& getSprite(SpriteID id) const
        {
            assert(id < spriteList.size());
            return spriteList[id];
        }
    private:
        std::unordered_map<std::string, sf::Texture> textureMap;

        //used this as reference:
        //https://www.geeksforgeeks.org/cpp/deque-cpp-stl/
        std::deque<Sprite> spriteList;
};

#endif  // SPRITE_MANAGER_H
