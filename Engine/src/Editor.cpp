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
    Logger::getInstance();
    Logger::log(Logger::DEBUG, "Initializing tilemap editor...");
    m_tilemap = Tilemap("outside_tileset", Vec2(32, 32), "config/testmap.txt");
    m_tilemap.loadMap(m_entityManager, m_game->assets());
}

void Editor::sDebug()
{

}

void Editor::sRender()
{
    m_tilemap.render(m_entityManager, m_game->window());

    for (auto e : m_entityManager.getEntities())
    {
        auto &transform = e->getComponent<CTransform>();

        if (e->hasComponent<CBoundingBox>() && e->getComponent<CBoundingBox>().active)
        {
            auto &bBox = e->getComponent<CBoundingBox>();
            bBox.rect.setPosition(transform.pos.x, transform.pos.y);
            m_game->window().draw(bBox.rect);
        }
    }
}

void Editor::sImGuiWindow()
{
    ImGui::Begin("Tilemap Information");
    ImGui::Text("Test");
    ImGui::End();
}

void Editor::sDoAction(const Action &action)
{

}

void Editor::update()
{
    m_entityManager.update();

    sImGuiWindow();
    sRender();
}

void Editor::onEnd()
{
}
