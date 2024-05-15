#pragma once

#include "global.hpp"
#include "plant.hpp"



class Tile
{
public:
    Tile(FloatRect rect);
    bool isPlanted(){return PlantedOrNot;}
    void seed(Plant *plant);
    void render();
    bool isInside(FloatRect plantRect);
    Vector2f tileCenter();
    void free();
    void update();
    
private:
    bool PlantedOrNot = false;
    FloatRect rectangle;
    Plant* plantInTile = nullptr;
};