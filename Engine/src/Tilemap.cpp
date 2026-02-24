#include "Tilemap.h"

Tilemap::Tilemap(std::string texTag, Vec2 size, std::string filePath) : 
    m_texTag(texTag), 
    m_tileSize(size),
    m_mapFilePath(filePath)
{
    m_errorTile.tag = "ERRORTILE";
    m_errorTile.textureX = 0;
    m_errorTile.textureY = 0;
    m_errorTile.renderX = 0;
    m_errorTile.renderY = 0;
    m_errorTile.collision = false;

    loadMapFile();
}

void Tilemap::loadMapFile()
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    auto path = currentDir.string() + "/" + m_mapFilePath;

    std::fstream inputFile(path);
    if (!inputFile)
    {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    std::string line;

    while(std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        Tile tile;
        iss >> tile.tag;
        iss >> tile.textureX;
        iss >> tile.textureY;
        iss >> tile.renderX;
        iss >> tile.renderY;
        iss >> tile.collision;

        m_tVec.push_back(tile);
    }

    inputFile.close();
}

void Tilemap::loadMap(EntityManager &eManager, Assets &assets)
{
    for (auto tile : getTileVector())
    {
        auto e = eManager.addEntity(tile.tag);
        e->addComponent<CSprite>();
        auto &sprite = e->getComponent<CSprite>().sprite;
        sprite.setTexture(assets.getTexture(getTextureTag()));
        Vec2 v(gridToPixel(tile.textureX, tile.textureY));
        sprite.setTextureRect(sf::IntRect(v.x, v.y, getTileSize().x, getTileSize().y));
        sprite.setOrigin(getTileSize().x / 2, getTileSize().y / 2);

        e->addComponent<CBoundingBox>(getTileSize());

        auto& bBox = e->getComponent<CBoundingBox>();
        bBox.active = true;

        auto pos = gridToMidPixel(tile.renderX, tile.renderY);
        sprite.setPosition(pos.x, pos.y);

        e->addComponent<CTransform>(pos);
    }
}

void Tilemap::render(EntityManager &eManager, sf::RenderWindow &window)
{
    for (auto e : eManager.getEntities("TILEMAP"))
    {
        window.draw(e->getComponent<CSprite>().sprite);
    }
}

void Tilemap::setTexturePath(std::string &path)
{
    m_mapFilePath = path;
}

void Tilemap::setTileTag(std::string &tag)
{
    m_tileTag = tag;
}

Vec2 Tilemap::getTileSize()
{
    return m_tileSize;
}

TileVec Tilemap::getTileVector()
{
    return m_tVec;
}

std::string Tilemap::getTileTag()
{
    return m_tileTag;
}

std::string Tilemap::getTextureTag()
{
    return m_texTag;
}

// *** Be careful of iterator invalidation on the tile vector
Tile& Tilemap::getTileByPosition(float renderX, float renderY)
{
    for (auto& i : m_tVec)
    {
        if (i.renderX == renderX && i.renderY == renderY)
        {
            return i;
        }
    }

    return m_errorTile;
}

void Tilemap::addTile(Tile t)
{
    m_tVec.push_back(t);
}

void Tilemap::addTile(std::string tag, float textureX, float textureY, float renderX, float renderY, bool collision)
{
    Tile t;
    t.tag = tag;
    t.textureX = textureX;
    t.textureY = textureY;
    t.renderX = renderX;
    t.renderY = renderY;
    t.collision = collision;

    m_tVec.push_back(t);
}

void Tilemap::removeTile(Tile t)
{
    for (auto& t : m_tVec)
    {
        /* code */
    }
}

void Tilemap::removeTile(std::string tag, float textureX, float textureY, float renderX, float renderY, bool collision)
{

}

uint8_t Tilemap::save()
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    auto path = currentDir.string() + "/" + m_mapFilePath;

    std::ofstream outputFile(path);
    if (!outputFile)
    {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    for (auto& t : m_tVec)
    {
        outputFile << t.tag << " ";
        outputFile << t.textureX << " ";
        outputFile << t.textureY << " ";
        outputFile << t.renderX << " ";
        outputFile << t.renderY << " ";
        outputFile << t.collision << std::endl;
    }

    outputFile.close();

    return 0;
}

Vec2 Tilemap::gridToPixel(float gridX, float gridY)
{
    return Vec2(gridX * m_tileSize.x, gridY * m_tileSize.y);
}

Vec2 Tilemap::gridToMidPixel(float gridX, float gridY)
{
    float pixelX = gridX * m_tileSize.x;
    float pixelY = gridY * m_tileSize.y;

    return Vec2(pixelX + (m_tileSize.x / 2), pixelY + (m_tileSize.y / 2));
}