#pragma once

#include "EntityManager.h"
#include "Scene.h"
#include "GameEngine.h"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

class Editor : public Scene
{
    std::string m_levelPath;
    std::shared_ptr<Entity> m_player;

    void init(const std::string &levelPath);

    void sAnimation();
    void sMovement();
    void sLifespan();
    void sCollision();
    void sRender();
    void sDoAction(const Action &action);
    void sDebug();
    void onEnd();

public:
    Editor(GameEngine *gameEngine);
    Editor(GameEngine *gameEngine, const std::string &levelPath);
    void update();
};
