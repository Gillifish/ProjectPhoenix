#pragma once

#include <iostream>
#include <string>

#include "Vec2.h"
#include "EntityManager.h"
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Logger.h"

struct Tile
{
    std::string tag;
    float textureX;
    float textureY;
    float renderX;
    float renderY;
    bool collision = false;
    bool empty = true;
};

typedef std::vector<Tile> TileVec;

class Tilemap
{
    std::string m_texTag = "none";
    Vec2 m_tileSize = { 32, 32 };
    Vec2 m_mapSize = { 32, 32 };
    std::string m_mapFilePath = "";
    std::string m_tileTag = "TILEMAP";
    TileVec m_tVec;
    Tile m_errorTile;
    
    void setTexturePath(std::string &path);
    void setTileTag(std::string &tag);
    void loadMapFile();


public:
    Tilemap() = default;
    Tilemap(std::string texTag, Vec2 tileSize, Vec2 mapSize, std::string path);

    void loadMap(EntityManager &eManager, Assets &assets);
    void render(EntityManager &eManager, sf::RenderWindow &window);
    Vec2 getTileSize();
    TileVec getTileVector();
    std::string getTextureTag();
    std::string getTileTag();
    Tile& getTileByPosition(float renderX, float renderY);
    bool getEmptyTile(Tile*& t);
    bool isEmptyTile(Vec2 pos);
    void addTile(Tile t);
    void addTile(std::string tag, float textureX, float textureY, float renderX, float renderY, bool collision);
    void removeTile(Tile t);
    void removeTile(std::string tag, float textureX, float textureY, float renderX, float renderY, bool collision);
    uint8_t save();
    Vec2 gridToPixel(float gridX, float gridY);
    Vec2 gridToMidPixel(float gridX, float gridY);
};