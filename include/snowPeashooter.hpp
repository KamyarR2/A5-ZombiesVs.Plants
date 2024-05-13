#pragma once

#include "global.hpp"


class SnowPeashooter
{
public:
    SnowPeashooter(int x, int y, string address, int v, string type);
    ~SnowPeashooter();
    void render(RenderWindow &window);
    void update(Vector2i pos);
    void startDrag();
    void stopDrag(Vector2f tileOrigin);
    bool isDragging(){return DraggedOrNot;}
    Vector2f getSpritePosition(){return sprite.getPosition();}
    FloatRect getSpriteRect(){return sprite.getGlobalBounds();}
    void planted();
    bool isPlanted(){return PlantedOrNot;}
    int getValue(){return value;}


private:
    int value;
    Sprite sprite;
    Texture texture;
    string address;
    bool PlantedOrNot = false;
    bool DraggedOrNot = false;
};