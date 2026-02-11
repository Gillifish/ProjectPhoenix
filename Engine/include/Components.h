#pragma once

#include "Vec2.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

// NOTE: All components need to be added to the entity header in order to use

// Base class for all components
// All components must inherit this class
class Component
{
public:
    bool has = false;
};

// Transform component; includes positioning and movement
class CTransform : public Component
{
public:
    Vec2 pos = {0.0, 0.0};
    Vec2 gridPos = {0, 0};
    Vec2 prevPos = {0.0, 0.0};
    Vec2 scale = {1.0, 1.0};
    Vec2 velocity = {0.0, 0.0};
    float angle = 0;

    CTransform() {}
    CTransform(const Vec2 &p) : pos(p) {}
    CTransform(const Vec2 &p, const Vec2 &v, float a)
        : pos(p), velocity(v), angle(a) {}
};

// Shape component; currently can only create a circle shape, will update so other SFML shapes
class CShape : public Component
{
public:
    sf::CircleShape circle;

    CShape() {}
    CShape(float radius, int points, const sf::Color &fill,
           const sf::Color &outline, float thickness)
        : circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

// Collision component; might need to update to take more than just a radius; 
// possibly dependant on having transform component?
class CCollision : public Component
{
public:
    float radius = 0;
    CCollision() {}
    CCollision(float r)
        : radius(r) {}
};

// Score component; renders given integer to the screen; may need to expand this
class CScore : Component
{
public:
    int score = 0;
    CScore() {}
    CScore(int s)
        : score(s) {}
};

class CLifespan : public Component
{
public:
    int remaining = 0;
    int total = 0;
    CLifespan() {}
    CLifespan(int total)
        : remaining(total), total(total) {}
};

// Input component; seems ok for current implementation
class CInput : public Component
{
public:
    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool isMoving = false;

    CInput() {}
};

// Bounding Box component; might be a better alternative to the collision component
// Considering moving collision component into this one
class CBoundingBox : public Component
{
public:
    Vec2 size = { 0.0, 0.0 };
    Vec2 halfSize = { 0.0, 0.0 };
    sf::RectangleShape rect;
    bool active = false;

    CBoundingBox() {}
    CBoundingBox(const Vec2 &s)
        : size(s), halfSize(s.x / 2, s.y / 2) 
        {
            rect.setSize(sf::Vector2f(size.x, size.y));
            rect.setOrigin(size.x / 2, size.y / 2);
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color(255, 255, 255));
            rect.setOutlineThickness(1);
        }
};

// Animation component; seems ok for now
class CAnimation : public Component
{
public:
    Animation animation;
    bool repeat = false;
    CAnimation() {}
    CAnimation(const Animation &animation) : animation(animation) {}
    CAnimation(const Animation &animation, bool r)
        : animation(animation), repeat(r) {}
};

// Gravity component; seems ok for now
class CGravity : public Component
{
public:
    float gravity = 0;
    CGravity() {}
    CGravity(float g) : gravity(g) {}
};

// State component; seems ok for now
class CState : public Component
{
public:
    std::string state = "none";
    std::string previousState = "none";

    CState() {}
    CState(const std::string &s) : state(s) {}
};

// Text component; seems ok for now
class CText : public Component
{
public:
    sf::Text text;
    float width = 0.0f;
    float height = 0.0f;

    CText() {}
    CText(const std::string &content, sf::Font &font, const sf::Color &fill, int size)
    {
        text.setString(content);
        text.setFont(font);
        text.setFillColor(fill);
        text.setCharacterSize(size);

        width = text.getLocalBounds().width;
        height = text.getLocalBounds().height;
    }
};

// Sprite component; seems ok for now
class CSprite : public Component
{
public:
    sf::Sprite sprite;

    CSprite() {}
};

// Direction enum for the direction component
enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// 2D dirction component; seems ok for now
class CDirection2D : public Component
{
public:
    Direction direction;

    CDirection2D() {}
    CDirection2D(Direction d) : direction(d) {}
};