#include "Editor.h"

#include <iostream>

Editor::Editor(GameEngine *gameEngine)
: Scene(gameEngine)
{
    init("");
}

Editor::Editor(GameEngine *gameEngine, const std::string &levelPath)
    : Scene(gameEngine)
    , m_levelPath(levelPath)
{
    init(m_levelPath);
}

void Editor::init(const std::string &levelPath)
{

}

void Editor::sMovement()
{
}

void Editor::sLifespan()
{
}

void Editor::sCollision()
{
}

void Editor::sAnimation()
{
}

void Editor::sDebug()
{

}

void Editor::sRender()
{
}

void Editor::sDoAction(const Action &action)
{

}

void Editor::update()
{
    m_entityManager.update();

    sMovement();
    sLifespan();
    sCollision();
    sAnimation();
    sRender();
}

void Editor::onEnd()
{
}
