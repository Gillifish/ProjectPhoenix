#pragma once

#include <iostream>
#include "Vec2.h"
#include <SFML/Graphics.hpp>

class Animation
{
    std::string m_name = "name";
    sf::Sprite m_sprite;
    size_t m_frameCount = 1;
    size_t m_currentFrame = 0;
    size_t m_speed = 0;
    Vec2 m_size = { 1, 1 };
    size_t m_gridColumns = 0;
    size_t m_gridRows = 0;
    size_t m_startRow = 0;

public:
    Animation();
    Animation(const std::string &name, const sf::Texture &t);
    Animation(const std::string &name, const sf::Texture &t, size_t frameCount, size_t speed);
    Animation(const std::string &name, const sf::Texture &t, size_t frameCount, size_t speed, size_t gridColumns, size_t gridRows, size_t startRow);

    void update();
    bool hasEnded() const;
    const std::string &getName() const;
    const Vec2 &getSize() const;
    sf::Sprite &getSprite();
};