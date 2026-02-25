#include "ExampleScene.h"
#include <imgui-SFML.h>
#include <imgui.h>

ExampleScene::ExampleScene(GameEngine *gameEngine)
    : Scene(gameEngine)
{
    init();
}

void ExampleScene::init()
{
    Logger::getInstance();
    Logger::log(Logger::DEBUG, "Initializing example scene...");
    m_tilemap = Tilemap("outside_tileset", Vec2(32, 32), Vec2(32, 32), "config/testmap.txt");
    m_tilemap.loadMap(m_entityManager, m_game->assets());

    auto e = m_entityManager.addEntity("player");
    e->addComponent<CTransform>().pos = gridToMidPixel(2, 2, 0, -8);
    e->addComponent<CState>("IDLE_DOWN");
    e->addComponent<CAnimation>(m_game->assets().getAnimation("IDLE_DOWN"), true);
    e->addComponent<CBoundingBox>(Vec2(32, 48));
    e->addComponent<CDirection2D>(Direction::DOWN);

    m_player = e;

    m_camera.setSize(sf::Vector2f(960.0, 640.0f));
    m_camera.setCenter(m_player->getComponent<CTransform>().pos.x, m_player->getComponent<CTransform>().pos.x);
    m_camera.zoom(0.7);

    Tile testTile;
    testTile.tag = "TILEMAP";
    testTile.textureX = 0;
    testTile.textureY = 0;
    testTile.renderX = 0;
    testTile.renderY = 0;
    testTile.collision = false;

    registerAction(sf::Mouse::Left + 1000, "LEFT_MOUSE");
}

void ExampleScene::topLayer()
{

}

void ExampleScene::middleLayer()
{
}

void ExampleScene::bottomLayer()
{
}

void ExampleScene::update()
{
    m_entityManager.update();

    // TODO: implement pause functionality

    sMovement();
    sLifespan();
    sCollision();
    sAnimation();
    sCamera();
    sRender();
}

void ExampleScene::sMovement()
{
    
}

void ExampleScene::sCamera()
{
    auto pos = m_player->getComponent<CTransform>().pos;
    m_camera.setCenter(sf::Vector2f(pos.x, pos.y));
    m_game->window().setView(m_camera);
}

void ExampleScene::sLifespan()
{
}

void ExampleScene::sCollision()
{
}

void ExampleScene::sAnimation()
{
    if (m_player->getComponent<CState>().state == "IDLE_DOWN" && m_player->getComponent<CAnimation>().animation.getName() != "IDLE_DOWN")
    {
        m_player->addComponent<CAnimation>(m_game->assets().getAnimation("IDLE_DOWN"));
    }

    for (auto e : m_entityManager.getEntities())
    {
        e->getComponent<CAnimation>().animation.update();
    }
}

void ExampleScene::sRender()
{
    m_tilemap.render(m_entityManager, m_game->window());

    for (auto e : m_entityManager.getEntities())
    {
        auto &transform = e->getComponent<CTransform>();

        if (e->hasComponent<CAnimation>())
        {
            auto &animation = e->getComponent<CAnimation>().animation;
            animation.getSprite().setRotation(transform.angle);
            animation.getSprite().setPosition(transform.pos.x, transform.pos.y);
            animation.getSprite().setScale(transform.scale.x, transform.scale.y);
            m_game->window().draw(animation.getSprite());
        }

        if (e->hasComponent<CBoundingBox>() && e->getComponent<CBoundingBox>().active)
        {
            auto &bBox = e->getComponent<CBoundingBox>();
            bBox.rect.setPosition(transform.pos.x, transform.pos.y);
            m_game->window().draw(bBox.rect);
        }
    }

    ImGui::ShowDemoWindow();
}

void ExampleScene::onEnd()
{
}

void ExampleScene::sDebug()
{
}

void ExampleScene::sDoAction(const Action &action)
{
    if (action.type() == "START")
    {
        if (action.name() == "LEFT_MOUSE")
        {
            std::cout << "Mouse Clicked" << std::endl;
        }
    }

    if (action.type() == "END")
    {

    }
}

Vec2 ExampleScene::gridToMidPixel(float gridX, float gridY, float offsetX, float offsetY)
{
    float pixelX = gridX * m_tileWidth;
    float pixelY = gridY * m_tileHeight;

    return Vec2((pixelX + (m_tileWidth / 2)) + offsetX, (pixelY + (m_tileHeight / 2)) + offsetY);
}