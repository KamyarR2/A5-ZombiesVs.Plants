#pragma once

#include "global.hpp"
#include "projectile.hpp"


class Plant{

public:
    Plant(int x, int y, string address, int v, string projAddress);
    ~Plant();
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
    bool isAlive(){return DeadOrNot;}
    bool canShoot(){return hasProjectile;}
    string getProjAddress(){return projAddress;}
    
private:
    int value;
    Sprite sprite;
    Texture texture;
    string address;
    vector <Projectile*> projectiles;
    bool PlantedOrNot = false;
    bool DraggedOrNot = false;
    bool DeadOrNot = false;
    bool hasProjectile = false;
    string projAddress;
};