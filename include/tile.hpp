#pragma once

#include "global.hpp"



class Tile
{
public:
    Tile(FloatRect rect);
    bool isPlanted(){return PlantedOrNot;}
    void seed();
    void render(RenderWindow &window);
    bool isInside(FloatRect plantRect);
    Vector2f tileCenter();
    
private:
    bool PlantedOrNot = false;
    FloatRect rectangle;
};